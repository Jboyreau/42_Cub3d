#include "header.h"
#include <sys/stat.h>
#define MAP_PATH "./map/map.txt"

static char *load_map(char *file)
{
	int		fd;
	int		len;
	char	*buffer;
	struct stat info_fichier;

	if (stat(file, &info_fichier) != 0)
	{
		perror("Error get file informations");
		return (NULL);
	}
	if (S_ISDIR(info_fichier.st_mode))
	{
		perror("FILE is a directory");
		return (NULL);
	}
	fd = open(file, O_RDWR);
	if (fd == -1)
		return (NULL);
	len = lseek(fd, 0, SEEK_END) + 1;
	if (len == 1)
		return (NULL);
	buffer = malloc(len);
	if (buffer == NULL)
		return (NULL);
	lseek(fd, 0, SEEK_SET);
	read(fd, buffer, len - 1);
	*(buffer + len - 1) = '\0';
	close(fd);
	return (buffer);
}

static void set_map_size(char *map_raw, int *line_len, int *line_nb)
{
	int	i;
	int len;

	len = 0;
	i = 0;
	while (*(map_raw + i))
	{
		++len;
		if (*(map_raw + i) == '\n')
		{
			++(*line_nb);
			if (len > *line_len)
				*line_len = len;
			len = 0; 
		}
		++i;
	}
}

static char *process_map(char *map_raw, int line_len, int line_nb)
{
	char	*map;
	int		len;
	int		i;
	int		j;

	map = malloc(line_len * line_nb);
	if (map == NULL)
		return (NULL);
	i = -1;
	j = 0;
	len = 0;
	while (*(map_raw + (++i)))
	{
		++len;
		if (*(map_raw + i) == '\n')
		{
			while (len <= line_len)
			{
				*(map + j) = '?';
				++j;
				++len;
			}
			len = 0;
		}
		else
		{
			if (*(map_raw + i) == ' ')
				*(map + j) = '?';
			else
				*(map + j) = *(map_raw + i);
			++j;
		}
	}
	return (map);
}

void	print_process_map(char *map, int line_len, int line_nb)
{
	for (int i = 0; i < line_nb; ++i)
	{
		for (int j = 0; j < line_len; ++j)
			putchar(*(map + i * line_len + j));
		putchar('\n');
	}
			
}

int	main (void)
{
	char	*map_raw;
	char	*map;
	int		line_len;
	int		line_nb;

	line_len = 0;
	line_nb = 0;
	map_raw = load_map(MAP_PATH);
	if (map_raw == NULL)
		return (write(2, "Error open map failed.\n", 23), 1);
	set_map_size(map_raw, &line_len, &line_nb);
	printf("line_len = %d, line_nb = %d\n", line_len, line_nb);
	map = process_map(map_raw, line_len, line_nb);
	if (map == NULL)
		return (write(2, "Error process map failed.\n", 27), 1);
	print_process_map(map, line_len, line_nb);
	if (map_raw)
		free(map_raw);
	if (map)
		free(map);
	return (0);
}
