/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:22:44 by jedusser          #+#    #+#             */
/*   Updated: 2024/05/24 13:33:45 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include "libft.h"
#include "struct.h"
#include <stdio.h>
#include <readline/readline.h> 
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

// ###### INCLUDES ######


// ###### PROTO ######

char	*get_pwd(void);
size_t	ft_perror(char *err_message);
t_cmd	*parse_prompt(char *prompt);
void	echo(char *arguments);
int		exec_found(const char *dirname, char *exec_searched);
char	*check_all_dirs(char **envp, char *exec_searched);
int		exec(char **envp, char **argv, char *exec_path);


// ###### PROTO ######

char	*ft_concat_path(char **envp, char *prompt)
{
	char	*exec_path;
	
	exec_path = ft_strcat(check_all_dirs(envp, prompt), "/"); 
	exec_path = ft_strcat(exec_path, prompt);
	return (exec_path);
}
int main (int argc, char **argv, char **envp)
{
	char 	*prompt;
	char 	*exec_path;
	pid_t	pid;
	if (argc != 1)
		return (ft_perror("arguments are invalid\n"));
	if (pid > 0)
		wait(0);
	while (1)
	{
		prompt = readline(">>>");
		add_history(prompt);
		exec_path = ft_concat_path(envp, prompt);
		if (exec(envp, argv, exec_path))
			ft_perror("Execution failed.\n");
	}
	return (0);
}

