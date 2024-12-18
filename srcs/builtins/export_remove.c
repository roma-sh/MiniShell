/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:23:27 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/07 18:25:12 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	node_remove(t_env **new_export, char *line, int i);
char	*ft_strjoin_export(char const *s1, char const *s2, char c);

void	find_if_exists(t_env **new_export, char *line, t_env **mini_env)
{
	int	i;

	i = 0;
	while (line[i] != '=' && line[i] != '\0')
		i++;
	if (*new_export == NULL)
		return ;
	if (ft_strncmp("declare -x ", line, 11) == 0)
		node_remove(new_export, line, i);
	else
		node_remove(mini_env, line, i);
}

void	node_remove(t_env **node_remove, char *line, int i)
{
	t_env	*curr;
	t_env	*remove;

	curr = *node_remove;
	while (curr->next != NULL)
	{
		if (ft_strncmp(line, curr->next->line, i) == 0 \
			&& (curr->next->line[i] == '=' || curr->next->line[i] == '\0'))
		{
			remove = curr->next;
			curr->next = curr->next->next;
			free(remove->line);
			free(remove);
			return ;
		}
		curr = curr->next;
	}
}

char	*ft_strjoin_export(char const *s1, char const *s2, char c)
{
	size_t	s1len;
	size_t	s2len;
	char	*ptr;
	size_t	i;

	i = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ptr = (char *)ft_malloc((s1len + s2len + 3) * sizeof(char));
	while (i < s1len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = c;
	i = 0;
	while (i < s2len)
	{
		ptr[s1len + 1 + i] = s2[i];
		i++;
	}
	ptr[s1len + i + 1] = c;
	return (ptr[s1len + s2len + 2] = '\0', ptr);
}

void	print_export(t_env **new_export)
{
	t_env	*tmp;

	tmp = *new_export;
	while (tmp != NULL)
	{
		if (tmp->line[11] == '?' && tmp->line[12] == '=')
			tmp = tmp->next;
		else
		{
			printf("%s\n", tmp->line);
			tmp = tmp->next;
		}
	}
}

void	create_export_path(t_env **mini_env, t_env **new_export)
{
	t_env	*new_env;
	int		len;
	char	*export_line;
	t_env	*tmp;

	len = 0;
	tmp = *mini_env;
	while (tmp != NULL)
	{
		len = ft_strlen(tmp->line) + 13;
		export_line = create_export_line(tmp->line);
		new_env = (t_env *)ft_malloc(sizeof(t_env));
		new_env->line = export_line;
		new_env->line[len] = '\0';
		if (!new_env->line)
		{
			free(new_env);
			exit(EXIT_FAILURE);
		}
		new_env->next = NULL;
		add_path_to_list(new_export, new_env);
		tmp = tmp->next;
	}
}
