#include "shell.h"

/**
 * add_key - create a new environment variable
 * @vars: pointer to struct of variables
 * 
 * Return: void
 */

void add_key(vars_t *vars)
{
    unsigned int i;
    char **newenv;

    for (i = 0; vars->env[i] != NULL; i++)
        newenv = malloc(sizeof(char *) * (i + 2));
    if (newenv == NULL)
    {
        print_error(vars, NULL);
        vars->status = 127;
        new_exit(vars);
    }
    for (i = 0; vars->env[i] != NULL; i++)
        newenv[i] = vars->env[i];
    newenv[i] = add_value(vars->av[1], vars->av[2]);
    if (newenv[i] == NULL)
    {
        print_error(vars, NULL);
        free(vars->buffer);
        free(vars->commands);
        free(vars->av);
        free_env(vars->env);
        free(newenv);
        exit(127);
    }
    newenv[i + 1] = NULL;
    free(vars->env);
    vars->env = newenv;
}

/**
 * find_key - finds an environment variable
 * @env: array of environment variables
 * @key: environment variable to find
 * 
 * Return: pointer to address of the environment variable
 */

char **find_key(char **env, char *key)
{
    unsigned int i, j, len;

    len = _strlen(key);
    for (i = 0; env[i] != NULL; i++)
    {
        for (j = 0; j < len; j++)
            if (key[j] != env[i][j])
                break;
        if (j == len && env[i][j] == '=')
            return (&env[i]);
    }
    return (NULL);
}

/**
 * add_value - create a new environment variable string
 * @key: variable name
 * @value: variable value
 * 
 * Return: pointer to the new string
 */

char *add_value(char *key, char *value)
{
    unsigned int len1, len2, i, j;
    char *new;

    len1 = _strlen(key);
    len2 = _strlen(value);
    new = malloc(sizeof(char) * (len1 + len2 + 2));
    if (new == NULL)
        return (NULL);
    for (i = 0; key[i] != '\0'; i++)
        new[i] = key[i];
    new[i] = '=';
    for (j = 0; value[j] != '\0'; j++)
        new[i + 1 + j] = value[j];
    new[i + 1 + j] = '\0';
    return (new);
}