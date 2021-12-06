/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:55:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/06 11:33:58 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/fdf.h"
#include <stdlib.h>

static int	cont_char(char const *s, char c)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	if (s[0] && s[0] != c)
		cont++;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			cont++;
		i++;
	}
	return (cont);
}

static char	*ft_word(char const *s, char c, int i)
{
	int		p;
	int		k;
	char	*w;

	p = i;
	while (s[i] && s[i] != c)
		i++;
	w = (char *)malloc(sizeof(char) * ((i - p) + 1));
	if (!w)
		return (NULL);
	k = 0;
	while (p != i)
	{
		w[k] = s[p];
		k++;
		p++;
	}
	w[k] = '\0';
	return (w);
}

void	ft_split(char const *s1, char c, t_fdf *d)
{
	int		i;
	int		k;
	char	*aux;

	if (!s1)
		return ;
	d->read.buf = (char **)malloc(sizeof(char *) * (cont_char(s1, c) + 1));
	if (!d->read.buf)
		return ;
	i = 0;
	k = 0;
	while (i <= (int)ft_strlen(s1) && cont_char(s1, c))
	{
		aux = ft_word(s1, c, i);
		if (ft_strlen(aux))
		{
			d->read.buf[k] = ft_strdup(aux);
			i += (ft_strlen(d->read.buf[k]) + 1);
			k++;
		}
		else
			i++;
		free(aux);
		aux = NULL;
	}
	d->read.buf[k] = NULL;
}