#include "main.h"

void    ft_count_pipe(t_command *list)
{
    t_command *cur = list;
    int count = 0;
    while (cur)
    {
        if (cur->type == PIPE)
            count++;
        cur = cur->next;
    }
    return (count);
}

void    ft_count_read_out(t_command *node, t_pipex *p)
{
    t_command *cur = node;
    p->count_read_out = 0;

    while (cur)
    {
        if (cur->type == RED_OUT)
            p->count_read_out++;
        cur = cur->next;
    }
}
void    ft_count_read_in(t_command *node, t_pipex *p)
{
    t_command *cur = node;
    p->count_read_in = 0;

    while (cur)
    {
        if (cur->type == RED_OUT)
            p->count_read_in++;
        cur = cur->next;
    }
}

void    open_infile(t_command *node, t_pipex *p)
{
    
    int *fd  = malloc(sizeof(int) * p->count_read_in);
    int i = 0;
    t_command *cur = node;
    printf("count_read_in = %d\n", p->count_read_in);
    while (cur && i < p->count_read_in)
    {
        if (cur->type == RED_IN)
        {
            fd[i] = open(cur->args[0], O_RONLY, 0644);
            i++;
        }
        cur = cur->next;
    }
    p->outfile = fd[i - 1];
}
void    open_outfile(t_command *node, t_pipex *p)
{
    
    int *fd  = malloc(sizeof(int) * p->count_read_out);
    int i = 0;
    t_command *cur = node;
    printf("count_read_out = %d\n", p->count_read_out);
    while (cur && i < p->count_read_out)
    {
        if (cur->type == RED_OUT)
        {
            fd[i] = open(cur->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            i++;
        }
        cur = cur->next;
    }
    p->outfile = fd[i - 1];
}

void    ft_onecmd(t_command *node, char **ev, t_pipex *p)
{
    char *buf[1025];
    ssize_t beyt_char;
    pid_t pid;
    int end[2];
    int status;
    int flag = 0;
    while (node)
    {
        if (node->type == RED_IN)
        {
            flag = 1;
            node = node->next;
        }
        else
            break;
    }
    pipe(end);

    pid = fork();
    if (pid == 0)
    {
        printf("cmd\n");
        if (flag == 1)
        {
            close(end[0]);
            dup2(p->infile, STDIN_FILENO);
            close(p->infile);
            dup2(end[1], STDOUT_FILENO);
            close(end[1]);
            ft_excute(node->args, ev);
        }
        else
        {
            close(end[0]);
            dup2(end[1], STDOUT_FILENO);
            close(end[1]);
            ft_excute(node->args, ev);
        }
    }
    else
    {
        printf("outfile\n");
        close(end[1]);
        dup2(end[0], STDIN_FILENO);
        close(end[0]);
        while ((beyt_char = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
            write(p->outfile, buf, beyt_char);
        dup2(p->outfile, STDOUT_FILENO);
        waitpid(pid, &status, 0);
        close(p->outfile);
    }
}
pid_t	fork_pipe(t_command *node1, char **env, t_pipex *p)
{
	pid_t	pid;
	if (pipe(p->end) == -1)
		ft_error_2();
	pid = fork();
	if (pid == -1)
		ft_error_2();
	else if (pid == 0)
    {
        if (p->flag == 1)
        {
            close(p->end[0]);
            dup2(p->infile, STDIN_FILENO);
            close(p->infile);
            dup2(p->end[1], STDOUT_FILENO);
            close(p->end[1]);
            ft_excute(node1->args, env);
        }
        else if (node1->type == CMD && node1->next != NULL && node1->next->type == RED_OUT)
        {
            printf("read_out\n");
            close(p->end[0]);
            close(p->end[1]);
            dup2(p->outfile, STDOUT_FILENO);
            close(p->outfile);
            ft_excute(node1->args, env);
        }
        else if (node1->type == CMD && node1->next == NULL)
        {
            printf("STIN_OUT\n");
            ft_excute(node1->args, env);
        }
        else
        {
            printf("CMD\n");
            close(p->end[0]);
            dup2(p->end[1], STDOUT_FILENO);
            close(p->end[1]);
            ft_excute(node1->args, env);
        }
    }
        // all_cmd(node1, env, pipex);
	close(p->end[1]);
	dup2(p->end[0], STDIN_FILENO);
	close(p->end[0]);
    wait(NULL);
	return (pid);
}

void    ft_pipe(t_command *node1, char **ev, t_pipex *p)
{
    pid_t pid;
    //int status;
    t_command *cur = node1;
    p->flag = 0;
    while (cur != NULL)
    {
        if (cur->type == PIPE | cur->type == RED_IN)
        {
            if (cur->type == RED_IN)
                p->flag = 1;
            cur = cur->next;
        }
        else if (cur->type != RED_OUT && cur->type == CMD)
        {
            pid = fork_pipe(cur, ev, p);
            //waitpid(pid, &status, 0);
            cur = cur->next;
        }
        else
            cur = cur->next;
    }
    // pid_t pid[2];
    // int end[2];
    // pipex->i = 0;
    // pipe(end);
    // pid[0] = fork();

    // if (pid[0] == 0)
    // {
    //     close(end[0]);
    //     dup2(end[1], 1);
    //     close(end[1]);
    // }
    // pid[1] = fork();
    // if (pid[1] == 0)
    // {
    //     waitpid(pid[0], &status, 0);
    //     close(end[1]);
    //     dup2(end[0], 0);
    //     close(end[0]);
    //     ft_excute(*node1->next->next->args,ev);
    // }

}
//  ls | grep f | wc -l
int main(int ac, char **av, char **ev)
{
    (void)ac;
    (void)av;
    t_pipex	pipex;
    t_command *node1 = malloc(sizeof(t_command));
    node1->type = CMD;
    node1->args = (char *[]){"ls","-l", NULL};
    t_command *node2 = malloc(sizeof(t_command));
    node2->type = RED_OUT;
    node2->args =(char *[]){"a.txt", NULL};
    node1->next = node2;
    t_command *node3 = malloc(sizeof(t_command));
    node3->type = RED_OUT;
    node3->args =(char *[]){"b.txt", NULL};
    node1->next->next = node3;
    // t_command *node3 = malloc(sizeof(t_command));
    // node3->type = CMD;
    // node3->args = (char *[]){"grep", "t", NULL};
    // //node3->next = NULL;
    // node1->next->next = node3;
    // t_command *node4 = malloc(sizeof(t_command));
    // node4->type = PIPE;
    // node4->args = NULL;
    // //node4->next = NULL;
    // node1->next->next->next = node4;
    // t_command *node5 = malloc(sizeof(t_command));
    // node5->type = CMD;
    // node5->args = (char *[]){"ls", "-l", NULL};
    // node5->next = NULL;
    // node1->next->next->next->next = node5;
    // t_command *node6 = malloc(sizeof(t_command));
    // node6->type = RED_OUT;
    // node6->args = (char *[]){"outfile.txt", NULL};
    // node1->next->next->next->next->next = node6;
    // t_command *node7 = malloc(sizeof(t_command));
    // node7->type = RED_OUT;
    // node7->args = (char *[]){"c",NULL};
    // node1->next->next->next->next->next->next = node7;
    // t_command *node8 = malloc(sizeof(t_command));
    // node8->type = RED_OUT;
    // node8->args = (char *[]){"d.txt", NULL};
    // node8->next = NULL;
    // node1->next->next->next->next->next->next->next = node8;
    // t_command *node9 = malloc(sizeof(t_command));
    // node9->type = RED_OUT;
    // node9->args = (char *[]){"e.txt", NULL};
    // node9->next = NULL;
    // node1->next->next->next->next->next->next->next->next = node9;


    ft_count_pipe(node1);
    ft_count_read_out(node1, &pipex);
    ft_count_read_in(node1, &pipex);
    open_infile(node1, &pipex);
    open_outfile(node1, &pipex);
    ft_pipe(node1, ev, &pipex);
    // ft_onecmd(node1, ev, &pipex);

}