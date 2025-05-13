/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:24:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/13 12:17:55 by tcassu           ###   ########.fr       */
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

char	**ft_set_string(const char *str, char **result, char c)
{
	int		i;
	int		debut;
	int		aw;

	i = 0;
	aw = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		debut = i;
		while (str[i] != c && str[i] != '\0')
			i++;
		if (aw < ft_countword(str))
		{
			result[aw] = (char *)malloc(sizeof(char) * ((i - 1)
						- debut + 1) + 1);
			if (!result[aw])
				return (NULL);
			result[aw] = ft_strcpy(str, result[aw], debut, (i - 1));
			aw++;
		}
	}
	result[aw] = 0;
	return (result);
}

char *ft_cutting()
{
	
}
char **test(const char *str, char **result, char separator)
{
	int i;
	int debut;
	int aw;
	
	i = 0;
	aw = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		debut = i;
		if (str[i] == '\'' || str[i] == '"')
			ft_cutting(str, str[i]);
		else

	}
	result[aw] = 0;
	return (result);
}

char	**tokenizer(char const *str)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * (ft_countword(str) + 1));
	printf("%d", ft_countword(str));
	if (!result)
		return (NULL);
	if (!ft_set_string(str, result, ' '))
	{
		ft_free(result);
		free(result);
		return (NULL);
	}
	return (result);
}