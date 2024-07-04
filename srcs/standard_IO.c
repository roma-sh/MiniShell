/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_IO.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 07:00:37 by rshatra           #+#    #+#             */
/*   Updated: 2024/07/03 08:20:00 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	standard_IO(t_line_data *line_data)
{
	int	fd;
	t_line_data *new_line_data;

	new_line_data = line_data;
	while (new_line_data != NULL)
	{
		if (new_line_data->redirctor != NULL)
		{
			if (!ft_strcmp("<", new_line_data->redirctor))
			{
				new_line_data = new_line_data->next;
				fd = open(new_line_data->after_redirctor, O_RDONLY);
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			else if (!ft_strcmp(">", new_line_data->redirctor))
			{
				new_line_data = new_line_data->next;
				fd = open(new_line_data->after_redirctor, O_WRONLY | O_CREAT | O_TRUNC, 0644);	//O_WRONLY: the file is opened for writing only.
																						// O_CREAT: to create the file if it does not already exist.
																						// O_TRUNC: clearing any existing content in the file.
																						// 0644: the file permission.
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			else if (!ft_strcmp(">>", new_line_data->redirctor))
			{
				new_line_data = new_line_data->next;
				fd = open(new_line_data->after_redirctor, O_WRONLY | O_CREAT | O_APPEND, 0644); // O_APPEND: the file is opened in append mode.
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			// to be continued:
			// else if (!ft_strcmp(new_line_data->redirctor, "<<"))
			// {
			// }
		}
		else
			new_line_data = new_line_data->next;
	}
}
void	reset_IO(void)
{
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
}