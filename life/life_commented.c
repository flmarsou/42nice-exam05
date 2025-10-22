#include "life.h"

/**
 * print_map
 * -----------------------------------------------------------------------------
 * Prints the current state of the game grid to stdout.
 * Alive cells are shown as '0', dead cells as ' '.
 */
static void	print_map(t_game game)
{
	for (int y = 0; y < game.height; ++y)
	{
		for (int x = 0; x < game.width; ++x)
			putchar(game.map[y][x]);
		putchar('\n');
	}
}

/**
 * free_map
 * -----------------------------------------------------------------------------
 * Frees all dynamically allocated memory associated with the game map.
 */
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

/**
 * fill_map
 * -----------------------------------------------------------------------------
 * Allows the user to manually draw the starting pattern.
 * 
 * Controls:
 *   W / A / S / D - Move the cursor up/left/down/right
 *   X - Toggle drawing mode (on/off)
 * 
 * While drawing mode is active, moving the cursor marks cells as alive ('0') while checking boundaries.
 * Input is read one character at a time from STDIN.
 */
static void	fill_map(t_game *game)
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

		// If draw mode is on AND x and y are within the game grid, mark the cell as alive
		if (draw && x >= 0 && x < game->width && y >= 0 && y < game->height)
			game->map[y][x] = '0';
	}
}

/**
 * count_neighbors
 * -----------------------------------------------------------------------------
 * Counts how many of the 8 surrounding cells around (x, y) are alive ('0').
 * 
 * dx/dy = direction
 * nx/ny = neighbor
 */
static int	count_neighbors(t_game game, int y, int x)
{
	int	count = 0;

	for (int dy = -1; dy < 2; ++dy)
	for (int dx = -1; dx < 2; ++dx)
	{
		// Skip the iteration if we're at the origin
		if (dx == 0 && dy == 0)
			continue ;

		// Calculate the cell to look at
		int	nx = x + dx;
		int	ny = y + dy;
		// If the cell we're looking at is within the game grid AND marked as alive, increase the count
		if (nx >= 0 && nx < game.width && ny >= 0 && ny < game.height && game.map[ny][nx] == '0')
			count++;
	}

	return (count);
}

/**
 * play_game
 * -----------------------------------------------------------------------------
 * Executes one full iteration of the Game of Life.
 * 
 * Rules applied:
 *   - Alive cell ('0') survives with 2 or 3 neighbors; otherwise dies.
 *   - Dead cell (' ') becomes alive with exactly 3 neighbors.
 * 
 * Allocates a new map for the next generation, applies rules, then swap the old map.
 */
static void	play_game(t_game *game)
{
	// Allocate a new map of the same size since it's easier than "redrawing" on the old one
	char	**new_map = malloc(game->height * sizeof(char *));
	for (int y = 0; y < game->height; ++y)
		new_map[y] = malloc(game->width * sizeof(char *));

	for (int y = 0; y < game->height; ++y)
	for (int x = 0; x < game->width; ++x)
	{
		int	neighbors = count_neighbors(*game, y, x);
		if (game->map[y][x] == '0')
		{
			// If the cell is alive with 2 or 3 neighbors, do nothing
			if (neighbors == 2 || neighbors == 3)
				new_map[y][x] = '0';
			// Otherwise kill it
			else
				new_map[y][x] = ' ';
		}
		// If the cell is dead with 3 neighbors, make it alive
		else
			if (neighbors == 3)
				new_map[y][x] = '0';
			else
				new_map[y][x] = ' ';
	}

	// Free the old map and replace it with the new allocated one
	free_map(game);
	game->map = new_map;
}

/**
 * init_game
 * -----------------------------------------------------------------------------
 * Initializes the game structure and allocates the 2D map.
 * 
 * Arguments:
 *   argv[1] = map width (x)
 *   argv[2] = map height (y)
 *   argv[3] = number of iterations
 */
static void	init_game(t_game *game, const char **argv)
{
	game->width = atoi(argv[1]);
	game->height = atoi(argv[2]);
	game->iteration = atoi(argv[3]);

	game->map = malloc(game->height * sizeof(char *));
	for (int y = 0; y < game->height; ++y)
	{
		game->map[y] = malloc(game->width * sizeof(char *));
		// Fill the entire map with dead cells
		for (int x = 0; x < game->width; ++x)
			game->map[y][x] = ' ';
	}
}

/**
 * Usage: echo <movements> | ./a.out <width> <height> <iterations>
 * 
 * 1. Initializes the game grid.
 * 2. Lets the user draw the initial pattern.
 * 3. Simulates the game for the given number of iterations.
 * 4. Prints the final grid state to STDOUT.
 */
int	main(const int argc, const char **argv)
{
	if (argc != 4)
		return (1);

	t_game	game;

	init_game(&game, argv);
	fill_map(&game);

	for (int i = 0; i < game.iteration; ++i)
		play_game(&game);

	print_map(game);
	free_map(&game);

	return (0);
}
