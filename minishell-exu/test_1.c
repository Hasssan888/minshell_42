#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int fd[2];
    pid_t pid;

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // Child process
        // Close the read end of the pipe
        close(fd[0]);

        // Redirect the standard output to the write end of the pipe
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        // Execute the command
        execlp("ls", "ls", NULL);
        perror("execlp");
        return 1;
    } else { // Parent process
        // Close the write end of the pipe
        close(fd[1]);

        // Open a file for writing
        int output_fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd == -1) {
            perror("open");
            return 1;
        }

        // Redirect the read end of the pipe to the output file
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        // Copy the output from the pipe to the file
        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
            if (write(output_fd, buffer, bytes_read) != bytes_read) {
                perror("write");
                return 1;
            }
        }

        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);

        close(output_fd);
    }

    return 0;
}