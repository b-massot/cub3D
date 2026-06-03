/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:53:43 by bmassot           #+#    #+#             */
/*   Updated: 2025/12/04 13:46:58 by bmassot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_size(long n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*new;
	long	nb;
	int		len;

	nb = (long)n;
	len = int_size(nb);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	new[len] = '\0';
	if (nb < 0)
	{
		nb = -nb;
		new[0] = '-';
	}
	while (len > (new[0] == '-'))
	{
		new[len - 1] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (new);
}
/*
#include <stdio.h>
int	main()
{
	int test = -1234;
	int test2 = 0;
	printf("%s\n", ft_itoa(test));
	printf("%s\n", ft_itoa(test2));

	return (0);
}
*/
