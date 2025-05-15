/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:06:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/16 00:40:52 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum 
{
    COMMAND,
    ARGUMENT,
    OPERATION,
    PIPE
} t_type;

typedef struct token
{
    char    *value;
    t_type  type;
    struct token *next;
}	t_token;

/* Spliting*/
char	**ft_splits(char const *str);
char    *ft_clean_comment(char *str);
/*      Spliting Utils */
void	ft_free(char **result);
int		is_quote(const char *str, int i);
int		check_in_quote(const char *str, int i);
int		check_symbol(const char *str, int i);
int		ft_countword(const char *str);
char	*ft_strcpy(const char *src, char *dest, int debut, int fin);
char	*extract_symbol_token(const char *str, int *i);
t_token	*create_token(void *content);
void	ft_lstadd_backs(t_token **tokens, t_token *new);
void	add_type(t_token *tokens);
#endif