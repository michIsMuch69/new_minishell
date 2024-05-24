/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:22:44 by jedusser          #+#    #+#             */
/*   Updated: 2024/05/24 11:14:32 by jedusser         ###   ########.fr       */
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

// ###### PROTO ######

int main (int argc, char **argv, char **envp)
{

	//char	*exec_searched = "ls";
	char 	*prompt;
	char 	*exec_path;
	if (argc != 1)
		return (ft_perror("arguments are invalid\n"));
	while (1)
	{
		prompt = readline(">>>");
		add_history(prompt);
		exec_path = ft_strcat(check_all_dirs(envp, prompt), "/"); 
		exec_path = ft_strcat(exec_path, prompt);
		if (exec_path)
		{
			printf("exec path is : %s\n", exec_path);
			execve(exec_path, argv, envp);
			free(exec_path);

		}
		free(prompt);
	 }
	return (0);
}

