#include "../../includes/minishell.h"

int	skip_n(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] == 'n')
		i++;
	if (s[i])
		return (0);
	return (1);
}
