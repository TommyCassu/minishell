/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:32:45 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/19 23:26:45 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
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
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("[%d : %s ]\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}
void	ft_print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}