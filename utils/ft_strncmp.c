/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:51:55 by akhouya           #+#    #+#             */
/*   Updated: 2022/03/20 18:10:03 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned int	i;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (str1[i] == str2[i] && --n > 0 && str1[i] && str2[i])
		i++;
	if (n == 0)
		return (0);
	return (str1[i] - str2[i]);
}
