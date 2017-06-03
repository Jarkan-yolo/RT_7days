/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jribeiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 21:20:21 by jribeiro          #+#    #+#             */
/*   Updated: 2017/06/03 21:51:26 by jribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void				*copyListObj(void *objet, int type)
{
	void				*objcopy;

	objcopy = NULL;
	if (!(objcopy = (void *)malloc(128)))
		exit(EXIT_FAILURE);
}

static t_listobj		*copyList(t_listobj *liste)
{
	t_listobj			*copy;
	t_listobj			*first;

	copy = NULL;
	if (!(copy = (t_listobj *)malloc(sizeof(t_listobj))))
		exit(EXIT_FAILURE);
	first = copy;
	while (liste)
	{
		copy->next = NULL;
		if (liste->next != NULL)
			if (!(copy->next = (t_listobj *)malloc(sizeof(t_listobj))))
				exit(EXIT_FAILURE);
		copy->objet = copyListObj(liste->objet, liste->type);
		copy->type = liste->type;
		copy = copy->next;
		liste = liste->next;
	}
	return (first);
}

static t_rayon			*copyRay(t_rayon *ray)
{
}

static t_thread_data	*copyData(t_listobj *liste, t_rayon *ray)
{
	t_thread_data		*data;

	data = NULL;
	if (!(data = (t_thread_data *)malloc(sizeof(t_thread_data))))
		exit(EXIT_FAILURE);
	data->liste = copyList(liste);
	data->ray = copyRay(ray);
	return (data);
}
