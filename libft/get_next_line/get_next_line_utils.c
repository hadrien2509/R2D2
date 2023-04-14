/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:53:21 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/14 16:55:04 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_free(char **str)
{
	if (!str || !*str)
		return (NULL);
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s2 || !*s2)
		return (s1);
	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof (char));
		if (!s1)
			return (0);
		s1[0] = 0;
	}
	s3 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s3)
		return (ft_free(&s1));
	i = -1;
	j = 0;
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = 0;
	free(s1);
	return (s3);
}
