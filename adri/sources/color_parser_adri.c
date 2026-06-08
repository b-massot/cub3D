/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser_adri.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:00:00 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 15:16:29 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

static int	parse_rgb_value(char *line, int *pos)
{
	int	value;

	value = 0;
	while (line[*pos] >= '0' && line[*pos] <= '9')
	{
		value = value * 10 + (line[*pos] - '0');
		(*pos)++;
	}
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

static int	skip_whitespace_and_comma(char *line, int *pos, int count)
{
	while (line[*pos] == ' ' || line[*pos] == '\t')
		(*pos)++;
	if (count < 2 && line[*pos] != ',')
		return (0);
	if (count < 2)
		(*pos)++;
	while (line[*pos] == ' ' || line[*pos] == '\t')
		(*pos)++;
	return (1);
}

int	check_color(char *line, int pos)
{
	int	count;
	int	value;

	count = 0;
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	while (count < 3)
	{
		if (line[pos] < '0' || line[pos] > '9')
			return (0);
		value = parse_rgb_value(line, &pos);
		if (value == -1)
			return (0);
		if (!skip_whitespace_and_comma(line, &pos, count))
			return (0);
		count++;
	}
	if (line[pos] != '\0' && line[pos] != '\n')
		return (0);
	return (1);
}
