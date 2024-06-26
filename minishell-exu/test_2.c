#include "main.h"

int main(int ac, char **av, char **ev)
{
    (void)ac;
    (void)av;
    int end[2];
    pid_t   pid[2];
    int fd;
    int status;

    pipe(end);
    pid[0] = fork();

    if (pid[0] == 0)
    {
        close(end[0]);
        dup2(end[1], STDOUT_FILENO);
        close(end[1]);
        ft_excute("ls", ev);
    }
    else
        waitpid(pid[0], &status, 0);


    pid[1] = fork();
    if (pid[1] == 0)
    {
        fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        close(end[1]);
        dup2(end[0], STDIN_FILENO);
        close(end[0]);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        ft_excute("wc", ev);
    }
   // waitpid(pid[1], &status, 0);

}