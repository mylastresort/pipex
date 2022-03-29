/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stamim <stamim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:04:41 by stamim            #+#    #+#             */
/*   Updated: 2022/03/29 15:05:57 by stamim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	**get_env_paths(char **env)
{
	size_t	i;
	char	*paths;

	if (env != NULL)
	{
		i = 0;
		while (env[i] != NULL)
		{
			paths = ft_strnstr(env[i], "PATH=", 5);
			if (paths != NULL)
				return (ft_split(paths + 5, ':'));
			i++;
		}
		log_err(ENV_PATHS_NOT_FOUND);
	}
	else
		log_err(ENV_NOT_FOUND);
	return (NULL);
}

static int	run(const t_pipe p, t_param params)
{
	t_fd	**pipes;
	char	**paths;
	int		exit_status;

	exit_status = EXIT_FAILURE;
	paths = get_env_paths(params.envp);
	if (paths != NULL)
	{
		pipes = open_io_streams(p.size);
		if (pipes != NULL)
		{
			exit_status = run_subprocesses(paths, p, params, pipes);
			pipes = (free_arr_int(pipes, p.size), free((void *)pipes), NULL);
		}
		paths = (free_arr_string(paths), free((void *)paths), NULL);
	}
	return (exit_status);
}

static void	wait_for_heredoc(t_fd write_end, const char *const del)
{
	char		*buf;
	char		*old;
	static char	inpt[2] = {'\0', '\0'};

	buf = ft_strdup("");
	if (buf != NULL)
	{
		ft_putstr_fd(PIPE_PREFIX, STDOUT_FILENO);
		while (buf != NULL && read(STDIN_FILENO, inpt, sizeof(char) * 1) > 0)
		{
			if (*inpt == '\n')
			{
				if (ft_strcmp(del, buf) == 0)
					break ;
				write_to_child(buf, write_end);
				ft_putstr_fd(PIPE_PREFIX, STDOUT_FILENO);
				buf = (free((void *)buf), ft_strdup(""));
			}
			else
				old = ((old = buf), (buf = ft_strjoin(buf, inpt, "")),
						free((void *)old), NULL);
		}
		close(write_end);
		buf = (free((void *)buf), NULL);
	}
}

static bool	valid_main_args(const size_t ac, char *av[])
{
	size_t	i;

	if (ac < 5)
		return (log_err(LESS_ARGS), false);
	i = 0;
	while (i < ac)
	{
		if (av[i++][0] == '\0')
			return (log_err(EMPTY_ARGS), false);
	}
	return (true);
}

int	main(int ac, char *av[], char *env[])
{
	t_pipe	p;
	t_fd	heredoc_pipe[2];

	if (!valid_main_args((size_t)ac, av))
		return (EXIT_FAILURE);
	p.is_heredoc = (ft_strcmp(av[1], HEREDOC_ALERT) == 0);
	if (p.is_heredoc)
	{
		if (pipe(heredoc_pipe) == -1)
			return (failure("pipe"));
		p = (t_pipe){(size_t)(ac - 5), heredoc_pipe[R_END],
			open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0664), true};
		wait_for_heredoc(heredoc_pipe[W_END], av[2]);
	}
	else
	{
		p = (t_pipe){(size_t)(ac - 4), open(av[1], O_RDONLY),
			open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664), false};
		if (p.input == -1)
			return (failure(av[1]));
	}
	if (p.output == -1)
		return (failure(av[ac - 1]));
	return (run(p, (t_param){av + 2 + p.is_heredoc, env}));
}
