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

# define MAX_ARGS 	15

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
}			t_pipex;

typedef struct s_command
{
    int type; //cmd pipe red arg
   // char *file;
    char *value;
    char **args;
    struct s_command *next;
} t_command;


// link_list
int	ft_lstsize(t_command *lst);


//allcmd

void	all_cmd(t_command *node1, char **env, t_pipex *pipex)

#endif