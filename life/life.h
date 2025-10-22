#pragma once

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct
{
	int		width;
	int		height;
	int		iteration;
	char	**map;
} t_game;
