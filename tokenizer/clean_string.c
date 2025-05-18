/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:14:49 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/18 00:59:40 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Remplace le # et tout ce qu'il y a deriere dans la ligne de commande recus */
char	*ft_clean_comment(char *str)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\0')
			return (str);
		if (str[i] == '#' && check_in_quote(str, i) == 0)
			break ;
		i++;
	}
	result = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '#' && check_in_quote(str, i) == 0)
			break ;
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	free(str);
	return (result);
}
