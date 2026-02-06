/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:21:39 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/06 16:19:58 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

typedef struct  routine_arg{
    int             n;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} routine_arg;

void *routine(void *arg)
{
	routine_arg *r_arg;

    r_arg = (routine_arg *)arg;

    while(1)
    {
        pthread_mutex_lock(&r_arg->mutex);
        r_arg->n++;
        pthread_mutex_unlock(&r_arg->mutex);
    }
    return NULL;
}

int main(void)
{
	pthread_t	threads[10];
    routine_arg arg;

	arg.n = 0;
    pthread_mutex_init(&arg.mutex, NULL);

	for (int i = 0; i < 5; i++)
		pthread_create(&threads[i], NULL, routine, &arg);

	for (int i = 0; i < 5; i++)
		pthread_join(threads[i], NULL);

	printf("n = %d\n", arg.n);
    pthread_mutex_destroy(&arg.mutex);
	return 0;
}
