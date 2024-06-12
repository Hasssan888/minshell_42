#include "main.h"

void	infile(t_pipex *pipex)
{
	close(pipex->end[0]);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->infile);
	dup2(pipex->end[1], STDOUT_FILENO);
	close(pipex->end[1]);
}

// char	*ft_check_r(t_command *node)
// {
// 	t_command *check_r = node->next;
// 	while (check_r)
// 	{
// 		if(check_r->type != RED_OUT)
// 			break;
// 		check_r = check_r->next;
// 	}
// 	return(check_r->file);
// }

// void	outfile(t_command *node, t_pipex *pipex)
// {
// 	if (ft_lstlast(node)->type == RED_OUT)
// 		pipex->outfile = open(ft_lstlast(node)->file, O_RDWR | O_TRUNC | O_CREAT, 0644);
// 	close(pipex->end[0]);
// 	close(pipex->end[1]);
// 	if (pipex->outfile == -1)
// 	{
// 		perror("outfile fail");
// 		exit(-1);
// 	}
// 	dup2(pipex->outfile, STDOUT_FILENO);
// 	close(pipex->outfile);
// }
//< infile	ls | grep f | wc -l > outfile
void	all_cmd(t_command *node1, char **env, t_pipex *pipex)
{
	// printf("allcmd >> i = %d\n", pipex->i);
	// printf("type = %d\n", node1->type);

	// if (pipex->i == 1)
	// {
	// 	printf("infile\n");
	// 	infile(pipex);
	// 	//printf("infile >> i = %d\n", pipex->i);
	// }
	// else if (node1->next->type == RED_OUT)
	// {

	// 	printf("outfile = %s\n", node1->next->file);
	// 	outfile(node1, pipex);
	// }
	// else
	// {
		close(pipex->end[0]);
		dup2(pipex->end[1], STDOUT_FILENO);
		close(pipex->end[1]);
	// }
	ft_excute(*node1->args, env);
}