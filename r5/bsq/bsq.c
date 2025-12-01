#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

// allowed : malloc, calloc, realloc, free, fopen, fclose,
// getline, fscanf, fputs, fprintf, stderr, stdout, stdin, errno

typedef struct s_rule
{
	char space, obstacle, fill;
	int	highest, x, y;
}	t_rule;

bool	fail()
{
	return (fputs("Error: ", stderr), 1);
}

int	mapping(char c, t_rule rule)
{
	if (c == rule.space)
		return 1;
	else if (c == rule.obstacle)
		return 0;
	else if (c == 0)
		return (rule.obstacle);
	else if (c == rule.fill)
		return rule.fill;
	else
		return rule.space;
}

void	print_map(int *map, t_rule rule, int col, int rol)
{
	for (int y = 0; y < rol; ++y)
	{
		for (int x = 0; x < col; ++x)
		{
			printf("%c", mapping(map[y * col + x], rule));
		}
		printf("\n");
	}
}

t_rule	find_square(int *map, int col , int rol, t_rule rule)
{
	for (int y = 1; y < rol; ++y)
	{
		for (int x = 1; x < col; ++x)
		{
			int idx = y * col + x;
			if (map[idx] == 0)
				continue;
			int top = map [(y - 1) * col + x];
			int	dia = map [(y - 1) * col + (x - 1)];
			int left = map[y * col + (x - 1)];
			int min = top < left ? top : left;
			if (dia < min)
				min = dia;
			map[idx] = min + 1;
			if (map[idx] > rule.highest)
			{
				rule.highest = map[idx];
				rule.x = x;
				rule.y = y;
			}
		}
	}
	return (rule);
}

void	print_square(int *map, t_rule rule, int col, int rol)
{
	for (int y = rule.y - rule.highest + 1; y <= rule.y; ++y)
	{
		for (int x = rule.x - rule.highest + 1; x <= rule.x; ++x)
			map[y * col + x] = rule.fill;
	}
	print_map(map, rule, col, rol);
	printf("highest: %d\n", rule.highest);
}

bool	file_read(FILE *fp)
{
	if (!fp)
		return (fail());

	int	rol = 0, col = -1;
	t_rule	rule;
	char	end;
	if (fscanf(fp, "%d%c%c%c%c", &rol, &rule.space, &rule.obstacle, &rule.fill, &end) != 5 || end != '\n' || rol == 0)
		goto	cleanup;
	if (rule.space < 33 || rule.space > 126 || rule.obstacle < 33 || rule.obstacle > 126 || rule.fill < 33 || rule.fill > 126)
		goto	cleanup;
	if (rule.space == rule.obstacle || rule.space == rule.fill || rule.obstacle == rule.fill)
		goto	cleanup;
	rule.highest = -1;
	// printf("space : '%c' obs : '%c' fill : '%c' rol : '%d' col : '%d'\n", rule.space, rule.obstacle, rule.fill, rol, col);

	char *line = NULL;
	size_t	lcap;
	ssize_t	llen;
	int	*map = NULL;

	for (int y = 0; y < rol; ++y)
	{
		if ((llen = getline(&line, &lcap, fp)) <= 0 || line[llen - 1] != '\n' || (col != -1 && --llen != col))
			goto	cleanup;
		if (col == -1 && --llen > 0)
		{
			col = llen;
			map = calloc(rol * col, sizeof(int));
			if (!map)
				goto	cleanup;
		}
		for (int x = 0; x < col; ++x)
			map[y * col + x] = mapping(line[x], rule);
		// printf("line: %s\n", line);
	}
	print_square(map, find_square(map, col, rol, rule), col, rol);
	if (line)
		free(line);
	free(map);
	fclose(fp);
	return (0);
	cleanup:
		if (line && *line != '\0')
			free(line);
		if (map)
			free(map);
		if (fp)
			fclose(fp);
		return (1);
}

int	main(int ac, char **av)
{
	if (ac < 2)
		return (file_read(stdin));
	for (int i = 1; i < ac; ++i)
		if (file_read(fopen(av[i], "r")))
			return (fail());
}