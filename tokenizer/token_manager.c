/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:16:18 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/16 00:38:07 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(void *content)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = content;
	token->next = NULL;
	return (token);
}

void	ft_lstadd_backs(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
    last = *tokens;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

void	add_type(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->value[0] == '>')
			tokens->type = OPERATION;
		else if (tokens->value[0] == '|')
			tokens->type = PIPE;
		tokens = tokens->next;
	}
}
// faire la fonction qui free la liste


