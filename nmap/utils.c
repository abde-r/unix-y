#include "nmap.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*tab;

	tab = calloc((strlen(s1) + strlen(s2) + 1), 1);
	if (!tab)
		return (0);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		tab[i++] = s2[j];
		j++;
	}
	tab[i] = '\0';
	free(s1);
	return (tab);
}