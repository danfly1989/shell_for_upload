/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:02:33 by daflynn           #+#    #+#             */
/*   Updated: 2025/09/13 20:02:39 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "minishell: %s: No such file or directory\n", file);
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 in");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	ft_redir_out(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		if (errno == EACCES)
		{
			fprintf(stderr, "minishell: %s: Permission denied\n", file);
		}
		else
		{
			perror(file);
		}
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 out");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	ft_redir_append(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (perror(file), 0);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror("dup2 append"), 0);
	close(fd);
	return (1);
}
