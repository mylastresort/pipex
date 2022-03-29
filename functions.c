/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stamim <stamim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:01:05 by stamim            #+#    #+#             */
/*   Updated: 2022/03/29 14:27:53 by stamim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	redirect_io_streams(t_fd **pipes, t_pipe p, const size_t at)
{
	t_fd	in;
	t_fd	out;

	if (at != 0)
		in = pipes[at - 1][R_END];
	else
		in = p.input;
	if (dup2(in, STDIN_FILENO) == -1)
		return (failure("dup2"), false);
	if (close(in) != 0)
		return (failure("close"), false);
	if (at != p.size)
		out = pipes[at][W_END];
	else
		out = p.output;
	if (dup2(out, STDOUT_FILENO) == -1)
		return (failure("dup2"), false);
	if (close(out) != 0)
		return (failure("close"), false);
	return (true);
}

static bool	execute(char *bin, char **args, char **env)
{
	if (bin != NULL && args != NULL && env != NULL)
	{
		execve(bin, args, env);
		perror(args[0]);
	}
	if (close(STDOUT_FILENO) != 0 || close(STDIN_FILENO) != 0)
		perror("close");
	return (false);
}

static int	wait_for_last_child(pid_t child)
{
	static int	exit_status = -5;

	if (waitpid(child, &exit_status, 0) > 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	run_subprocesses(char **paths,
	const t_pipe p, const t_param params, t_fd **pipes)
{
	char			*bin;
	char			**args;
	static size_t	i = 0;
	static pid_t	child = -5;

	while (i <= p.size)
	{
		child = fork();
		if (child < 0)
			return (failure("fork"));
		if (child == 0)
		{
			if (redirect_io_streams(pipes, p, i) == false)
				return (EXIT_FAILURE);
			args = ft_split(params.argv[i], ' ');
			execute(bin = get_full_path(paths, args[0]), args, params.envp);
			bin = (free((void *)bin), NULL);
			args = (free_arr_string(args), free((void *)args), NULL);
			return (EXIT_FAILURE);
		}
		if (i != p.size && close(pipes[i][W_END]) != 0)
			return (failure("close"));
		i++;
	}
	return (wait_for_last_child(child));
}

t_fd	**open_io_streams(const size_t size)
{
	size_t	i;
	t_fd	**pipes;

	pipes = (t_fd **)malloc(size * sizeof(t_fd *));
	if (pipes == NULL)
		log_err(MALLOC_FAILURE_MSG);
	else
	{
		i = 0;
		while (i < size)
		{
			pipes[i] = (t_fd *)malloc(2 * sizeof(t_fd));
			if ((pipes[i] == NULL && log_err(MALLOC_FAILURE_MSG))
				|| (pipe(pipes[i]) == -1 && failure("pipe")))
			{
				free_arr_int(pipes, i);
				free((void *)pipes);
				pipes = NULL;
			}
			i++;
		}
	}
	return (pipes);
}
