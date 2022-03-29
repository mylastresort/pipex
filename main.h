/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stamim <stamim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:04:35 by stamim            #+#    #+#             */
/*   Updated: 2022/03/29 09:02:04 by stamim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define R_END 0
# define W_END 1
# define HEREDOC_ALERT "here_doc"
# define PIPE_PREFIX "pipe heredoc>"
# define COMMAND_NOT_FOUND "command not found"
# define MALLOC_FAILURE_MSG "malloc had failed."
# define LESS_ARGS "main arguments are less than 5 !"
# define EMPTY_ARGS "main arguments cannot be empty !"
# define ENV_PATHS_NOT_FOUND "we could not find the PATH variable in env."
# define ENV_NOT_FOUND "the command binary is wrong, the env variable is wrong."

typedef int	t_fd;
typedef struct s_param {
	char	**argv;
	char	**envp;
}	t_param;
typedef struct s_pipe {
	size_t	size;
	t_fd	input;
	t_fd	output;
	bool	is_heredoc;
}	t_pipe;

int		run_subprocesses(char **paths, const t_pipe p,
			t_param params, t_fd **pipes);
t_fd	**open_io_streams(const size_t size);
void	free_arr_string(char **arr);
void	free_arr_int(t_fd **arr, size_t end);
char	*ft_strnstr(
			const char *const haystack, const char *const needle, size_t len);
size_t	log_err(const char *const err);
char	**ft_split(char const *s, const char c);
char	*ft_strdup(const char *const string);
size_t	ft_putstr_fd(const char *const string, const t_fd fd);
int		ft_strcmp(const char *const s1, const char *const s2);
char	*ft_strjoin(char const *const s1,
			char const *const s2, const char *const seperator);
int		write_to_child(char *line, t_fd write_end);
int		failure(const char *const err);
char	*get_full_path(char *paths[], const char *const command);
void	free_arr_int(t_fd **arr, size_t end);
size_t	ft_putstr_fd(const char *const string, const t_fd fd);

#endif
