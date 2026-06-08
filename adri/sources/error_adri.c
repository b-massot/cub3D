/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_adri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:58:16 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 13:50:11 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

char	*get_error_text(int code)
{
	if (code == FAILED_MEMORY_ALLOCATION)
		return ("Memory allocation failed");
	if (code == MAP_EMPTY)
		return ("Map file is empty");
	if (code == COLOR_INVALID)
		return ("Invalid RGB color format");
	if (code == TEXTURE_INVALID)
		return ("Invalid or missing texture path");
	if (code == DOUBLE_IDENTIFIERS)
		return ("Textures or colors are not unique identifiers");
	if (code == INVALID_MAP)
		return ("Invalid map configuration");
	return ("Unknown error");
}

int	print_error(char *message, int error_code)
{
	ft_putstr_fd("Error\n", 2);
	if (error_code != -1)
		ft_putstr_fd(get_error_text(error_code), 2);
	else
		ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
