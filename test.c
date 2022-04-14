
#include "philo.h"

int	main()
{
	struct timeval	time;

	while (1) {
		printf("Now it's %d\n", get_time(&time));
		usleep(1000000);
	}
}