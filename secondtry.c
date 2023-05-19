#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int	ft_putstr_fd2(char *str, char * arg)
{
	while (*str)
		write (2, str++, 1);
	if (arg)
		while (*arg)
			write (2, arg++, 1);
	write (2, "\n", 1);
	return (1);
}

int	ft_exec(char **argv, int i, int tmp_fd, char **envp)
{
	argv[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(argv[0], argv, envp);
	return (ft_putstr_fd2("Cannon execute command: ", argv[0]));
}


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	int i =0;
	int	fd[2];
	int	tmp_fd = dup(STDIN_FILENO);

	while (argv[i] && argv[1 + i])
	{
		argv = &argv[i + 1];
		i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if (strcmp(argv[0], "cd") == 0)
		{
			if (i != 2)
			{
				ft_putstr(Wrong)
			elseif (chdir(Argv[1]) == -1)
				ft_putstr_(swing);
			}
			else if (i != 0 (argv[i] == NULL || strcmp(virgula)))
			{

				if (fork() == )
				{
					if (ft_exec(argv, i, tmp_fd, i))
						return (1);
				}
				else
				{
					close(tmp_fd);
					while (waitpid(-1, NULL, WUNTRACED) == -1)
						;
					tmp = dup(STDIN_FILENO)
				}
			}
			else if (i != 0 (strcmp(pipe)))
			{
				pipe(fd);
				if (fork() == 0)
				{
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
					close(fd[0]);
					if (ft_exec())
						return (1);
				}
				else
				{
					close(fd[1]);
					close(tmp_fd);
					tmp_fd = fd[0]);
				}
			}
		}
	}
	close(tmp_fd);
	return (0);
}
