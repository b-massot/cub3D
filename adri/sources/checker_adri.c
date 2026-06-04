/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_adri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:58:13 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/04 13:46:59 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

int	check_extension(char *str)
{
	int len;
	
	len = ft_strlen(str);
	if (len < 5)
		return (0);
	if(ft_strncmp(&str[len-4], ".cub", 4) == 0)
		return (1);
	return (0);
}

int	check_path(char *str)
{
	int fd;

	fd = open(str, O_RDONLY);
	if(fd == -1)
		return (0);
	close(fd);
	return (1);
}

