/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:58:10 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/13 21:22:55 by ayhirose         ###   ########.fr       */
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
	if (rule->scheduler_type == FIFO)
	{
		time1 = rule->coders[id1 - 1].enqueue_time;
		time2 = rule->coders[id2 - 1].enqueue_time;
	}
	else
	{
		time1 = rule->coders[id1 - 1].last_compile_start;
		time2 = rule->coders[id2 - 1].last_compile_start;
	}
	if (time1 == time2)
		printf("omg!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"); //デバッグ用
	if (time1 < time2)
		return TRUE;
	return FALSE;
}

void	shift_up(int n, t_coder *coder)
{
	t_rules	*rule;

	rule = coder->rule;
	if (n == 1)
		return ;
	while (compare_coders(coder->id, rule->queue[n / 2], rule))
	{
		swap_queue(n, n / 2, rule);
		n /= 2;
		if (!n)
			break ;
	}
}

void	shift_down(t_coder *coder)
{
	t_rules	*rule;
	int		n;

	rule = coder->rule;
	while (compare_coders(coder->id, rule->queue[n / 2], rule))
	{
		swap_queue(n, n / 2, rule);
		n /= 2;
	}
}

void	pop_queue(t_coder *coder)
{

}

//スケジューリング統括関数
int	scheduler(t_coder *coder)
{
	t_rules	*rule;
	int		flag;

	rule = coder->rule;
	if (coder->is_in_queue == FALSE) //キューに入っていなければ予約する
	{
		rule->queue_size++;
		rule->queue[rule->queue_size] = coder->id;
		coder->is_in_queue = TRUE;
		coder->enqueue_time = get_time();
		shift_up(rule->queue_size, coder);
	}
	//ここから予約していて、キューの中で自分が優先されるべきかを返す処理になる
	flag = 1;
	flag *= compare_coders(coder->id, coder->left_coder_id, rule);
	flag *= compare_coders(coder->id, coder->right_coder_id, rule);
	return flag;
}
