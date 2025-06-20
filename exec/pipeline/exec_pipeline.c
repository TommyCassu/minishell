/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:43 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/20 23:04:28 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Fork a child process for a command in the pipeline */
static int	fork_cmd(t_shell *shell, t_cmd *cmd, int in_fd, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		exec_pipe_cmd(shell, cmd, in_fd, pipefd);
	return (pid);
}

/* Update pipe file descriptors for next command */
static void	update_pipe_fd(int *in_fd, int pipefd[2])
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	close(pipefd[PIPE_WRITE]);
	*in_fd = pipefd[PIPE_READ];
}

/* Wait for all child processes and return last exit status */
static int	wait_pipeline(pid_t last_pid, int n_cmds)
{
	int	status;
	int	last_status;
	int	i;

	last_status = 0;
	i = 0;
	while (i < n_cmds)
	{
		if (wait(&status) == -1)
		{
			break ;
		}
		if (wait(&status) == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
			else
				last_status = 1;
		}
		i++;
	}
	return (last_status);
}

/* Execute all commands in the pipeline */
static int	exec_loop(t_shell *shell, t_cmd *cmd, int *n_cmds, pid_t *last_pid)
{
	int		pipefd[2];
	int		in_fd;
	pid_t	curr_pid;

	in_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next_pipe && create_pipe(pipefd) == -1)
			return (1);
		curr_pid = fork_cmd(shell, cmd, in_fd, pipefd);
		if (curr_pid == -1)
			return (1);
		*last_pid = curr_pid;
		if (cmd->next_pipe)
			update_pipe_fd(&in_fd, pipefd);
		else if (in_fd != STDIN_FILENO)
			close(in_fd);
		(*n_cmds)++;
		cmd = cmd->next;
	}
	return (SUCCESS);
}

/* Main pipeline execution - fork all commands and wait */
int	exec_pipeline(t_shell *shell, t_cmd *cmd)
{
	int		n_cmds;
	pid_t	last_pid;

	n_cmds = 0;
	if (exec_loop(shell, cmd, &n_cmds, &last_pid) == GENERAL_ERROR)
		return (GENERAL_ERROR);
	return (wait_pipeline(last_pid, n_cmds));
}
