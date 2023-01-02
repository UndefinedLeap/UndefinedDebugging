#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10000
#define ARR_SIZE 10000
#define BOARDS_COUNT 10000

int main1() {
	char ins[BUFFER_SIZE];
	int boards[BOARDS_COUNT][5][5];
	int board_count = 0;
	int arr[ARR_SIZE] = {0};

	assert(fgets(ins, BUFFER_SIZE, stdin) == ins);
	int eof = 0;

	for (;; ++board_count) {
		for (int y = 0; y < 5; ++y) {
			for (int x = 0; x < 5; ++x) {
				if (scanf("%d", &boards[board_count][y][x]) == EOF) {
					eof = 1;
					break;
				}
			}
		}

		if (eof)
			break;
	}

	int arr_size = 0;
	char *nums = ins;

	for (;; ++arr_size) {
		char *after = NULL;

		errno = 0;

		arr[arr_size] = (int) strtol(nums, &after, 10);

		if (errno != 0 || after[0] == '\0') {
			break;
		}

		// Skip over the comma with `+ 1`.
		nums = after + 1;
	}

	int ans = 0;

	for (int i = 0; i < arr_size; ++i) {
		const int num = arr[i];
		int done = 0;

		for (int j = 0; j < board_count; ++j) {
			for (int y = 0; y < 5; ++y) {
				for (int x = 0; x < 5; ++x) {
					if (boards[j][y][x] == num) {
						boards[j][y][x] = -1;
					}
				}
			}
		}

		for (int j = 0; j < board_count; ++j) {
			int s = 0;

			for (int y = 0; y < 5; ++y) {
				int c = 0;

				for (int x = 0; x < 5; ++x) {
					if (boards[j][y][x] < 0) {
						c += 1;
					} else {
						s += boards[j][y][x];
					}
				}

				if (done == 0 && c == 5) {
					done = 1;
				}
			}

			if (done) {
				ans = s * num;
				break;
			}

			done = 0;

			for (int x = 0; x < 5; ++x) {
				int c = 0;

				for (int y = 0; y < 5; ++y) {
					if (boards[j][y][x] < 0) {
						c += 1;
					}
				}

				if (done == 0 && c == 5) {
					done = 1;
				}
			}

			if (done) {
				ans = s * num;
				break;
			}
		}

		if (done)
			break;
	}

	printf("%d\n", ans);

	return 0;
}

int main2() {
	char ins[BUFFER_SIZE];
	int boards[BOARDS_COUNT][5][5];
	int board_count = 0;
	int arr[ARR_SIZE] = {0};

	assert(fgets(ins, BUFFER_SIZE, stdin) == ins);
	int eof = 0;

	for (;; ++board_count) {
		for (int y = 0; y < 5; ++y) {
			for (int x = 0; x < 5; ++x) {
				if (scanf("%d", &boards[board_count][y][x]) == EOF) {
					eof = 1;
					break;
				}
			}
		}

		if (eof)
			break;
	}

	int arr_size = 0;
	char *nums = ins;

	for (;; ++arr_size) {
		char *after = NULL;

		errno = 0;

		arr[arr_size] = (int) strtol(nums, &after, 10);

		if (errno != 0 || after[0] == '\0') {
			break;
		}

		// Skip over the comma with `+ 1`.
		nums = after + 1;
	}

	int ans = 0;
	int won = 0;
	int won_boards[BOARDS_COUNT] = { 0 };

	for (int i = 0; i < arr_size; ++i) {
		if (won >= board_count) {
			break;
		}

		const int num = arr[i];

		for (int j = 0; j < board_count; ++j) {
			for (int y = 0; y < 5; ++y) {
				for (int x = 0; x < 5; ++x) {
					if (boards[j][y][x] == num) {
						boards[j][y][x] = -1;
					}
				}
			}
		}

		int done = 0;

		for (int j = 0; j < board_count; ++j) {
			if (won_boards[j])
				continue;

			int s = 0;

			for (int y = 0; y < 5; ++y) {
				for (int x = 0; x < 5; ++x) {
					if (boards[j][y][x] >= 0) {
						s += boards[j][y][x];
					}
				}
			}

			for (int y = 0; y < 5; ++y) {
				int c = 0;

				for (int x = 0; x < 5; ++x) {
					if (boards[j][y][x] < 0) {
						c += 1;
					}
				}

				if (done == 0 && c == 5) {
					done = 1;
					break;
				}
			}

			if (done) {
				done = 0;
				ans = s * num;
				won += 1;
				won_boards[j] = 1;
				continue;
			}

			done = 0;

			for (int x = 0; x < 5; ++x) {
				int c = 0;

				for (int y = 0; y < 5; ++y) {
					if (boards[j][y][x] < 0) {
						c += 1;
					}
				}

				if (done == 0 && c == 5) {
					done = 1;
					break;
				}
			}

			if (done) {
				done = 0;
				ans = s * num;
				won += 1;
				won_boards[j] = 1;
				continue;
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}

int main() {
#ifdef PART1
	main1();
#else
	main2();
#endif
}
