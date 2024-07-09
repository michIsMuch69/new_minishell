/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 08:27:25 by jedusser          #+#    #+#             */
/*   Updated: 2024/07/09 10:25:53 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_cd(char **args, char **env)
{
   	char	cwd[1024];
    char	*home = NULL;
    char	*oldpwd = NULL;
    char	*new_dir = NULL;
	char	*temp;

	temp = getcwd(cwd, sizeof(cwd));
    if (!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        if (ft_getenv("HOME", env, &home) != 0)
            return (ft_putstr_fd("cd: HOME not set\n", 2), -1);
        new_dir = home;
    }
    else if (ft_strcmp(args[1], "-") == 0)
    {
        if (ft_getenv("OLDPWD", env, &oldpwd) != 0)
            return (ft_putstr_fd("cd: OLDPWD not set\n", 2), -1);
        new_dir = oldpwd;
    }
    //  ft_strncmp;
	else if (ft_strcmp(args[1], "..") == 0)
		new_dir = "..";
    else
        new_dir = args[1];
    if (chdir(new_dir) != 0)
        return (perror("cd"), free(home), free(oldpwd), -1);
	set_env("OLDPWD", temp, env);
	temp = getcwd(cwd, sizeof(cwd) * sizeof(char));
    if (temp != NULL)
	    set_env("PWD", temp, env);
    else
        perror("getcwd");
	free(home);
    free(oldpwd);
    return 0;
}

int	ft_export(char **args, char **env)
{
    char	*key;
    char	*value;

    value = args[3];
    key = args[1];
    if (!args[1])
    {
        ft_env(env);
        return 0;
    }
    if (args[2] && ft_strcmp(args[2], "=") == 0 && value)
        set_env(key, value, env);
    else
    {
        ft_putstr_fd("export: invalid format\n", 2);
        return (1);
    }
    return 0;
}

int ft_unset(char *var, t_table *env)
{
    int i;
    int j;
    int var_len;

    i = 0;
    j = 0;
    var_len =  ft_strlen(var);

    while (env->tab[i])
    {
        if (ft_strncmp(env->tab[i], var, var_len) == 0)
        {
            free(env->tab[i]);
            j = i;
            while (env->tab[j])
            {
                env->tab[j] = env->tab[j + 1];
                j++;
            }
            env->size--;
    		printf("size of  key : %ld\n", ft_strlen(var));
            printf("env var set : %s\n", env->tab[i]);
            return (1);
        }
		else
			return (-1);
        i++;
    }
    env->tab[i + 1] = NULL;
    printf("size of  key added : %ld\n", ft_strlen(env->tab[i]));
    printf("env var added : %s\n", env->tab[i]);
    return (0);
}

void	ft_exit(t_data *data, int tab_size, int last_status)
{
	int	status;

	printf("My exit\n");
	status = 0;
	if (data->args.tab[1])
	{
		if (is_numeric_str(data->args.tab[1]) == 0)
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			status = 255;
		}
		else
		{
			status = ft_atoi(data->args.tab[1]);
			status = status % 256;
			if (status < 0)
				status += 256;
			printf("Status in ft_exit = %d\n", status);
		}
	}
	else
	{
		printf("Status in ft_exit no agrs = %d\n", status);
		status = last_status;
	}
	free_struct(data, tab_size);
	exit(status);
}

//close_fds --> input output files.
//free_pipes -->  close pipes, free pipe_ptr.
