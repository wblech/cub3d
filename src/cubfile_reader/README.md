# CUBFILE READER

This is a program that reads .cub files to be used in the project cub3d from 42 school.

After reading the file, it checks if follow the file follow this rules:

* The map must be composed of only 4 possible characters: **0** for an emptyspace, **1** for a wall, **2** for an item and **N**, **S**,**E** or **W** for the player’s start position and spawning orientation.
* This is a simple valid map:

```
  111111
  100101
  102001
  1100N1
  111111
```

* The map must be closed/surrounded by walls, if not the program must returnan error.* Except for the map content, each type of element can be separated by one or more empty line(s).
* Except for the map content which always has to be the last, each type of element can be set in any order in the file.
* Except for the map, each type of information from an element can be separatedby one or more space(s).
* The map must be parsed as it looks like in the file. Spaces are a valid part of the map, and is up to you to handle. You must be able to parse any kind of map, as long as it respects the maps rules.
* Each element (except the map) firsts information is the type identifier (com-posed by one or two character(s)), followed by all specific informations for each object in a strict order such as :
  * Resolution:
  `R 1920 1080`
  identifier: **R**
  x render size
  y render size
  * North texture:
`NO ./path_to_the_north_texture`
identifier: **NO**
path to the north texure
  * South texture:
   `SO ./path_to_the_south_texture`
   identifier: **SO**
   path to the south texure
  * West texture:
  `WE ./path_to_the_west_texture`
identifier: **WE**
path to the west texure
  * East texture:
  `EA ./path_to_the_east_texture`
identifier: **EA**
path to the east texure
  * Sprite texture:
  `S ./path_to_the_sprite_texture`
identifier: **S**
path to the sprite texure
  * Floor color:
  `F 220,100,0`
identifier: **F**
R,G,B colors in range [0,255]:0, 255, 255

  * Ceilling color:
  `C 225,30,0`
identifier: **C**
R,G,B colors in range [0,255]:0, 255, 255

* Example of the mandatory part with a minimalist.cubscene:

```
R 1920 1080
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
S ./path_to_the_sprite_texture
F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000002000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10002000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

* If any misconfiguration of any kind is encountered in the file, the programmust exit properly and return "Error\n" followed by an explicit error messageof your choice


## Return

If all rules are respected it will return a pointer to a struct named file:

```
typedef struct	s_file
{
	int			width;
	int			height;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sprite;
	int			floor;
	int			ceiling;
	t_map		*map;
}				t_file;
```

## How to Install

1) Do a git clone from this repository:

    `git clone https://github.com/wblech/cubfile_reader`

2) Add a main function

```C
int main(int argc, char **argv)
{
	t_file *file;

	(void)argc;
	file = ft_cubfile(argv[1]);
	ft_del_file(file);
	return (0);
}
```

3) Run Makefile

    `make`

## How to use

For a simple test you can create this main function

If you use the example main file just run this command at the terminal:

`./main ./maps/1.cub`

You can change the "./maps/1.cub" for any cubfile that you want to test.

