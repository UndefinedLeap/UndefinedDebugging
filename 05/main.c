#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_BUFFER_SIZE 100
#define LINES_CAPACITY 1000

void ocean_floor_log(const int *ocean_floor, int max_x, int max_y) {
	for (size_t y = 0; y < (size_t) max_y; ++y) {
		for (size_t x = 0; x < (size_t) max_x; ++x) {
			int num_lines = ocean_floor[y * (size_t) max_x + x];

			if (num_lines == 0) {
				putchar('.');
			} else if (num_lines < 10) {
				putchar('0' + num_lines);
			} else {
				putchar('X');
			}
		}
		putchar('\n');
	}
	putchar('\n');
}

int main1() {
	char line_buffer[LINE_BUFFER_SIZE];
	int lines[LINES_CAPACITY][4] = {0};
	size_t lines_count = 0;

	for (size_t y = 0; fgets(line_buffer, LINE_BUFFER_SIZE, stdin) == line_buffer; ++y) {
		char *remaining = line_buffer;
		char *endptr = NULL;

		for (size_t x = 0; x < 4; ++x) {
			long num = strtol(remaining, &endptr, 10);

			while (!isdigit(*endptr)) {
				endptr += 1;
			}

			remaining = endptr;
			endptr = NULL;
			lines[y][x] = (int) num;
		}

		lines_count += 1;
	}

	int max_x = 0;
	int max_y = 0;

	// Find max x and y.
	for (size_t i = 0; i < lines_count; ++i) {
		int x1 = lines[i][0];
		int y1 = lines[i][1];
		int x2 = lines[i][2];
		int y2 = lines[i][3];

#define MAX_ASSIGN(x, max) if (x > max) max = x;
		MAX_ASSIGN(x1, max_x);
		MAX_ASSIGN(x2, max_x);
		MAX_ASSIGN(y1, max_y);
		MAX_ASSIGN(y2, max_y);
#undef MAX_ASSIGN
	}

	// Account for 0 based indexing.
	max_x += 1;
	max_y += 1;

	int *ocean_floor = (int *) calloc((size_t) (max_x * max_y), sizeof(int));

	for (size_t i = 0; i < lines_count; ++i) {
		int x1 = lines[i][0];
		int y1 = lines[i][1];
		int x2 = lines[i][2];
		int y2 = lines[i][3];
		// printf("%d..%d -> %d..%d\n", x1, y1, x2, y2);

		if (x1 != x2 && y1 != y2) {
			continue;
		}

/// Compare x and y and evaluate to -1, 0, and 1 if x < y, x == y, and x > y respectively.
#define CMP(x, y) ((x == y) ? 0 : ((x < y) ? -1 : 1))
		const int dx = CMP(x2, x1);
		const int dy = CMP(y2, y1);
#undef CMP

		for (int x = x1, y = y1;; x += dx, y += dy) {
			ocean_floor[y * max_x + x] += 1;

			if (x == x2 && y == y2)
				break;
		}
	}

	// Count the number of points where at least two lines overlap.
	int count = 0;
	for (size_t y = 0; y < (size_t) max_y; ++y) {
		for (size_t x = 0; x < (size_t) max_x; ++x) {
			const int num_lines = ocean_floor[y * (size_t) max_x + x];
			if (num_lines >= 2) {
				count += 1;
			}
		}
	}

	// ocean_floor_log(ocean_floor, max_x, max_y);
	free(ocean_floor);

	printf("%d\n", count);

	return 0;
}

int main() {
#ifdef PART1
    main1();
#else
    printf("There no part-2!");
#endif
    return 0;
}