/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:26:24 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/19 16:43:52 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_quote(char *str)
{
	int i;
	int	single_quote;
	int	double_quote;
	
	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quote % 2 == 0)
			single_quote++;
		if (str[i] == '\"' && single_quote % 2 == 0)
			double_quote++;
		i++;
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
		return (1);
	return (0);
}

int verif_valid_operator(t_token *tokens)
{
    t_token *tmp;
    
    tmp = tokens;
    // Verification premier token ( Interdit d'etre un pipe / operateur)
    if (tmp && (tmp->type == PIPE || tmp->type == L_REDIRECT || tmp->type == R_REDIRECT
        || tmp->type == HEREDOC || tmp->type == APP_REDIRECT))
    {
        printf("Minishell : syntax error1\n");
        return (1);
    }
        
    while (tmp)
    {
        if (tmp && (tmp->type == PIPE || tmp->type == L_REDIRECT || tmp->type == R_REDIRECT
        || tmp->type == HEREDOC || tmp->type == APP_REDIRECT))
        {
            if (!tmp->next)
            {
                printf("Minishell : syntax error2\n");
                return (1);
            }
            if (tmp->next->type != WORD
                && tmp->next->type != SINGLEQUOTE && tmp->next->type != DOUBLEQUOTE)
            {
                printf("Minishell : syntax error3\n");
                    return (1);
            }
        }
        tmp = tmp->next;
    }
    return (0);
}

int verif_input(char *str)
{
    if (!str)
        return (1);
    if (str[0] == '!' && !str[1])
        return (1);
    if (str[0] == ':' && !str[1])
        return (1);
    return (0);
}