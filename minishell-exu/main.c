#include "main.h"

pid_t	fork_pipe(t_command *node1, char **env, t_pipex *pipex)
{
	int	pid;

	if (pipe(pipex->end) == -1)
		ft_error_2();
	pid = fork();
	if (pid == -1)
		ft_error_2();
	else if (pid == 0)
		all_cmd(node1, env, pipex);
	close(pipex->end[1]);
	dup2(pipex->end[0], STDIN_FILENO);
	close(pipex->end[0]);
	return (pid);
}

int main(int ac, char **av, char **ev)
{
    t_pipex	pipex;
    t_command *node1 = malloc(sizeof(t_command));
    node1->type = RED_IN;
    node1->value = "<";
    node1->args = (char *[]){"infile.txt", NULL};
    t_command *node1 = malloc(sizeof(t_command));
    node1->type = CMD;
    node1->value = "ls";
    node1->args = NULL;
    t_command *node2 = malloc(sizeof(t_command));
    node2->type = PIPE;
    node2->value = "|";
    node2->args = NULL;
    node1->next = node2;
    t_command *node3 = malloc(sizeof(t_command));
    node3->type = CMD;
    node3->value = "grep";
    node3->args = (char *[]){"f", NULL};
    node1->next->next = node3;
    t_command *node4 = malloc(sizeof(t_command));
    node4->type = PIPE;
    node4->value = "|";
    node4->args = NULL;
    node1->next->next->next = node4;
    t_command *node5 = malloc(sizeof(t_command));
    node5->type = CMD;
    node5->value = "wc";
    node5->args = NULL;
    node1->next->next->next->next = node5;
    t_command *node6 = malloc(sizeof(t_command));
    node6->type = RED_OUT;
    node6->value = ">";
    node6->args = (char *[]){"outfile.txt", NULL};
    node6->next = NULL;
    node1->next->next->next->next->next = node6;
    //int i = 0;
    //int size_list = ft_lstsize(node1);
    // printf("%d\n", size_list);
    t_command *current = node1;
    while (current != NULL)
    {
        if (current->value == "|")
            current = current->next;
        else
        {
            fork_pipe(current, ev, &pipex);
            current = current->next;
        }
    }
}