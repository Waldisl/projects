
#include "../../includes/minishell.h"
static bool	ft_check_index(const char *cmd_arg, int char_index)
{
	int	i;
	int	count;

	if (char_index <= 0)
		return (false);
	if (ft_strlen(cmd_arg) <= (unsigned int) char_index)
		return (false);
	count = 0;
	i = char_index - 1;
	while (i >= 0 && cmd_arg[i] == '\\')
	{
		count++;
		i--;
	}
	return (count % 2);
}

static char	*ft_get_name_env(const char *str)
{
	int		i;
	char	*env_name;

	str++;
	if (*str == 0)
		return (NULL);
	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (!i)
		return (NULL);
	env_name = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(env_name, str, i + 1);
	return (env_name);
}

void	ft_check_env(char **cmd_arg)
{
	char	*tmp;
	char	*env_name;
	char	*env_value;
	int		i;

	tmp = *cmd_arg;
	while (tmp && *tmp)
	{
		tmp = ft_strchr(tmp, '$');
		i = tmp - *cmd_arg;
		if (!tmp)
			return ;
		if (*cmd_arg[0] != '\'' && !ft_check_index(*cmd_arg, i))
		{
			env_name = ft_get_name_env(tmp);
			if (env_name)
			{
				env_value = ft_find_env(env_name);
				ft_str_replace(cmd_arg, i, i + ft_strlen(env_name), env_value);
				free(env_value);
				free(env_name);
			}
		}
		tmp = *cmd_arg + i + 1;
	}
}

void	ft_check_str_code(char **cmd_arg)
{
	char	*tmp;
	char	*code;
	int		i;

	tmp = *cmd_arg;
	while (tmp && *tmp)
	{
		tmp = ft_strchr(tmp, '$');
		i = tmp - *cmd_arg;
		if (!tmp)
			return ;
		if (*cmd_arg[0] != '\'' && !ft_check_index(*cmd_arg, i))
		{
			code = ft_itoa(g_global.code);
			ft_str_replace(cmd_arg, i, i + 1, code);
			free(code);
		}
		tmp = *cmd_arg + i + 1;
	}
}

void	ft_check_tilde(char **cmd_arg)
{
	char	*tmp;

	if ((*cmd_arg)[0] == 0 || (*cmd_arg)[0] == '\'' || (*cmd_arg)[0] == '"')
		return ;
	if ((*cmd_arg)[0] == '~' && (*cmd_arg)[1] != '~')
	{
		tmp = ft_find_env("HOME");
		ft_str_replace(cmd_arg, 0, 0, tmp);
		free(tmp);
	}
}
