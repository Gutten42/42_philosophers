
#include "philo.h"

void	*threadie(void *data)
{
	int	ret;
	
	ret = pthread_mutex_lock((pthread_mutex_t *)data);
	ft_putnbr_fd(ret, STDERR_FILENO);
	return (NULL);
}

int	main()
{
	pthread_mutex_t	mutex;
	pthread_t		th;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	ft_putendl_fd("A", STDERR_FILENO);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
	pthread_create(&th, NULL, threadie, &mutex);
	//ft_putnbr_fd(pthread_mutex_lock(&mutex), STDERR_FILENO);
	ft_putendl_fd("B", STDERR_FILENO);
	pthread_join(th, NULL);
	ft_putendl_fd("C", STDERR_FILENO);
}