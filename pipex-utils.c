/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:52:08 by msintas-          #+#    #+#             */
/*   Updated: 2022/12/10 21:00:44 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	free(split);
}

char	*ft_access_program(char *environ_path, char *command)
{
	char	**access_folder;
	char	*half_path;
	char	*final_path;
	int		i;

	i = 0;
	half_path = "";
	final_path = "";
	access_folder = ft_split(environ_path, ':');
	while (access_folder[i])
	{
		half_path = ft_strjoin(access_folder[i], "/");
		final_path = ft_strjoin(half_path, command);
		free(half_path);
		if (access(final_path, F_OK) == 0)
		{
			ft_free_split(access_folder);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	ft_free_split(access_folder);
	return (NULL);
}

char	*ft_env_path(char **envp)
{
	char	*env_path;
	int		i;

	env_path = "";
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			env_path = ft_strchr(envp[i], '/');
		i++;
	}
	return (env_path);
}

char	**ft_command_extract(char *cmd)
{
	char	**result;

	result = ft_split(cmd, ' ');
	return (result);
}

int	ft_infile_valid(char **argv)
{
	if (access(argv[1], R_OK | F_OK) != 0)
	{
		perror(argv[1]);
	}
	return (0);
}
