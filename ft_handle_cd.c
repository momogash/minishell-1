

#include "minishell.h"

static void		ft_home(char ***envp)
{
	char *temp;

	temp = NULL;
	if (chdir(ft_handle_getenv(*envp, "HOME")) < 0)
	{
		ft_error(NDIR, ft_handle_getenv(*envp, "HOME"));
		return ;
	}
	temp = ft_strdup(ft_handle_getenv(*envp, "PWD"));
	ft_handle_setenv(envp, "PWD", ft_handle_getenv(*envp, "HOME"), 1);
	ft_handle_setenv(envp, "OLDPWD", temp, 1);
	ft_strdel(&temp);
}

static void		ft_handle_dash(char ***envp)
{
	char *temp;

	temp = NULL;
	if (chdir(ft_handle_getenv(*envp, "OLDPWD")) < 0)
	{
		ft_error(NDIR, ft_handle_getenv(*envp, "OLDPWD"));
		return ;
	}
	temp = ft_strdup(ft_handle_getenv(*envp, "PWD"));
	ft_handle_setenv(envp, "PWD", ft_handle_getenv(*envp, "OLDPWD"), 1);
	ft_handle_setenv(envp, "OLDPWD", temp, 1);
	ft_strdel(&temp);
}

static void		ft_handle_dirname(char ***envp, char **argv)
{
	char *temp;

	temp = NULL;
	if (chdir(argv[1]) < 0)
	{
		ft_error(NDIR, argv[1]);
		return ;
	}
	temp = ft_strdup(ft_handle_getenv(*envp, "PWD"));
	ft_handle_setenv(envp, "PWD", getcwd(argv[1], ft_strlen(argv[1])), 1);
	ft_handle_setenv(envp, "OLDPWD", temp, 1);
	ft_strdel(&temp);
}

void			ft_handle_cd(char ***envp, char **argv)
{
	if ((argv[0] && !argv[1]) || ft_strcmp(argv[1], "~") == 0)
		ft_home(envp);
	else if (argv[0] && argv[1][0] == '-')
		ft_handle_dash(envp);
	else if (argv[0] && argv[1])
		ft_handle_dirname(envp, argv);
}
