/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:58:10 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/15 04:02:11 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//配列の要素間入れ替え
void	swap_queue(int i, int j, t_rules *rule)
{
	int	temp;

	temp = rule->queue[i];
	rule->queue[i] = rule->queue[j];
	rule->queue[j] = temp;
}

//id1がid2より優先されるべきかを返す
int compare_coders(int id1, int id2, t_rules *rule)
{
	long long time1;
	long long time2;
	if (rule->scheduler_type == FIFO) // FIFOならキューに並んだ時間
	{
		time1 = rule->coders[id1 - 1].enqueue_time;
		time2 = rule->coders[id2 - 1].enqueue_time;
	}
	else // EDFなら最後のコンパイル時間
	{
		time1 = rule->coders[id1 - 1].last_compile_start;
		time2 = rule->coders[id2 - 1].last_compile_start;
	}
	if (time1 < time2)
		return TRUE;
	return FALSE;
}

// nがヒープ構造状最適な位置へと上る
void	shift_up(int n, t_rules *rule)
{
	while (1 < n && compare_coders(rule->queue[n], rule->queue[n / 2], rule))
	{
		swap_queue(n, n / 2, rule);
		n /= 2;
	}
}

// nがヒープ構造状最適な位置へと下る
void	shift_down(int n, t_rules *rule)
{
	int		left;
	int		right;
	int		winner;

	while (TRUE) // 一番大きい値を見つけてそれとnを交換する、nが一番大きいならそこで終了
	{
		left = 2 * n;
		right = 2 * n + 1;
		winner = n;
		if (left <= rule->queue_size && \
			compare_coders(rule->queue[left], rule->queue[winner], rule))
			winner = left;
		if (right <= rule->queue_size && \
			compare_coders(rule->queue[right], rule->queue[winner], rule))
			winner = right;
		if (winner == n)
			break;
		swap_queue(n, winner, rule);
		n = winner;
	}
}

// 優先キューからcoderを抜いて、ヒープ構造を修正する
void	pop_queue(t_coder *coder)
{
	t_rules	*rule;
	int		n;

	rule = coder->rule;
	n = 0;
	while (++n <= rule->queue_size)
		if (rule->queue[n] == coder->id)
			break ;
	rule->queue[n] = rule->queue[rule->queue_size];
	rule->queue_size--;
	coder->is_in_queue = FALSE;
	if (rule->queue_size < n)
		return ;
	shift_up(n, rule);
	shift_down(n, rule);
}

//スケジューリング統括関数
int	scheduler(t_coder *coder)
{
	t_rules	*rule;
	t_coder	*l_coder;
	t_coder	*r_coder;

	rule = coder->rule;
	l_coder = &rule->coders[coder->left_coder_id - 1];
	r_coder = &rule->coders[coder->right_coder_id - 1];
	if (coder->is_in_queue == FALSE) //キューに入っていなければ予約する
	{
		rule->queue_size++;
		rule->queue[rule->queue_size] = coder->id;
		coder->is_in_queue = TRUE;
		coder->enqueue_time = get_time();
		shift_up(rule->queue_size, rule);
	}
	//ここから予約していて、キューの中で自分が優先されるべきかを返す処理になる
	if (l_coder->is_in_queue && compare_coders(coder->left_coder_id, coder->id, rule))
		return FALSE;
	if (r_coder->is_in_queue && compare_coders(coder->right_coder_id, coder->id, rule))
		return FALSE;
	return TRUE;
}
