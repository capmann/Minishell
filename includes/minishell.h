/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:35:06 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/05 22:53:11 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700
# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>

# define SIMPLE_QUOTE 39
# define DOUBLE_QUOTE 34

# define SIGINT  2
# define SIGQUIT 3

extern pid_t	g_exit_code;

typedef struct s_data {
	char			**cmd;
	char			*path;
	int				redirect;
	int				redir_stdin;
	int				redir_stdout;
	char			*infile;
	char			*outfile;
	int				heredoc;
	int				nb_args;
	pid_t			pid;
	int				std_in;
	int				std_out;
	struct s_data	*next;
}				t_data;

typedef struct s_split {
	char	*tmp;
	char	*tmptmp;
	int		n_word;
	char	**res;
	int		j;
}				t_split;

//chained list to manipulate env variables
typedef struct s_env {
	char			*env_var;
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_list
{
	t_env	*first;
	t_data	*prems;
	int		pipe;
	int		prev_pdes;
	int		stdin;
	int		stdout;
}		t_list;

// parsing functions
char	**ft_split(const char *s, char c, int start, int mode);
int		ft_cinset(const char c, const char *set);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**get_command(char *cmd, t_data *data);
t_data	*parsing(char *cmd, t_list *list);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcat(char *s1, char *s2);
t_data	*create_datas(char *cmd, int num, t_list *list);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(char *s, int c);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		check_files(char *cmd);
int		get_redirect(char *cmd, t_data *data);
int		check_in_quote(char *cmd, char c, int index);
void	redirection_files(char *cmd, t_data *data);
t_data	*set_quote(char *cmd, t_data *data);
int		ft_isascii(int c);
char	*verify_path(t_data *data);
char	*clear_tab(char *str);
char	*parsing_quotes(char *s);
int		count_quotes(char *s);
int		ft_search_index(const char *s, int c);
char	*ft_substr_free(char *s, unsigned int start, size_t len);
int		cmd_digit(char *cmd);
t_split	*mini_split(t_split *split, char c, int mode, int quote);
char	*extract_word(const char *s, char c, int mode);
char	*move_tmp(char *tmp, int quote);
int		handling_quotes(char *s, int n, int mode);
int		check_quote(char *tab, int pos, char c);
int		skip_n(char *s);

//lexical analysis functions
int		is_quote(char c);
void	skip_quotes(t_data *data, int arg);
void	quotes_skip(t_list *list);
int		is_closed_quotes(char *cmd, int index);
int		ft_atoi(const char *str);
void	get_expansion(t_data *data, t_list *list);
char	*find_env_var(t_list *list, char *str);
char	*remove_braces(char *d, t_list *list);
char	*cat_expansion(char *cmd, t_list *list);
int		ft_isalnum(int c);
int		skip_redirect(char *cmd);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_cinset(const char c, const char *set);
size_t	get_n_word(const char *s, char c, int start, int mode);
size_t	get_n_arg(char *s, char *c, int start);
int		verify_quotes(char *cmd);
t_data	*get_redirect_files(char *cmd, t_data *data, int infile, int outfile);
char	*skip_dble_quotes(char *str);
t_data	*one_data(char *cmd, t_data **data, t_list *list, int mode);
int		count_cmds(char *cmd);
void	ft_show_prompt(void);
int		is_in_quote(char *str, char quote, char c);
int		return_get_in_quote(char *str);
int		quote_pos(char *cmd, char c, int index);
int		char_in_quote(char *cmd, char c, int index);
char	*skip_spaces(char *cmd);
char	*quote_mgt(const char *s, int end);

//builtins functions
void	my_echo(t_data *data);
void	my_cd(t_data *data, t_list *list);
void	my_pwd(void);
void	my_env(t_list *list);
void	my_export(t_list *list, t_data *data);
void	my_export_arg(t_data *data, t_list *list);
void	my_unset(t_list *list, t_data *data);
void	my_exit(t_list *list, t_data *data);
void	run_builtin(t_data *data, t_list *list);
int		is_builtin(t_data *data, t_list *list);
char	*ft_itoa(int n);
t_env	*create_env_var(char *tmp, char *cmd, t_env *env, t_list *list);
void	check_var_exist(t_list *list, char *tmp, char *cmd);
void	unset_var(t_list *list, t_env *env, char *cmd, t_env *tmp);
char	*join_pieces(char **b, char *c, char *var);
int		check_biggest(char *s1, char *s2);
void	print_echo(char *cmd);
char	*ft_strchr_exp(const char *s, int c);
int		is_digit_arg(char *s);
void	mini_echo(t_data *data);

//env management
t_list	*init(char **envp);
t_list	*swap(t_list *list);
int		is_sorted(t_list *list);
void	duplicate_env(char **env, t_list *list);
void	ft_free_list(t_list *liste);
void	print_export(t_list *list);
void	update_pwd(t_list *list);
char	*cd_args(t_list *list, char *str);

//redirections
void	run_redir(t_data *args);
char	*gets_path(t_list *list, t_data *data);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*heredoc(t_data *data);
void	mini_heredoc(t_data *data, char *doc, int *pdes);
char	*last_redir(char *cmd, char c);
int		check_file_exist(char *file);
int		count_redir(char *cmd, char c);
void	open_files(char *cmd, t_data *data);
int		redirect_tab(int *redirect);
int		close_and_open_files(char *tmp, int i, int k, t_data *data);
void	ignore_redirect(t_list *list);
void	orga_data(t_list *list);

//free functions
void	free_malloc(char **cmd, char *path, int mode);
void	secure_free(void **ptr);
void	ft_free_data(t_list *liste);

// signal functions
void	sig_backslash(int signum);
void	sig_quit(int signum);
void	set_sigaction(int enable);
void	*ft_memset(void *b, int c, size_t len);
int		handle_EOT(char *cmd);
int		verify_cmd(char *cmd);
void	disable_signals(int fork);
void	sigign(int signum);
void	sig_heredoc(int signum);
void	signals_heredoc(int fork);
void	inthandler2(int sig);

//pipe implementation
void	run_shell(t_list *list);
pid_t	run_pipe(t_data *data, t_list *list, int *pdes);
void	run_heredoc(t_data *data);
int		null_pipe(char *cmd);

//errors
int		invalid_identifier(t_data *data, t_list *list, int i);
int		syntax_error(char *cmd);
int		perm_denied(char *cmd);
int		check_errors(char *cmd, t_list *list);
int		error_code(int exit_code, int error_code, t_list *list);
int		check_parsing(char *cmd, t_list *list);
int		check_valid_cmd(char *cmd, t_data *data, t_list *list);
int		pipe_errors(char *cmd, int i);
int		test_file(char *tmp, int i, int k);
int		check_null_cmd(t_data *data, int i);
int		file_test(char *tmp, int i, int k);
char	*access_path(char **tmp_path, char *tmp, t_data *data);

//execution
void	exec(t_list *list, t_data *data);
void	child_process(t_list *list, t_data *data, int *pdes);
void	parent_process(t_list *list, int *pdes);
void	execute_cmd(t_list *list, t_data *data);

//debug
void	print_data(t_data *data);
void	print_cmd(char **cmd);

#endif
