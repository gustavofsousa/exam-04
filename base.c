#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void print_error(char *str)
{
    while (*str)
        write(2, str++, 1);
}

int cd(char **argv, int i)
{
    if (i != 2)
        return (print_error("error: cd: bad arguments"), 1);
    else if (chdir(argv[1]) == -1)
        return (print_error("bla bla"), 1);
    return 0;
}

int exec(char **argv, char **envp, int i)
{
    int status;
    int fds[2];
    int has_pipe = (argv[i] && !strcmp(argv[i], "|"));
    if (has_pipe && pipe(fds) == -1)
        return (print_error("pipe error"), 1);
    int pid = fork();
    if (!pid)
    {
        argv[i] = 0;
        if (has_pipe && (dup2(fds[1], 1) == -1 || close(fds[0]) == -1 || close(fds[1]) == -1))
            return (print_error("pipe setup error"), 1);
        execve(*argv, argv, envp);
        return (print_error("execve error"), 1);
    }
    waitpid(pid, &status, 0);
    if (has_pipe && (dup2(fds[0], 0) == -1 || close(fds[0]) == -1 || close(fds[1]) == -1))
        return (print_error("pipe cleanup error"), 1);
    return WIFEXITED(status) && WEXITSTATUS(status);
}

int main(int argc, char **argv, char **envp)
{
    int status = 0;
    int i;
    if (argc > 1)
    {
        argv++;
        while (*argv && *(argv + 1))
        {
            argv++;
            i = 0;
            while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
                i++;
            if (!strcmp(*argv, "cd"))
                status = cd(argv, i);
            else if (i)
                status = exec(argv, envp, i);
            argv += i;
        }
    }
    return status;
}

