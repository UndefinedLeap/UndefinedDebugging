#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 20
#define ARR_SIZE 10000

int main1() {
	char ins[BUFFER_SIZE];
	int one_count[BUFFER_SIZE] = {0};

	int total_count = 0;
	size_t bin_size = 0;

	while (fgets(ins, BUFFER_SIZE, stdin) == ins) {
		total_count += 1;

		if (bin_size == 0) {
			bin_size = strlen(ins);
			if (ins[bin_size - 1] == '\n')
				bin_size -= 1;
		}

		for (size_t i = 0; ins[i] == '1' || ins[i] == '0'; ++i) {
			one_count[i] += (ins[i] == '1') ? 1 : 0;
		}
	}

	uint32_t gamma_rate = 0;
	uint32_t epsilon_rate = 0;

	for (size_t i = 0; i < bin_size; ++i) {
		int ones = one_count[i];
		gamma_rate <<= 1;
		epsilon_rate <<= 1;

		if (ones > total_count - ones) {
			gamma_rate |= 1;
		} else {
			epsilon_rate |= 1;
		}
	}

	printf("%d\n", gamma_rate * epsilon_rate);

	return 0;
}

int main2() {
	char ins[BUFFER_SIZE];
	int one_count[BUFFER_SIZE] = {0};

	int arr[ARR_SIZE] = {0};

	int total_count = 0;
	size_t bin_size = 0;
	size_t arr_size = 0;

	for (; fgets(ins, BUFFER_SIZE, stdin) == ins; ++arr_size) {
		arr[arr_size] = (int) strtol(ins, NULL, 2);

		if (bin_size == 0) {
			bin_size = strlen(ins);
			if (ins[bin_size - 1] == '\n')
				bin_size -= 1;
		}

		for (size_t i = 0; ins[i] == '1' || ins[i] == '0'; ++i) {
			one_count[i] += (ins[i] == '1') ? 1 : 0;
		}
	}

	int oxygen_filter = 0;
	int co2_filter = 0;

	int oxygen_generator_rating = 0;
	int co2_scruber_rating = 0;

	int oxygen_count = total_count;
	int co2_count = total_count;

	int oxygen_ones = one_count[0];
	int co2_ones = one_count[0];

	for (size_t i = 0; i < bin_size; ++i) {
		oxygen_filter <<= 1;
		co2_filter <<= 1;

		if (oxygen_ones >= oxygen_count - oxygen_ones) {
			oxygen_filter |= 1;
		}

		if (co2_ones < co2_count - co2_ones) {
			co2_filter |= 1;
		}

		int shift = (int) (bin_size - i - 1);

		if (oxygen_count != 1) {
			oxygen_count = 0;
			oxygen_ones = 0;

			for (size_t j = 0; j < arr_size; ++j) {
				if ((arr[j] >> shift) == oxygen_filter) {
					oxygen_generator_rating = arr[j];
					oxygen_count += 1;
					oxygen_ones += arr[j] >> (shift - 1) & 1;
				}
			}
		}

		if (co2_count != 1) {
			co2_count = 0;
			co2_ones = 0;

			for (size_t j = 0; j < arr_size; ++j) {
				if ((arr[j] >> shift) == co2_filter) {
					co2_scruber_rating = arr[j];
					co2_count += 1;
					co2_ones += arr[j] >> (shift - 1) & 1;
				}
			}
		}
	}

	printf("%d\n", oxygen_generator_rating * co2_scruber_rating);

	return 0;
}

int main() {
#ifdef PART1
	main1();
#else
	main2();
#endif
}
