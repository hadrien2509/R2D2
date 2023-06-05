/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:55:42 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/05 18:40:18 by hgeissle         ###   ########.fr       */
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

static	void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	quit(t_data *data, int status)
{
	if (!data)
		exit(status);
	if (data->env)
		free_env(data->env);
	if (data->pwd)
		free(data->pwd);
	exit(status);
}
