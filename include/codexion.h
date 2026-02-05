/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:17:39 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/05 18:25:34 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>


// /* --- 定数 --- */
// # define SCHED_FIFO 0
// # define SCHED_EDF  1


// /* --- 構造体 --- */
// struct s_rules;

// // ドングル（共有リソース）
// typedef struct s_dongle
// {
//     int             id;
//     pthread_mutex_t lock;           // ドングルを守る鍵
//     long long       last_used_time; // クールダウン判定用
// } t_dongle;


// // コーダー（スレッド）
// typedef struct s_coder
// {
//     int             id;             // 1 ~ N
//     int             compile_count;  // コンパイル回数
//     long long       last_compile_start; // Burnout判定用

//     // 円卓の構造：左右のドングルへのポインタ
//     t_dongle        *left_dongle;
//     t_dongle        *right_dongle;

//     struct s_rules  *rules;         // 全体ルールへの参照
//     pthread_t       thread_id;      // スレッドの実体
//     pthread_mutex_t coder_lock;     // 自分自身のデータ保護用
// } t_coder;

// // 全体設定（引数で受け取るもの）
// typedef struct s_rules
// {
//     int             num_coders;
//     long long       time_burnout;
//     long long       time_compile;
//     long long       time_debug;
//     long long       time_refactor;
//     int             num_required;    // ノルマ回数
//     long long       dongle_cooldown;
//     int             scheduler;       // FIFO or EDF

//     long long       start_time;      // シミュレーション開始時刻
//     int             is_dead;         // 誰かがBurnoutしたら1
//     int             all_full;        // 全員ノルマ達成したら1

//     pthread_mutex_t write_lock;      // ログ出力用
//     pthread_mutex_t stop_lock;       // 終了フラグ用

//     t_coder         *coders;         // 配列
//     t_dongle        *dongles;        // 配列
// } t_rules;

// // 優先度付きキュー（待ち行列）
// typedef struct s_pqueue
// {
//     struct s_coder  **data;         // 待っているコーダーへのポインタ配列（ヒープ木）
//     int             size;           // 現在待っている人数
//     int             capacity;       // 最大容量（= num_coders）
//     pthread_mutex_t lock;           // 行列の操作を守る鍵
//     pthread_cond_t  cond_empty;     // ドングルが空くのを待つための条件変数
// } t_pqueue;

// /* --- プロトタイプ宣言 --- */
// int     init_all(t_rules *rules, char **argv);

// void codexion(int argc, char **argv);

#endif
