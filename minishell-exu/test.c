#include "main.h"

int main(int ac, char **av, char **ev)
{
    (void)ac;
    (void)av;
    // (void)ev;
    int end[2];
    pid_t   pid[2];
    int fd;
    int status;
    char *buf[1024];
    ssize_t bytes_read;

    pipe(end);
    pid[0] = fork();

    if (pid[0] == 0)
    {
        close(end[0]);
        dup2(end[1], STDOUT_FILENO);
        close(end[1]);
        // execlp("/bin/ls","ls",NULL);
        ft_excute("ls",ev);
    }
    else
    {
        close(end[1]);
        dup2(end[0], STDIN_FILENO);
        close(end[0]);
        fd = open("infile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        while ((bytes_read = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
            write(fd, buf, bytes_read);
        dup2(fd, STDOUT_FILENO);
        waitpid(pid[0], &status, 0);
        close(fd);
    }

    pid[1] = fork();
    if (pid[1] == 0)
    {
        int outfile = open("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        close(end[1]);
        dup2(fd, 0);
        close(fd);
        dup2(outfile, 1);
        close(outfile);
        // execlp("usr/bin/wc", "wc", NULL);
        ft_excute("wc", ev);
    }
    else
        waitpid(pid[1], &status, 0);
}