/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:55:42 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/27 18:26:52 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_parse(t_parse *parse)
{
	t_parse	*tmp;

	while (parse)
	{
		tmp = parse->next;
		if (parse->cmd)
			free(parse->cmd);
		free(parse);
		parse = tmp;
	}
}

// void	ft_lstfree(t_list **split)
// {
// 	if (!split | !(*split))
// 		return ;
// 	while (*split)
// 	{
// 		free(*split);
// 		*split = 0;
// 	}
// }

// void	ft_tokenfree(t_token **token)

// void	set_to_zero(void *content)
// {
// 	content = 0;
// }

// int	ft_free(t_data **data, t_parse **parse, t_token **token)
// {
// 	ft_lstfree((*data)->split, );
// }