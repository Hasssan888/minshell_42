#include "main.h"

// void    ft_pipe(t_command *node1, char **ev, t_pipex *p)
// {
//     //pid_t pid;
//     //int status;
//     t_command *cur = node1;
//     p->flag = 0;
//     while (cur != NULL)
//     {
//         if (cur->type == PIPE || cur->type == RED_IN)
//         {
//             if (cur->type == RED_IN)
//                 p->flag = 1;
//             cur = cur->next;
//         }
//         else if (cur->type != RED_OUT && cur->type == CMD && cur->type == HERD)
//         {
//             if (cur->type == HERD)
//                 here_doc(cur, p);
//             fork_pipe(cur, ev, p);
//             //waitpid(pid, &status, 0);
//             p->flag = 0;
//             cur = cur->next;
//         }
//         else
//             cur = cur->next;
//     }
// }
int main(int ac, char **av, char **ev)
{
    (void)ac;
    (void)av;
    t_pipex	pipex;
    t_command *node1 = malloc(sizeof(t_command));
    node1->type = CMD;
    node1->args = (char *[]){"cat", NULL};
    t_command *node2 = malloc(sizeof(t_command));
    node2->type = HRER_DOC;
    node2->args =(char *[]){"limt", NULL};
    node1->next = node2;
    // t_command *node3 = malloc(sizeof(t_command));
    // node3->type = PIPE;
    // node3->args = NULL;
    // node1->next->next = node3;
    // t_command *node4 = malloc(sizeof(t_command));
    // node4->type = CMD;
    // node4->args = (char *[]){"wc", "-l", NULL};
    // node1->next->next->next = node4;
    //ft_pipe(node1, ev, &pipex);

    open_here_doc(node1, &pipex);
    pipex.infile_here_doc = open("file_here_doc.txt", O_RDONLY, 0644);

    dup2(pipex.infile_here_doc, 0);
    close(pipex.infile_here_doc);
    ft_excute(node1->args, ev);
}
