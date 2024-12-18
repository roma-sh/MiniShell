/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:00:29 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/02 14:01:13 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_path(char **env, t_env **mini_env)
{
	t_env	*new_env;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp("OLDPWD", env[i], 6) != 0)
		{
			new_env = (t_env *)ft_malloc(sizeof(t_env));
			new_env->line = ft_strdup(env[i]);
			if (!new_env->line)
			{
				free(new_env);
				exit(EXIT_FAILURE);
			}
			new_env->next = NULL;
			add_path_to_list(mini_env, new_env);
		}
		i++;
	}
	add_status(mini_env);
}

void	add_path_to_list(t_env **mini_env, t_env *new_env)
{
	t_env	*tmp;

	if (*mini_env == NULL)
		*mini_env = new_env;
	else
	{
		tmp = *mini_env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_env;
	}
}
