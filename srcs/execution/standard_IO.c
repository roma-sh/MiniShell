/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_IO.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 07:00:37 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/23 23:28:41 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	standard_io(t_input *data)
void	standard_io(t_input *data, int **pipe_fd, int i, int processes_num)
{
	t_line_data	*new_line_data;
	int			fd;
	// printf("-------------------standard_io--------------------------\n");
	new_line_data = data->data_node;
	// printf("from standard_io() the command is %s\n", data->cmd_args[0]);
	// printf("processes_num is: %d\n", processes_num);
	// printf("i is: %d\n", i);
	// // printf("redirector is: %s\n", data->data_node->redirctor);
	// printf("-------------------end--------------------------\n");

	if (i == 0 && pipe_fd[i] != NULL)
	{
		close(pipe_fd[i][0]);
		dup2(pipe_fd[i][1], STDOUT_FILENO);
		close(pipe_fd[i][1]);
	}
	else if (i != 0 && i == (processes_num - 1) && pipe_fd[i - 1] != NULL)
	{
		close(pipe_fd[i - 1][1]);
		dup2(pipe_fd[i - 1][0], STDIN_FILENO);
		close(pipe_fd[i - 1][0]);
	}
	else if (i > 0 && i < (processes_num - 1))
	{
		if (pipe_fd[i - 1] != NULL)
		{
			close(pipe_fd[i - 1][1]);
			dup2(pipe_fd[i - 1][0], STDIN_FILENO);
			close(pipe_fd[i - 1][0]);
		}
		if (pipe_fd[i] != NULL)
		{
			close(pipe_fd[i][0]);
			dup2(pipe_fd[i][1], STDOUT_FILENO);
			close(pipe_fd[i][1]);
		}
	}
	while (new_line_data != NULL)
	{
		if (new_line_data->type == 5)
		{
			new_line_data = new_line_data->next;
			fd = open(new_line_data->after_redirctor, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (new_line_data->type == 4)
		{
			new_line_data = new_line_data->next;
			fd = open(new_line_data->after_redirctor, O_WRONLY | O_CREAT | O_TRUNC, 0644);	//O_WRONLY: the file is opened for writing only.
																					// O_CREAT: to create the file if it does not already exist.
																					// O_TRUNC: clearing any existing content in the file.
																					// 0644: the file permission.
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (new_line_data->type == 3)
		{
			new_line_data = new_line_data->next;
			fd = open(new_line_data->after_redirctor, O_WRONLY | O_CREAT | O_APPEND, 0644); // O_APPEND: the file is opened in append mode.
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		// else
			new_line_data = new_line_data->next;
	}
}

void	reset_io(void)
{
		int	stand_in;
		int	stand_out;
		stand_in = dup(STDIN_FILENO);
		stand_out = dup(STDOUT_FILENO);

		dup2(stand_in, STDIN_FILENO);
		dup2(stand_out , STDOUT_FILENO);
		close(stand_in);
		close(stand_out);
}