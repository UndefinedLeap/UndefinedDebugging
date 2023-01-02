#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_CAPACITY 1000
#define ENTRY_CAPACITY 300

typedef struct {
	char *str;
	size_t size;
} Pattern;

Pattern scan_next_pattern(const char *str, char **endptr) {
	size_t idx = 0;
	while (!(str[idx] >= 'a' && str[idx] <= 'g')) {
		idx += 1;
	}

	assert(str[idx] >= 'a' && str[idx] <= 'g');

	Pattern pattern;
	pattern.str = (char *) (str + idx);

	size_t size = 0;

	while (str[idx] >= 'a' && str[idx] <= 'g') {
		idx += 1;
		size += 1;
	}

	pattern.size = size;

	if (endptr != NULL)
		*endptr = (char *) (str + idx);

	return pattern;
}

int main() {
	char line_buffer[LINE_CAPACITY];

	Pattern entries[ENTRY_CAPACITY][14];
	size_t entry_count = 0;

	while (fgets(line_buffer, LINE_CAPACITY, stdin) == line_buffer) {
		char *remaining = line_buffer;
		char *endptr = NULL;

		for (size_t i = 0; i < 14; ++i) {
			Pattern pattern = scan_next_pattern(remaining, &endptr);
			// printf("%.*s\n", (int) pattern.size, pattern.str);
			entries[entry_count][i] = pattern;
			remaining = endptr;
			endptr = NULL;
		}

		entry_count += 1;
	}

	int appearance = 0;

	for (size_t y = 0; y < entry_count; ++y) {
		for (size_t x = 10; x < 14; ++x) {
			const size_t size = entries[y][x].size;

			if (size == 2 || size == 3 || size == 4 || size == 7) {
				appearance += 1;
			}
		}
	}

	printf("%d\n", appearance);

	return 0;
}
