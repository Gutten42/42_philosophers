/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:38:26 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/18 15:37:38 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	ind;

	ind = 0;
	while (str[ind])
		ind++;
	return (ind);
}

int	ft_isdigit(int value)
{
	if (value > 47 && value < 58)
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
	}
}

void	ft_bzero(void *memdir, size_t len)
{
	size_t	ind;

	ind = 0;
	while (ind < len)
	{
		*((char *)memdir + ind) = '\0';
		ind++;
	}
}

////////////////

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}

////////////////////////

static size_t	numsize(int n, int *pexp)
{
	size_t	val;

	val = 0;
	while (n / pexp[0] != 0 && pexp[0] != 1000000000)
	{
		pexp[0] = pexp[0] * 10;
		val++;
	}
	if (pexp[0] == 1000000000 && n / pexp[0] != 0)
		val++;
	if (n < 0)
		val++;
	if (n == 0)
		val++;
	return (val);
}

static void	assign(char *s, int n, int exp)
{
	size_t	ind;

	ind = 0;
	if ((exp == 1000000000 || exp == -1000000000) && n / exp != 0)
		s[ind++] = n / exp + 48;
	while (exp != 1 && exp != -1)
	{
		s[ind++] = ((n % exp) / (exp / 10)) + 48;
		exp = exp / 10;
	}
	if (n == 0)
		s[ind++] = '0';
	s[ind] = 0;
}

char	*ft_itoa(int n)
{
	int		exp;
	int		*pexp;
	char	*ret;
	size_t	ind;

	exp = 1;
	pexp = &exp;
	ind = 0;
	ret = malloc(numsize(n, pexp) + 1);
	if (!ret)
		return (NULL);
	if (n < 0)
	{
		ret[ind++] = '-';
		exp = -exp;
	}
	assign(&ret[ind], n, exp);
	return (ret);
}