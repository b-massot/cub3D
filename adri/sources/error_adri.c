/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_adri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:58:16 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/04 11:22:14 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

int print_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	free_map(t_map_info	map)
{
	
}