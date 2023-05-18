#include "microshell.h"
#include <stdio.h>

void	print_error(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int	ft_cd(char **argv, int i)
{
	int	nxt;

	nxt = i;
	while (argv[nxt] != NULL && (strcmp(argv[nxt], ";") != 0) && (strcmp(argv[nxt], "|") != 0))
	{
		nxt++;
	}
	if (nxt - i != 2)
	{
		print_error("error: cd: bad arguments\n");
		exit (1);
	}
	else if (chdir(argv[i + 1]) == -1)
	{
		print_error("error: cd: cannot change directory to ");
		print_error(argv[i + 1]);
		print_error("\n");
		exit (1);
	}
	return (nxt - 1);
}

int	question_has_pipe(char **argv, int i)
{
	int di;

	di = i;
	while (argv[di] && strcmp(argv[di], ";") != 0)
	{
		if (!strcmp(argv[di], "|"))
			return (1);
		di++;
	}
	return 0;
}

int	ft_exe(char **argv, int i, char **envp)
{
	int	fildes[2] ;
	int	has_pipe;
	int	pid;
	int	status;

	has_pipe = question_has_pipe(argv, i);
	if (has_pipe == 1)
		pipe(fildes);
	pid = fork();
	if (pid == 0)
	{
		if (has_pipe && (dup2(fildes[1], 1) == -1 || close(fildes[0]) == -1 || close(fildes[1] == -1)))
			exit (1);
		execve(argv[i], &argv[i], envp);
		exit (1);
	}
	waitpid(pid, &status, 0);
	if (has_pipe && (dup2(fildes[0], 0) == -1 || close(fildes[0]) == -1 || close(fildes[1] == -1)))
		exit (1);
	while (argv[i] != NULL && (strcmp(argv[i], ";") != 0) && (strcmp(argv[i], "|") != 0))
		i++;
	return (i);

}

int	main (int argc, char **argv, char **envp)
{
	int	i;

	if (argc == 1)
		return (0);
	i = 0;
	while (argv[i] && argv[i + 1])
	{
		i++;
		if (strcmp(argv[i], ";") != 0)
		{
			if (!strcmp(argv[i], "cd"))
				i += ft_cd(argv, i);
			else
				i = ft_exe(argv, i, envp);
		}
	}
	return (0);
}
