
#include "philo.h"

void	*threadie(void *data)
{
	int	*ret;
	int	reps;
	
	ret = (int *)data;
	reps = 1000000000;
	while (reps-- > 0)
		*ret += 1;
	return (NULL);
}

int	main()
{
	int				value;
	int				new_val;
	int				old_val;
	pthread_t		th;

	value = 0;
	pthread_create(&th, NULL, threadie, &value);
	while (new_val < 1000000000)
	{
		new_val = value;
		printf("%d\n", new_val);
	}
}