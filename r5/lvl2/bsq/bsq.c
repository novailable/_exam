#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
	int rows;
	int cols;
	char empty;
	char obstacle;
	char full;
	char **map;
} t_map;

typedef struct {
	int size;
	int row;
	int col;
} t_square;

void free_map(t_map *m) {
	if (!m) return;
	if (m->map) {
		for (int i = 0; i < m->rows; i++)
			free(m->map[i]);
		free(m->map);
	}
}

int error_msg() {
	fprintf(stderr, "map error\n");
	return 0;
}

int parse_first_line(char *line, t_map *m) {
	char c1, c2, c3;
	if (sscanf(line, "%d %c %c %c", &m->rows, &c1, &c2, &c3) != 4)
		return 0;
	if (m->rows <= 0 || c1 == c2 || c1 == c3 || c2 == c3)
		return 0;
	m->empty = c1; m->obstacle = c2; m->full = c3;
	return 1;
}

int read_map(FILE *f, t_map *m)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	// First line
	read = getline(&line, &len, f);
	if (read <= 0 || !parse_first_line(line, m)) { free(line); return 0; }

	m->map = malloc(sizeof(char*) * m->rows);
	if (!m->map) { free(line); return 0; }

	int row = 0;
	while (row < m->rows && (read = getline(&line, &len, f)) != -1) {
		if (line[read - 1] == '\n') line[--read] = '\0';
		if (row == 0) m->cols = read;
		else if (read != m->cols) { free(line); return 0; }

		m->map[row] = malloc(read + 1);
		if (!m->map[row]) { free(line); return 0; }
		strcpy(m->map[row], line);

		for (int i = 0; i < read; i++)
			if (m->map[row][i] != m->empty && m->map[row][i] != m->obstacle)
				return 0;
		row++;
	}
	free(line);
	return row == m->rows;
}

t_square find_bsq(t_map *m) {
	int **dp = malloc(sizeof(int*) * m->rows);
	t_square sq = {0, 0, 0};
	for (int i = 0; i < m->rows; i++)
		dp[i] = malloc(sizeof(int) * m->cols);

	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			if (m->map[i][j] == m->obstacle) dp[i][j] = 0;
			else if (i == 0 || j == 0) dp[i][j] = 1;
			else {
				int min = dp[i-1][j];
				if (dp[i][j-1] < min) min = dp[i][j-1];
				if (dp[i-1][j-1] < min) min = dp[i-1][j-1];
				dp[i][j] = min + 1;
			}
			if (dp[i][j] > sq.size) {
				sq.size = dp[i][j];
				sq.row = i;
				sq.col = j;
			}
		}
	}

	for (int i = 0; i < m->rows; i++)
		free(dp[i]);
	free(dp);
	return sq;
}

void fill_bsq(t_map *m, t_square sq) {
	for (int i = sq.row - sq.size + 1; i <= sq.row; i++)
		for (int j = sq.col - sq.size + 1; j <= sq.col; j++)
			m->map[i][j] = m->full;
}

void print_map(t_map *m) {
	for (int i = 0; i < m->rows; i++)
		printf("%s\n", m->map[i]);
}

int process_file(const char *filename)
{
	FILE *f = filename ? fopen(filename, "r") : stdin;
	if (!f) return error_msg();

	t_map m = {0};
	if (!read_map(f, &m))
	{
		free_map(&m); if (filename) fclose(f);
		return error_msg();
	}

	if (filename) fclose(f);

	t_square sq = find_bsq(&m);
	fill_bsq(&m, sq);
	print_map(&m);
	free_map(&m);
	return 1;
}

int main(int argc, char **argv) {
	if (argc < 2) return process_file(NULL);

	for (int i = 1; i < argc; i++) {
		process_file(argv[i]);
		if (i < argc - 1) printf("\n");
	}
	return 0;
}
