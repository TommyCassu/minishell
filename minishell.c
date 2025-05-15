/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:24:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/15 20:18:28 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("[%s] ", str[i]);
		free(str[i]);
		i++;
	}
	free(str);
	printf("\n");
}

int	main(void)
{
	char	*input;
	char	*clean;
	char	**split_string;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		clean = ft_clean_comment(input);
		/* Verif quote ouvert mais non ferme (a faire) */
		split_string = ft_splits(clean);
		free(clean);
		ft_print(split_string);
	}
}
