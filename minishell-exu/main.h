#ifndef MAIN_H
#define MAIN_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define CMD 		0
# define EXEC 		1
# define RED_OUT 	2
# define RED_IN 	3
# define PIPE 		4
# define LIST 		5
# define BACK 		6
# define ARG 		7
# define OR_OP 		8
# define AND_OP 	9
# define FLE		10
# define APP		11
# define HRER_DOC		12

# define MAX_ARGS 	15

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif


typedef struct s_pipex
{
	int		end[2];
	int		status;
	int		status_1;
	int		i;
	int		indixe;
	int		outfile;
	int		infile;
	int		infile_here_doc;
	pid_t	pid1;
	pid_t	pid2;
	pid_t	a[2];
	char	*line;
	pid_t	pid;
	int		fd;
	int		save1;
	pid_t	r;
	int		count_read_out;
	int		count_read_in;
	int		count_pipe;
	int		count_here_doc;
	int		flag;
}			t_pipex;

typedef struct s_command
{
    // ls > fil.txt
    int type; //cmd pipe red arg
    char **args;
    struct s_command *next;
} t_command;

typedef struct s_path
{
	char	*path_from_envp;
	char	**mypaths;
	char	*part_path;
	char	*path;
	int		i;
}			t_path;
// link_list
int	ft_lstsize(t_command *lst);
t_command	*ft_lstlast(t_command *lst);




//excut

void	ft_excute(char **av, char **env);
char	*search_path(char *mycmdargs, char **env);
char	*without_slash(char **env, char *mycmdargs);
char	*slash(char *mycmdargs);
char	*function(char **env);


// utilis.c

int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *str);

// split+strjoin

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);

// error
void	ft_putstr_fd(char *s, int fd);
void	ft_error_2(void);
void	ft_error(char *av);
char	*ft_strchr(const char *s, int c);
int	ft_strcmp(char *s1, char *s2);

// open_file

void    ft_count_pipe(t_command *list, t_pipex *p);
void    ft_count_read_out(t_command *node, t_pipex *p);
void    ft_count_read_in(t_command *node, t_pipex *p);
void    open_infile(t_command *node, t_pipex *p);
void    open_outfile(t_command *node, t_pipex *p);

// allcmd

void	fork_pipe(t_command *node1, char **env, t_pipex *p);

// one_cmd

void    ft_onecmd(t_command *node, char **ev, t_pipex *p);
void    ft_onecmd_her(t_command *node, char **ev, t_pipex *p);


// get_next_line

char	*get_next_line(int fd);

// here_doc

void	open_here_doc(t_command *node, t_pipex *pipex);
void	here_doc(t_command *node, t_pipex *pipex);
void    ft_count_here_doc(t_command *node, t_pipex *p);

#endif
