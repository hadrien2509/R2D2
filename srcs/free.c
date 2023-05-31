/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:55:42 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/31 19:12:43 by hgeissle         ###   ########.fr       */
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

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token);
		token = tmp;
	}
}
