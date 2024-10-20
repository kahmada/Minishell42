/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:05:48 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/18 14:26:11 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimmed;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	len = end - start;
	trimmed = (char *)malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_memcpy(trimmed, s1 + start, len);
	trimmed[len] = '\0';
	return (trimmed);
}

void	ft_initialize2(t_data *mydata)
{
	mydata->cmd = NULL;
	mydata->head = NULL;
	mydata->prev = NULL;
}
