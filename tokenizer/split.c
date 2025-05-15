/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:24:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/15 00:43:38 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_countword(const char *str)
{
	int	i;
	int	inword;
	int	nbword;

	i = 0;
	inword = 0;
	nbword = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39 || str[i] == 34)
		{
			i = is_quote(str, i);
			nbword++;
		}
		else
		{
			if (str[i] == ' ')
			inword = 0;
			else if (str[i] != ' ' && inword == 0)
			{
				inword = 1;
				nbword++;
			}
			i++;
		}
	}
	return (nbword);
}

char	*ft_strcpy(const char *src, char *dest, int debut, int fin)
{
	int	i;

	i = 0;
	while (debut <= fin)
	{
		dest[i] = src[debut];
		i++;
		debut++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_set_string(const char *str, char **result, int *i, int *compteur)
{
	int		debut;

	while (str[*i] != ' ' && str[*i] != '\0')
	{
		debut = *i;
		if (str[*i] == '"' || str[*i] == '\'')
		{
			(*i)++;
			while (str[*i] != '"' && str[*i] != '\'' && str[*i] != '\0')
				(*i)++;
			(*i)++;
		}
		else 
			while (str[*i] != ' ' && str[*i] != '\0')
				(*i)++;
		if (str[*i - 1] != '\0')
		{
			result[*compteur] = (char *)malloc(sizeof(char) * ((*i - 1) - debut + 1) + 1);
			if (!result[*compteur])
				return (NULL);
			result[*compteur] = ft_strcpy(str, result[*compteur], debut, ((*i) - 1));
			(*compteur)++;
		}
	}
	return (result);
}

char	**ft_splits(char const *str)
{
	char	**result;
	int	compteur;
	int i;

	i = 0;
	compteur = 0;
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
	return (result);
}
