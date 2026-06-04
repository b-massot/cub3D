/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_adri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:58:13 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/04 16:11:11 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

int	check_extension(char *str)
{
	int len;
	
	len = ft_strlen(str);
	if (len < 5)
		return (0);
	if (ft_strncmp(&str[len-4], ".cub", 4) == 0)
		return (1);
	return (0);
}

int	check_path(char *str)
{
	int fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	check_map_validity(t_map_info *map)
{
	int	i;
	int line_number;

	i = 0;
	line_number = 0;
	while (map->file[i])
	{
		//check lignes vide -> avancer 
		//check identifiant avec sensible aux espaces
			//check identifiant (identifiants selon la norme, chemin valide pour certain, code couleur bon, pas de doublon et pas de manque)
		// check lignes vides -> avancer
		// check map 
			// detecter si 1, 0 ou (NSEW) ou espace ou \n /vérifier pas de doublon (NSEW)
			// floodfill pour detecter la map fermée
		// check lignes vides -> avancer
		//check si autre chose que lignes vide
		
	}
}
