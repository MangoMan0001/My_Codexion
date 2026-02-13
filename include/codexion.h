/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:17:39 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/13 21:06:51 by ayhirose         ###   ########.fr       */
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
# include <stddef.h>
# include <limits.h>

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
	// --- コーダー情報 ---
	int				left_coder_id; // 左で座ってるコーダーID
	int				right_coder_id; // 右で座ってるコーダーID
	// --- ドングル情報 ---
	int				left_dongle_id; // 左手のドングル番号（配列インデックス）
	int				right_dongle_id; // 右手のドングル番号（配列インデックス）
	// --- 状態管理 ---
	int				compile_count; // 今までにコンパイルした回数
	long long		last_compile_start; // 最後にコンパイルを開始した時刻 (ms)
	long long		enqueue_time; // queueに登録した時間（ms）fifoのみ使用
	int				is_in_queue; //queueに並んでいるのかいないのか
	// --- 共有データへの参照 ---
	t_rules			*rule; // 親（全体設定）へのポインタ
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
	int				scheduler_type; // 優先順位付のタイプ
	// --- 時間管理 ---
	long long		start_time; // シミュレーション開始時刻
	// --- 制御フラグ ---
	int				is_simulation_active; // 1:継続中, 0:誰かが死んだor終了
	int				finished_coders; // 目標回数を達成した人数
	// --- 同期プリミティブ ---
	pthread_mutex_t	global_lock; // 全データ保護・出力保護用の神の鍵
	pthread_cond_t	cond; // スレッド就寝/起床変数
	// --- 共有リソース (ドングル) ---
	pthread_mutex_t	*dongle_locks; // ドングルごとの個別Mutex
	long long		*dongle_cool_times; // ドングルが次に使えるようになる時刻
	int				*dongle_status; // 拾えるドングルは0、使ってるドングルは1
	// --- 待ち行列 (Heap) ---
	int				*queue; // 待っているコーダーのIDを入れる配列
	int				queue_size; // 現在並んでいる人数
	// --- 子データ ---
	t_coder			*coders; // コーダー配列
	// --- モニター ---
	pthread_t		monitor;
};

// プロトタイプ宣言

// core
int	codexion(int argc, char **argv);
int	validate(int argc, char **argv);
int	init(t_rules *rule, int argc, char **argv);

// scheduler
int		scheduler(t_coder *coder);
int		fifo(t_coder *coder);
void	pop_queue(t_coder *coder);

// simulation
int 		simulation(t_rules *rule);
void		*routine(void *arg);
void		routine_compile(t_coder *coder, int *flag);
void		*monitor(void *arg);

// utils
void		free_rule(t_rules *rule);
void		destroy_mutexes(t_rules *r);
void		just_sleep(long long time, t_rules *rules);
long long	get_time(void);
void		*my_calloc(size_t size);
void		print_log(t_coder *coder, char *msg);
void		print_log_lock(t_coder *coder, char *msg);


#endif
