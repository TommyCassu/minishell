/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:06:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/23 14:59:10 by tcassu           ###   ########.fr       */
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
# include <string.h> // a retirer

typedef enum 
{
    WORD,           // 0
    SINGLEQUOTE,    // 1
    DOUBLEQUOTE,    // 2
    L_REDIRECT,     // 3
    R_REDIRECT,     //4
    HEREDOC,        //5
    APP_REDIRECT,   //6
    START_SUBSHELL, //7
    END_SUBSHELL,   //8
    PIPE            //9
} t_type;

typedef struct token
{
    char    *value;
    t_type  type;
    struct token *next;
}	t_token;

typedef struct cmd
{
    char    **arguments;
    char    *l_redirect;
    char    *r_redirect;
    char    *app_redirect;
    int     previous_pipe;
    int     next_pipe;

    struct cmd *next;
}	t_cmd;

/* Spliting*/
t_token *tokenize(char *str);
char    *ft_clean_comment(char *str);
/*      Spliting Utils */
void	ft_free(char **result);
int		is_quote(char *str, int i);
int		check_in_quote(char *str, int i);
int		check_symbol(char *str, int i);
int		ft_countword(char *str);
char	*ft_strcpy(char *src, char *dest, int debut, int fin);
char	*extract_symbol_token(char *str, int *i);
t_token	*create_token(void *content);
void	ft_lstadd_backs(t_token **tokens, t_token *new);
void	add_type(t_token *tokens);
t_type	get_type(t_token *tokens);

int	ft_count_quote(char *str);
int verif_input(char *str);
void	ft_clean(t_token *tokens);

t_token	*parse_line(char **str);
void	print_tokens(t_token *tokens);
/* Verif error */
int parsing(t_token *tokens);
int verif_first_token(t_token *tokens);
int verif_other_tokens(t_token *tokens);
int verif_operator_utils(t_token *token);

/* Parsing cmd manager */
void    init_cmd(t_cmd *cmd);
void    add_arg(t_cmd *cmd, char *value);
void print_cmd(t_cmd *cmd);
void	add_l_red(t_cmd *cmd, t_token **tokens);
void	add_r_red(t_cmd *cmd, t_token **tokens);
void	add_app_red(t_cmd *cmd, t_token **tokens);
t_cmd   *parse_cmd(t_token *tokens);
void print_cmd(t_cmd *cmd); // a retirer juste pour print 
void	clear_quote(t_token *tokens);

/* Expansion */
void    expansion(t_token *tokens);
char    *expand_variable_w(char *value);
char    *expand_variable_dq(char *value);
#endif