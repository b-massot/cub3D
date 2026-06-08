/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser_adri.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:00:00 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 14:47:09 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

static void	trim_line_end(char *line, int *end)
{
	while (*end >= 0
		&& (line[*end] == ' ' || line[*end] == '\t' || line[*end] == '\n'))
	{
		line[*end] = '\0';
		(*end)--;
	}
}

int	check_texture(char *line, int pos)
{
	int	end;
	int	len;

	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	if (line[pos] == '\0' || line[pos] == '\n')
		return (0);
	end = (int)ft_strlen(line) - 1;
	trim_line_end(line, &end);
	if (end < pos)
		return (0);
	len = end - pos + 1;
	if (len < 5 || ft_strncmp(&line[pos + len - 4], ".xpm", 4) != 0)
		return (0);
	return (check_path(&line[pos]));
}
