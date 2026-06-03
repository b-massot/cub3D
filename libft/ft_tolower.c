/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:02:24 by bmassot           #+#    #+#             */
/*   Updated: 2026/03/24 16:43:38 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/*
#include <stdio.h>
int	main()
{
	int i = 0;
	char test[] = "Hello";
	while (test[i] != '\0')
	{
		printf("%c ", ft_tolower(test[i]));
		i++;
	}
	return (0);
}
*/