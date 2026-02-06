/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:17:39 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/06 22:52:26 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

// --- 定数定義 ---
# define TRUE 1
# define FALSE 0
# define FIFO 1
# define EDF 2

// エラーメッセージ
# define ERR_ARGS "Error: Invalid arguments\n"
# define ERR_MALLOC "Error: Memory allocation failed\n"
# define ERR_THREAD "Error: Thread creation failed\n"

typedef struct s_rules	t_rules;

/*
** ‍コーダー個人の構造体
** 各スレッドが自分の状態を管理するために作成し、管理する。
*/
typedef struct s_coder
{
	int				id; // コーダー番号 (1 ~ N)
	pthread_t		tid; // スレッドID
	// --- ドングル情報 ---
	int				left_dongle_id; // 左手のドングル番号（配列インデックス）
	int				right_dongle_id; // 右手のドングル番号（配列インデックス）
	// --- 状態管理 ---
	int				compile_count; // 今までにコンパイルした回数
	long long		last_compile_start; // 最後にコンパイルを開始した時刻 (ms)
	// --- 共有データへの参照 ---
	t_rules			*rules; // 親（全体設定）へのポインタ
}	t_coder;

/*
** 全体ルール・共有リソース構造体
** Main関数で一つだけ作られ、全員がこれを参照する。
** 参照/書き換えはすべてglobal_lockを通して行う。
*/
struct s_rules
{
	// --- 設定値 (Read Only) ---
	int				num_coders;
	long long		time_to_burnout; // Burnoutまでの時間
	long long		time_to_compile;
	long long		time_to_debug;
	long long		time_to_refactor;
	int				must_compile_count; // 目標回数 (-1なら無限)
	int				dongle_cooldown; // ドングルのクールダウン時間 (ms)
	int				scheduler_typy; // 優先順位付のタイプ
	// --- 時間管理 ---
	long long		start_time; // シミュレーション開始時刻
	// --- 制御フラグ ---
	int				is_simulation_active; // 1:継続中, 0:誰かが死んだor終了
	int				finished_coders; // 目標回数を達成した人数
	// --- 同期プリミティブ ---
	pthread_mutex_t	global_lock; // 全データ保護・出力保護用の神の鍵
	pthread_cond_t	cond; // スレッド就寝/起床変数
	// --- 共有リソース (ドングル) ---
	// ドングルごとの個別Mutex
	pthread_mutex_t	*dongle_locks;
	// ドングルが次に使えるようになる時刻
	long long		*dongle_ready_times;

	// --- 待ち行列 (FIFO Queue -> 後にHeap化) ---
	int				*queue; // 待っているコーダーのIDを入れる配列
	int				queue_size; // 現在並んでいる人数
	int				queue_capacity; // 配列の最大サイズ (= num_coders)
	// ※ FIFO用のリングバッファ変数 (Heap化する時は使わなくなる)
	int				q_head; // 取り出し位置
	int				q_tail; // 追加位置
	// --- 子データ ---
	t_coder			*coders; // コーダー配列
};

// プロトタイプ宣言
void	codexion(int argc, char **argv);
void	validate(int argc, char **argv);
void	init(t_rules *rule, int argc, char **argv);

#endif
