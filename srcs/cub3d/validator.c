#include "../../incl/cub3d.h"

void check_rectangle(char *map[])
{
	int i;

	i = -1;
	while (map[++i])
		if (map_width(map[0]) != map_width(map[i]))
			quit(NULL, "Map is not rectangle");
}

void check_walls(char *map[], t_game *game)
{
	int i;

	if (!ft_strchr(map[0], '1') || !ft_strchr(map[game->map_height - 1], '1'))
		quit(NULL, "Map is not surrendered by upper or lower walls");
	i = -1;
	while (map[++i])
		if (map[i][0] != '1' || map[i][game->map_width - 1] != '1')
			quit(NULL, "Map is not surrendered by left or right walls");
}

void check_map_extension(const char *av[])
{
	if (!ft_strrstr(av[1], ".cub", 4))
		quit(NULL, "Map not .cub extension file");
}
