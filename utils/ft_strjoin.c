/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:52:07 by akhouya           #+#    #+#             */
/*   Updated: 2022/03/20 18:13:57 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		l;

	i = 0;
	l = 0;
	if (!s1 && !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
		str[l++] = s1[i++];
	i = 0;
	while (s2[i])
		str[l++] = s2[i++];
	str[l] = '\0';
	return (&str[0]);
}
