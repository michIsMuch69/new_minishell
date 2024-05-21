#include <errno.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <curses.h>
#include <term.h>
extern char PC;
extern char * UP;
extern char * BC;
extern unsigned ospeed;

int main (int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (0);
	
	// int getval = tgetent(NULL, getenv("TERM"));

	// if (getval <= 0)
	// 	perror(NULL);















	// int 	i = 0;
	// int 	val = 0;
	// pid_t	pid;
	// DIR		*dir;
	// struct dirent	*ry;
	// int fd = open("./file.txt", O_RDWR);
	// printf("FD = %d\n\n", fd);
	// char *path_fd = ttyname(fd);
	// // if (!path_fd)
	// // 	return (perror("error ->"), 0);
	// printf("getenv = %s\n", getenv("TERM"));
	// int				tty = isatty(fd);
	// printf("TTY == %d, path = %s\n", tty, path_fd);
	// close(fd);
	// printf("TTY == %d\n", tty);
	// pid = fork();
	// if (pid == 0)
	// 	val = execve("/usr/bin/ls", argv, envp);
	// if (pid > 0)
	// 	waitpid(pid, &i, 0);
	// printf("val = %d\n", val);
	// dir = opendir("./");
	// ry = readdir(dir);
	// while (ry)
	// {
	// 	printf("inode nb : %ld, gap for next dirent = %ld, recording length : %d, file type : '%c', filename : '%s'\n", \
	// 			ry->d_ino, ry->d_off, ry->d_reclen, ry->d_type, ry->d_name);
	// 	ry = readdir(dir);
	// }
	// if (closedir(dir))
	// 	perror(NULL);
	return (0);
	
}