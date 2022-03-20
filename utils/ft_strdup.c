/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhouya <akhouya@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:52:15 by akhouya           #+#    #+#             */
/*   Updated: 2022/03/20 18:13:52 by akhouya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../pipex.h"


void	*ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t	i;
    char	*ptr_d;
    char	*ptr_s;

    i = 0;
    ptr_d = (char *) dest;
    ptr_s = (char *) src;
    if (!dest && !src)
        return (NULL);
    while (i < n)
    {
        *ptr_d++ = *ptr_s++;
        i++;
    }
    return (dest);
}

char	*ft_strdup(char *s)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s, ft_strlen(s) + 1);
	return (str);
}
