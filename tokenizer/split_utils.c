/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 00:41:40 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/15 00:41:53 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
}

int	is_quote(const char *str, int i)
{
	char	quote;

	quote = str[i];
	
	i++;
	while(str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}