/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 09:11:37 by daflynn           #+#    #+#             */
/*   Updated: 2025/09/28 09:11:40 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_apply_redirections(t_rdr *r, char **tokens)
{
	int	last_in_fd;
	int	last_out_fd;
	int	i;
	int	fd;

	last_in_fd = -1;
	last_out_fd = -1;
	i = 0;
	if (r->heredoc_delim)
	{
		fd = handle_heredoc(r->heredoc_delim);
		if (fd == -1)
			return (0);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (0);
		}
		close(fd);
	}
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<") == 0 && tokens[i + 1])
		{
			if (last_in_fd != -1)
				close(last_in_fd);
			last_in_fd = open(tokens[i + 1], O_RDONLY);
			if (last_in_fd < 0)
			{
				perror(tokens[i + 1]);
				return (0);
			}
			i += 2;
		}
		else if (ft_strcmp(tokens[i], ">") == 0 && tokens[i + 1])
		{
			if (last_out_fd != -1)
				close(last_out_fd);
			last_out_fd = open(tokens[i + 1], O_CREAT | O_WRONLY | O_TRUNC,
					0644);
			if (last_out_fd < 0)
			{
				perror(tokens[i + 1]);
				return (0);
			}
			i += 2;
		}
		else if (ft_strcmp(tokens[i], ">>") == 0 && tokens[i + 1])
		{
			if (last_out_fd != -1)
				close(last_out_fd);
			last_out_fd = open(tokens[i + 1], O_CREAT | O_WRONLY | O_APPEND,
					0644);
			if (last_out_fd < 0)
			{
				perror(tokens[i + 1]);
				return (0);
			}
			i += 2;
		}
		else
		{
			i++;
		}
	}
	if (last_in_fd != -1)
	{
		if (dup2(last_in_fd, STDIN_FILENO) < 0)
		{
			perror("dup2 stdin");
			close(last_in_fd);
			return (0);
		}
		close(last_in_fd);
	}
	if (last_out_fd != -1)
	{
		if (dup2(last_out_fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 stdout");
			close(last_out_fd);
			return (0);
		}
		close(last_out_fd);
	}
	return (ft_remove_redirections(&tokens, 0, 0));
}
