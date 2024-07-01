#include "main.h"


void    ft_pipe(t_command *node1, char **ev, t_pipex *p)
{
    //pid_t pid;
    //int status;
    t_command *cur = node1;
    p->flag = 0;
    if (p->count_here_doc > 0)
        open_here_doc(node1, p);
    while (cur != NULL)
    {
        if (cur->type == PIPE || cur->type == RED_IN || cur->type == HRER_DOC)
        {
            if (cur->type == RED_IN)
                p->flag = 1;
            cur = cur->next;
        }
        else if (cur->type != RED_OUT && cur->type == CMD)
        {
            if (ft_strcmp(cur->args[0], "cat") == 0 && cur->next->type == HRER_DOC)
            {
                printf("flag == 2\n");
                p->flag = 2;
            }
            fork_pipe(cur, ev, p);
            //waitpid(pid, &status, 0);
            p->flag = 0;
            cur = cur->next;
        }
        else
            cur = cur->next;
    }
}
//  ls | grep f | wc -l
int main(int ac, char **av, char **ev)
{
    (void)ac;
    (void)av;
    t_pipex	pipex;
    t_command *node1 = malloc(sizeof(t_command));
    node1->type = CMD;
    node1->args =(char *[]){"cat", NULL};
    node1->next = NULL;
    t_command *node2 = malloc(sizeof(t_command));
    node2->type = HRER_DOC;
    node2->args =(char *[]){"lop", NULL};
    node1->next = node2;
    t_command *node3 = malloc(sizeof(t_command));
    node3->type = PIPE;
    node3->args = NULL;
    // node3->args = NULL;
    node1->next->next = node3;
    t_command *node4 = malloc(sizeof(t_command));
    node4->type = CMD;
    node4->args = (char *[]){"grep", "l", NULL};
    node1->next->next->next = node4;
    // t_command *node6 = malloc(sizeof(t_command));
    // node6->type = PIPE;
    // node6->args = NULL;
    // node1->next->next->next->next->next = node6;
    // t_command *node7 = malloc(sizeof(t_command));
    // node7->type = CMD;
    // node7->args =  (char *[]) {"wc", "-l", NULL};
    // node1->next->next->next->next->next->next = node7;
    // t_command *node8 = malloc(sizeof(t_command));
    // node8->type = CMD;
    // node8->args = (char *[]){"wc", NULL};
    // node1->next->next->next->next->next->next->next = node8;
    // t_command *node9 = malloc(sizeof(t_command));
    // node9->type = RED_OUT;
    // node9->args = (char *[]){"y.txt", NULL};
    // node1->next->next->next->next->next->next->next->next = node9;
    // t_command *node10 = malloc(sizeof(t_command));
    // node10->type = RED_OUT;
    // node10->args = (char *[]){"x.txt", NULL};
    // node1->next->next->next->next->next->next->next->next->next = node10;


    ft_count_pipe(node1, &pipex);
    printf("count_pipe = %d\n",pipex.count_pipe);
    ft_count_read_out(node1, &pipex);
    ft_count_read_in(node1, &pipex);
    ft_count_here_doc(node1, &pipex);
    open_infile(node1, &pipex);
    open_outfile(node1, &pipex);
    //open_herdoc(node1, &pipex);
    if (pipex.count_pipe == 0 && pipex.count_read_out == 0)
    {
        if (pipex.count_here_doc == 0 && pipex.count_read_in == 0)
            ft_excute(node1->args, ev);
        else if (pipex.count_here_doc == 0 && pipex.count_read_in != 0)
        {
            printf("rin\n");
            while (node1)
            {
                if (node1->type == RED_IN)
                    node1 = node1->next;
                else
                    break;
            }
            dup2(pipex.infile, 0);
            close(pipex.infile);
            ft_excute(node1->args, ev);
        }
        else
        {
            printf("not\n");
            open_here_doc(node1, &pipex);
            pipex.infile_here_doc = open("file_here_doc.txt", O_RDONLY, 0644);
            dup2(pipex.infile_here_doc, 0);
            close(pipex.infile_here_doc);
            ft_excute(node1->args, ev);
            // unlink("file_here_doc.txt");
            //wait(NULL);
        }

    }
    else if (pipex.count_pipe == 0 && pipex.count_read_out != 0)
    {
        if (pipex.count_here_doc != 0)
        {
            open_here_doc(node1, &pipex);
            ft_onecmd(node1, ev, &pipex);
           // wait(NULL);
            unlink("file_here_doc.txt");
        }
        else
            ft_onecmd(node1, ev, &pipex);
    }
    else
    {
        printf("existing pipe\n");
        ft_pipe(node1, ev, &pipex);
    }

}