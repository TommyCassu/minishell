/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:24:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/20 23:36:18 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_full_token(char *str, int *i)
{
	int		start;
	int		j;
	char	*token;
	char	quote;

	start = *i;
	j = *i;
	while (str[j] && str[j] != ' ' && !check_symbol(str, j))
	{
		if (check_in_quote(str, j))
		{
			quote = str[j];
			j++;
			while (str[j] && str[j] != quote)
				j++;
			if (str[j] == quote)
				j++;
		}
		else
			j++;
	}
	token = (char *)malloc(sizeof(char) * (j - start + 1));
	token = ft_strcpy(str, token, start, j - 1);
	*i = j;
	return (token);
}

char	**ft_set_string(char *str, char **result, int *i, int *count)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (!str[*i])
		return (result);
	if (check_symbol(str, *i))
		result[*count] = extract_symbol_token(str, i);
	else
		result[*count] = extract_full_token(str, i);
	(*count)++;
	return (result);
}

t_token	*tokenize(char *str)
{
	char	**result;
	int		compteur;
	int		i;
	i = 0;
	compteur = 0;
	if (verif_input(str) || ft_count_quote(str))
		return (NULL);
	str = ft_clean_comment(str);
	result = (char **)malloc(sizeof(char *) * (ft_countword(str) + 1));
	if (!result)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		ft_set_string(str, result, &i, &compteur);
	}
	result[ft_countword(str)] = 0;
	free(str);
	return (parse_line(result));
}
