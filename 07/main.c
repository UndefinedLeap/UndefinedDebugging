#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_BUFFER_CAPACITY 10000
#define CRAB_CAPACITY 1200

int main1() {
	char line_buffer[LINE_BUFFER_CAPACITY];
	int crabs[CRAB_CAPACITY] = {0};
	int crabs_count = 0;

	assert(fgets(line_buffer, LINE_BUFFER_CAPACITY, stdin) == line_buffer);

	char *remaining = line_buffer;
	char *endptr = NULL;

	while (1) {
		long num = strtol(remaining, &endptr, 10);
		assert(errno == 0);

		crabs[crabs_count] = (int) num;
		crabs_count += 1;

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

	int min = INT_MAX;
	int max = INT_MIN;

	for (int i = 0; i < crabs_count; ++i) {
		const int c = crabs[i];

		if (c < min)
			min = c;

		if (c > max)
			max = c;
	}

	uint64_t min_fuel_cost = (uint64_t) -1;

	for (int chosen = min; chosen <= max; ++chosen) {
		uint64_t fuel_cost = 0;

		for (int i = 0; i < crabs_count; ++i) {
			const int c = crabs[i];
			const uint64_t change = (uint64_t) ((c >= chosen) ? (c - chosen) : (chosen - c));
			fuel_cost += change;
		}

		if (fuel_cost < min_fuel_cost) {
			min_fuel_cost = fuel_cost;
		}
	}

	printf("%" PRIu64 "\n", min_fuel_cost);

	return 0;
}

int main(){
#ifdef PART1
	main1();
#else
	printf("There no part-2!");
#endif
	return 0;
}