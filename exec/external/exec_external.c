/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:33 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/28 22:25:05 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void print_error(const char *path, const char *msg)
{
    write(2, path, ft_strlen(path));
    write(2, ": ", 2);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
}

/* Replace current process with new program */
static void	exec_cmd(t_cmd *cmd, char *path)
{
	struct stat st;
	
	if (stat(path, &st) == -1)
    {
        print_error(path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(st.st_mode))
    {
        print_error(path, "Is a directory");
        exit(EXIT_FAILURE);
    }
	execve(path, cmd->arguments, environ);
	perror("execve");
	exit(EXEC_ERROR);
}

/* Child process: setup redirections and execute */
static void	exec_child(t_cmd *cmd, char *path)
{
	if (setup_redirs(cmd) == -1)
		exit(GENERAL_ERROR);
	exec_cmd(cmd, path);
}

/* Wait for child process and get exit status */
static int	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (GENERAL_ERROR);
}

/* Execute external command by forking and calling execve */
int	exec_external(t_cmd *cmd)
{
	pid_t	pid;
	char	*path;

	path = find_cmd_path(cmd->arguments[0]);
	if (!path)
	{
		print_cmd_not_found(cmd->arguments[0]);
		return (CMD_NOT_FOUND);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return (GENERAL_ERROR);
	}
	if (pid == 0)
		exec_child(cmd, path);
	free(path);
	return (wait_child(pid));
}
