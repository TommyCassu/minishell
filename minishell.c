/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:24:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/13 11:48:03 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	char	**token;
	int i;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
		add_history(input);
		if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }
		token = tokenizer(input);
		i = 0;
		while (token[i])
		{
			printf("[%s] ", token[i]);
			i++;
		}
		printf("\n");
        free(input);
	}
}
