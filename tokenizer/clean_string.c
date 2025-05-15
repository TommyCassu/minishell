/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:14:49 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/14 23:33:51 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *ft_clean_comment(char *str)
{
    int i;
    char    *result;
    
    i = 0;
    while (str[i] != '#' && str[i] != '\0')
    {
        if (str[i] == '\0')
            return (str);
        i++;
    }
    result = malloc(sizeof(char) * i + 1);
    i = 0;
    while (str[i] != '#' && str[i] != '\0')
    {
        result[i] = str[i];
        i++;
    }
    result[i] = '\0';
    free(str);
    return (result);
}
