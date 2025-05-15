/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:24:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/16 00:40:37 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("[%d : %s ]", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

void	test(char **str)
{
	t_token	*list = NULL;
	int i;

	i = 0;
	while (str[i])
	{
		t_token *t1 = create_token(str[i]);
		ft_lstadd_backs(&list, t1);
		i++;
	}
	add_type(list);
	print_tokens(list);
	t_token *tmp;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->value);
		free(tmp);
	}
}

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
		//ft_print(split_string);
		test(split_string);
	}
}
