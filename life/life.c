#include "life.h"

static void	print_map(t_game game)
{
	for (int y = 0; y < game.height; ++y)
	{
		for (int x = 0; x < game.width; ++x)
			putchar(game.map[y][x]);
		putchar('\n');
	}
}

static void	free_map(t_game *game)
{
	if (game->map)
	{
		for (int i = 0; i < game->height; ++i)
			if (game->map[i])
				free(game->map[i]);
		free(game->map);
	}
}

static void	draw_map(t_game *game)
{
	char	buffer;
	int		x = 0;
	int		y = 0;
	bool	draw = false;

	while (read(STDIN_FILENO, &buffer, 1) == 1)
	{
		switch (buffer)
		{
			case ('w'): if (y > 0) { --y; }; break ;
			case ('a'): if (x > 0) { --x; }; break ;
			case ('s'): if (y < game->height - 1) { ++y; } break ;
			case ('d'): if (x < game->width - 1) { ++x; } break ;
			case ('x'): draw = !draw; break ;
			default: continue ;
		}

		if (draw && x >= 0 && x < game->width && y >= 0 && y < game->height)
			game->map[y][x] = '0';
	}
}

static int	count_neighbors(t_game game, int y, int x)
{
	int	count = 0;

	for (int dy = -1; dy < 2; ++dy)
	{
		for (int dx = -1; dx < 2; ++dx)
		{
			if (dx == 0 && dy == 0)
				continue ;

			int	nx = x + dx;
			int	ny = y + dy;
			if (nx >= 0 && nx < game.width && ny >= 0 && ny < game.height && game.map[ny][nx] == '0')
				count++;
		}
	}

	return (count);
}

static bool	play_game(t_game *game)
{
	char	**new_map = malloc(game->height * sizeof(char *));
	if (!new_map)
		return (false);
	for (int y = 0; y < game->height; ++y)
	{
		new_map[y] = malloc(game->width * sizeof(char *));
		if (!new_map[y])
			return (false);
	}

	for (int y = 0; y < game->height; ++y)
	{
		for (int x = 0; x < game->width; ++x)
		{
			int	neighbors = count_neighbors(*game, y, x);
			if (game->map[y][x] == '0')
			{
				if (neighbors == 2 || neighbors == 3)
					new_map[y][x] = '0';
				else
					new_map[y][x] = ' ';
			}
			else
			{
				if (neighbors == 3)
					new_map[y][x] = '0';
				else
					new_map[y][x] = ' ';
			}
		}
	}

	free_map(game);
	game->map = new_map;
	return (true);
}

static bool	init_game(t_game *game, const char **argv)
{
	game->width = atoi(argv[1]);
	game->height = atoi(argv[2]);
	game->iteration = atoi(argv[3]);

	game->map = malloc(game->height * sizeof(char *));
	if (!game->map)
		return (false);

	for (int y = 0; y < game->height; ++y)
	{
		game->map[y] = malloc(game->width * sizeof(char *));
		if (!game->map[y])
		{
			free_map(game);
			return (false);
		}
		for (int x = 0; x < game->width; ++x)
			game->map[y][x] = ' ';
	}

	return (true);
}

int	main(const int argc, const char **argv)
{
	if (argc != 4)
		return (1);

	t_game	game;

	if (!init_game(&game, argv))
		return (1);

	draw_map(&game);

	for (int i = 0; i < game.iteration; ++i)
		if (!play_game(&game))
		{
			free_map(&game);
			return (1);
		}

	print_map(game);

	free_map(&game);

	return (0);
}
