
#include "philo.h"

void	*threadie(void *data)
{
	int	*value;

	value = (int *)data;
	while (1)
	{
		if (*value == 120)
		{
			*value += 1;
			*value += 1;
			*value += 1;
			*value += 1;
			*value += 1;
		}
		else
		{
			*value -= 1;
			*value -= 1;
			*value -= 1;
			*value -= 1;
			*value -= 1;
		}
	}
	return (NULL);
}

int	main()
{
	int				value;
	int				check;
	pthread_t		th;

	value = 120;
	pthread_create(&th, NULL, threadie, &value);
	while (1)
	{
		check = value;
		if (check < 120 || check > 125)
		{
			printf("Warning! The value changed to %d\n", check);
			exit(0);
		}
	}
	pthread_join(th, NULL);
}