#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	int	pid;
	int	fds[2];

	if (!file || !argv || (type != 'w' && type != 'r'))
		return (-1);
	if (pipe(fds) < 0)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (type == 'w')
		{
			close(fds[1]);
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
		}
		else
		{
			close(fds[0]);
			dup2(fds[1], STDOUT_FILENO);
			close(fds[1]);
		}
		execvp(file, argv);
		exit(1);
	}
	if (type == 'w')
	{
		close(fds[0]);
		return (fds[1]);
	}
	else
	{
		close(fds[1]);
		return (fds[0]);
	}
}