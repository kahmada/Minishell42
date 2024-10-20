/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:27:16 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/18 12:25:37 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_envp(t_env **envp, char *key, char *value)
{
	t_env	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		else
			add_env(envp, key, value);
		tmp = tmp->next;
	}
}

char	*get_home(t_env **envp)
{
	t_env	*current;

	current = *envp;
	while (current)
	{
		if (ft_strcmp(current->key, "HOME") == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*get_home_path(t_command *cmd, t_env **envp)
{
	char	*path;

	path = get_home(envp);
	if (!path)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		cmd->ex = manage_exit_status(1, 1);
		free(cmd->ex);
		return (NULL);
	}
	return (path);
}

void	bult_cd(t_command *cmd, t_env **envp)
{
	char	*path;
	char	*oldpath;
	char	*new_path;

	oldpath = getcwd(NULL, 0);
	if (cmd->args[1] == NULL)
	{
		path = get_home_path(cmd, envp);
		if (!path)
			return ;
	}
	else
		path = cmd->args[1];
	cmd->ret = chdir(path);
	if (cmd->ret == -1)
	{
		perror("minishell");
		free(manage_exit_status(1, 1));
		return ;
	}
	free(manage_exit_status(0, 1));
	update_envp(envp, "OLDPWD", oldpath);
	new_path = getcwd(NULL, 0);
	update_envp(envp, "PWD", new_path);
	(free(new_path), free(oldpath));
}
