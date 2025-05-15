#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


/* Spliting*/
char	**ft_splits(char const *str);
char    *ft_clean_comment(char *str);
/*      Spliting Utils */
void	ft_free(char **result);
int	is_quote(const char *str, int i);
#endif