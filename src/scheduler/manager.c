#include <sys/time.h>

void set_future_time(struct timespec *ts, int ms_to_wait)
{
    struct timeval tv;

    // 1. 今の時間を取得 (例: 100秒 500,000マイクロ秒)
    gettimeofday(&tv, NULL);

    // 2. マイクロ秒をナノ秒に変換して計算 (1us = 1000ns)
    //    今のナノ秒 + 待ちたい時間(ミリ秒→ナノ秒)
    long long nsec = (tv.tv_usec * 1000) + (ms_to_wait * 1000000);

    // 3. 繰り上がり計算 (10億ナノ秒を超えたら秒に足す)
    ts->tv_sec = tv.tv_sec + (nsec / 1000000000);
    ts->tv_nsec = nsec % 1000000000;
}

// 使い方: 1秒(1000ms)待つ設定を作る
struct timespec ts;
set_future_time(&ts, 1000);
pthread_cond_timedwait(&cond, &lock, &ts);
