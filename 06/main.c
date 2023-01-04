#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_BUFFER_CAPACITY 1000
#define LF_MAX 9

int main1() {
	char line_buffer[LINE_BUFFER_CAPACITY];
	uint64_t lanternfish[LF_MAX] = {0};

	assert(fgets(line_buffer, LINE_BUFFER_CAPACITY, stdin) == line_buffer);

	char *remaining = line_buffer;
	char *endptr = NULL;

	while (1) {
		long num = strtol(remaining, &endptr, 10);
		assert(errno == 0);

		lanternfish[num] += 1;

		int flag = 0;

		while (!isdigit(*endptr)) {
			if (*endptr == '\0') {
				flag = 1;
				break;
			}
			endptr += 1;
		}

		if (flag) {
			break;
		}

		remaining = endptr;
		endptr = NULL;
	}

	const int days = 80;

	// Model lanternfish' growth rate.
	for (int day = 0; day < days; ++day) {
		const uint64_t timer_zero = lanternfish[0];

		for (int rem = 1; rem < LF_MAX; ++rem) {
			lanternfish[rem - 1] = lanternfish[rem];
		}

		lanternfish[6] += timer_zero;
		lanternfish[8] = timer_zero;
	}

	// Count all the lanternfish.
	uint64_t lanternfish_count = 0;
	for (int rem = 0; rem < LF_MAX; ++rem) {
		lanternfish_count += lanternfish[rem];
	}

	printf("%lu\n", lanternfish_count);

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