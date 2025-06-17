/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:05:37 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/17 01:12:06 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *expand_tildes(t_shell *shell, char *value)
{
    char    *env_var;
    char    *new_value;
    
    if (ft_strcmp(value, "~") == 0)
    {
        env_var = env_get(shell->env, "HOME");
        free(value);
        if (env_var)
            return (ft_strdup(env_var));
        else
            return (ft_strdup(""));
    }
    if (value[0] == '~' && value[1] == '/')
    {
        env_var = env_get(shell->env, "HOME");
        new_value = ft_strjoin(env_var, (value + 2));
        free(value);
        return (new_value);
    }
    return (value);
}

char    *expand_cmd_code(t_shell *shell, char *value)
{
    char    *code;
    char    *result;
    
    code = ft_itoa(shell->global_status);
    result = replace_cmd_code(value, code);
    free(code);
    free(value);
    return (result);
}

void    expand_one(t_shell *shell, const char *value, char **exp, int *skip)
{ 
    if (value[1] == '{')
        expand_brace(shell, value, exp , skip);
    else if (ft_isalpha(value[1]) || value[1] == '_')
        expand_simple(shell, value, exp , skip);
    else
    {
       *exp = ft_strdup("$");
       *skip = 1;
    }
}

char    *expand_var(t_shell *shell, char *value)
{
    char    *new_value;
    char    *expansion;
    char    tmp[2];
    int     skip;
    int i;

    i = 0;
    new_value = ft_strdup("");
    while (value[i])
    {
        if (value[i] == '$' && check_in_quote(value, i) != 1)
        {
            expand_one(shell, value + i, &expansion, &skip);
            new_value = ft_strjoin_free(new_value, expansion);
            free(expansion);
            i += skip;
        }
        else
        {
            tmp[0] = value[i];
            tmp[1] = '\0';
            new_value = ft_strjoin_free(new_value, tmp);
            i++;
        }
    }
    free(value);
    return (new_value);
}

void    expansion(t_shell *shell, t_token *tokens)
{
    t_token *tmp;
    
    tmp = tokens;
    while(tmp)
    {
        if (tmp->type == WORD)
        {
            tmp->value = expand_tildes(shell, tmp->value);// tildes ~
            tmp->value = expand_var(shell, tmp->value);// variables
            tmp->value = expand_cmd_code(shell, tmp->value);// $?
        }
        tmp = tmp->next;
    }
}

/*
int is_valid_var(const char *str, int i)
{
    if (ft_isalnum(str[i]) || str[i] == '_')
        return (1);
    return (0);
}
char    *extract_varname(char *str)
{
    char    *tmp;
    char    *extract;
    int i;

    i = 0;
    tmp = malloc(sizeof(char) * 100);
    if (ft_isdigit(str[i]))
    {
        tmp[0] = str[i];
        tmp[1] = '\0';
        extract = ft_strdup(tmp);
        free(tmp);
        return (extract);
    }
    while (str[i] != '\0' && is_valid_var(str, i))
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    extract = ft_strdup(tmp);
    free(tmp);
    return(extract);
}

char    *fix_value(char *str)
{
    char    *new_value;
    int i;
    int j;
    
    i = 0;
    j = 0;
    new_value = NULL;
    if (str[i] != '\0')
    {
        new_value = malloc((sizeof(char)) * ft_strlen(str + i) + 1);
        while (str[i] != '\0')
        {
            if (str[i] == '$')
            {
                i++;
                continue ;
            }
            new_value[j++] = str[i++];
        }
            
        new_value[j] = '\0';
        free(str);
    }
    return (new_value);
}

char    *expand_variable_dq(t_shell *shell, char *value)
{
    int i;
    char    *variable;
    char    *var_env;
    
    i = 0;
    while (value[i])
    {
        if (value[i] == '$' && value[i + 1] == '?')
        {
            i++;
            variable = ft_strdup("?\0");
            var_env = ft_itoa(shell->global_status);
            value = expand_and_delete(value, variable, var_env);
            free(var_env);
            i = 0;
            continue ;
        }
        else if (value[i] == '$' && (value[i + 1] == '\"' || value[i + 1] == '\''))
        {
            value = fix_value(value);
        }
        else if (value[i] == '$' && value[i + 1] != '\0'
            && check_in_quote(value, i) != 1 && is_valid_var(value, i + 1))
        {
            i++;
            variable = extract_varname(value + i);
            var_env = env_get(shell->env, variable);
            value = expand_and_delete(value, variable, var_env);
            i = 0;
            continue ;
        }
        i++;
    }
    return (value);
} 


char    *expand_and_delete(char    *value, char *variable, char *var_env)
{
    int i;
    int j;
    char    *tmp;
    char    *new_value;
    
    j = 0;
    i = 0;
    while (value[i] != '$' && value[i])
        i++;
    j = i + 1 + ft_strlen(variable);
    tmp = ft_substr(value, 0, i);
    if (var_env)
        new_value = ft_strjoin(tmp, var_env);
    else
        new_value = ft_strdup(tmp);
    free(tmp);
    tmp = ft_strjoin(new_value, value + j);
    free(new_value);
    new_value = tmp;
    free(value);
    free(variable);
    return (new_value);
}
*/
