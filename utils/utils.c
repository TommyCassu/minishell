/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:32:45 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/20 23:44:04 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_only_numeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_clean(t_token *tokens)
{
	t_token	*tmp;

	if (tokens)
	{
		while (tokens)
		{
			tmp = tokens;
			tokens = tokens->next;
			free(tmp->value);
			free(tmp);
		}
	}
}

int	ft_countoperator(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			count++;
			if (count >= 2)
				return (0);
		}
		i++;
	}
	return (1);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (!path || !*path)
		return (0);
	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}
