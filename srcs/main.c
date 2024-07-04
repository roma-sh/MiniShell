/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:49:34 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/04 15:33:00 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_prompt(char **env)
{
	char		*input_line;
	t_line_data	*line_data; // a pointer to the first element of the linked list of nodes
	t_line_data	*tmp; // a temporary pointer to iterate through the linked list
	t_env *mini_env;	// our first list for the env (for now if it stays here)

	line_data = NULL;

	// I create the path here for now and let's see later
	create_path(env, &mini_env);
	printf("helloooo\n");
	while (1)
	{
		input_line = readline("minishell >");
		if (input_line && (ft_strcmp(input_line, "") != 0))
		{
			add_history(input_line);
			printf("You entered : %s\n", input_line);
			ft_split_line(input_line, &line_data, env);
			// standard_IO(line_data);
			// exec_command(line_data, env);
		tmp = line_data; // Use a temporary pointer for iteration
		while (tmp != NULL) // print the linked list to check if it's working
		{
			if (tmp->redirctor != NULL)
				printf("redirector is: %s\n", tmp->redirctor);
			if (tmp->after_redirctor != NULL)
				printf("File name is: %s\n", tmp->after_redirctor);
			if (tmp->expander != NULL)
				printf("expander is: %s\n", tmp->expander);
			if (tmp->command != NULL)
			{
				int i = 0;
				while (tmp->command[i] != NULL)
				{
					if (i == 0)
						printf("Command is: %s\n", tmp->command[i]);
					else
						printf("argument number %d is: %s\n", i, tmp->command[i]);
					i++;
				}
			}
			tmp = tmp->next;
		}
		// Free the linked list
		while (line_data != NULL)
		{
			tmp = line_data;
			line_data = line_data->next;
			free(tmp);
		}
		free(input_line);
		}
	}
}

int	main(int argc, char **argv, char **env)
{

	(void)argv;
	(void)argc;
	// (void)env;
	if (argc != 1)
	{
		printf("This program doesn't take any arguments!\n");
		return (1);
	}
	start_prompt(env);

	return (0);
}
