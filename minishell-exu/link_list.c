#include "main.h"

int	ft_lstsize(t_command *lst)
{
	int		size;
	t_command	*current;

	if (lst == NULL)
		return (0);
	size = 0;
	current = lst;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}