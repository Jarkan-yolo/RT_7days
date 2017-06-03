/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multithread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jribeiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 19:47:08 by jribeiro          #+#    #+#             */
/*   Updated: 2017/06/03 21:51:19 by jribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>


static void		*function(void *arg)
{
	t_thread_data	*data;

	data = (t_thread_data *)arg;
	ft_intersect(data->ray, data->liste);
	return (NULL);
}

t_listobj		*copyList(t_listobj *liste)
{
	t_listobj	*copy;
	t_listobj	*first;

	copy = NULL;
	if (!(copy = (t_listobj *)malloc(sizeof(t_listobj))))
		exit(EXIT_FAILURE);
	first = copy;
	while (liste)
	{
		if (liste->next != NULL)
		{
			copy->next = NULL;
			if (!(copy->next = (t_listobj *)malloc(sizeof(t_listobj))))
				exit(EXIT_FAILURE);
		}
		copy->objet = copyListObj(liste->objet);


		copy = copy->next;
		liste = liste->next;
	}
	return (copy);
}

t_rayon			*copyRayon(t_rayon *ray);
{
}

t_thread_data	*copyData(t_listobj *liste, t_rayon *ray)
{
	t_thread_data	*data;

	data = NULL;
	if (!(data = (t_thread_data *)malloc(sizeof(t_thread_data))))
		exit(EXIT_FAILURE);
	data->ray = NULL;
	if (!(data->ray = (t_rayon *)malloc(sizeof(t_rayon))))
		exit(EXIT_FAILURE);
	data->liste = copyList(liste);
	data->ray = copyRayon(ray);
	return (data);
}

int				initThreads(t_listobj *liste, t_rayon *ray, t_thread *threads)
{
	int				i;
	t_thread_data	*data;

	i = 0;
	data = NULL;
	while (liste)
	{
		data = copyData(liste, ray);
		if (pthread_create(&(threads->t[i]), NULL, function, (void *)data))
			return (-1);
		++i;
		free(data);
		data = NULL;
		liste = liste->next;
	}
	return (i);
}

void			waitThreads(t_thread *threads, int nb_threads)
{
	int				i;

	i = 0;
	while (i < nb_threads)
	{
		pthread_join(threads->t[i], NULL);
		++i;
	}
}
