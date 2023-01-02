#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_CAPACITY 1000
#define CRAB_CAPACITY 1200

#define FX 1000
#define FY 1000

#define PQCAP 3

typedef struct {
	int elements[PQCAP];
} PriorityQueue;

void pq_new(PriorityQueue *pq) {
	assert(pq != NULL);

	for (size_t i = 0; i < PQCAP; ++i) {
		pq->elements[i] = INT_MIN;
	}
}

void pq_insert(PriorityQueue *pq, int x) {
	size_t index = 0;

	for (index = 0; index < PQCAP; ++index) {
		if (pq->elements[index] < x)
			break;
	}

	for (size_t other = PQCAP; other > index; --other) {
		pq->elements[other] = pq->elements[other - 1];
	}

	if (index < PQCAP) {
		pq->elements[index] = x;
	}
}

void pq_log(PriorityQueue *pq) {
	printf("PQ: ");
	for (size_t i = 0; i < PQCAP; ++i) {
		printf("%d, ", pq->elements[i]);
	}
	printf("\n");
}

int idx(int y, int x, int n) { return y * n + x; }

int floor_traverse(int *floor, const int floor_x, const int floor_y, const int x, const int y) {
	assert(x >= 0 && x < floor_x && y >= 0 && y < floor_y);

	int current = floor[idx(y, x, floor_x)];

	if (current == 9) {
		return 0;
	}

	int count = 1;

	floor[idx(y, x, floor_x)] = 9;

	// If the neighbor (nx, ny) is valid then try and traverse it.
#define TRY_TRAVERSE(nx, ny)                                                                       \
	if (nx >= 0 && nx < floor_x && ny >= 0 && ny < floor_y &&                                      \
		floor[idx(ny, nx, floor_x)] > current)                                                     \
		count += floor_traverse(floor, floor_x, floor_y, nx, ny);

	TRY_TRAVERSE(x - 1, y);
	TRY_TRAVERSE(x + 1, y);
	TRY_TRAVERSE(x, y - 1);
	TRY_TRAVERSE(x, y + 1);

#undef TRY_TRAVERSE

	return count;
}

void floor_copy(const int *floor, const int floor_x, const int floor_y, int *new_floor) {
	for (int y = 0; y < floor_y; ++y) {
		for (int x = 0; x < floor_x; ++x) {
			new_floor[idx(y, x, floor_x)] = floor[idx(y, x, floor_x)];
		}
	}
}

void floor_log(const int *floor, const int floor_x, const int floor_y) {
	printf("FLOOR:\n");

	for (int y = 0; y < floor_y; ++y) {
		for (int x = 0; x < floor_x; ++x) {
			putchar('0' + floor[idx(y, x, floor_x)]);
		}
		putchar('\n');
	}
	printf("\n\n");
}

int main() {
	char line_buffer[LINE_CAPACITY];

	int floor_x = 0;
	int floor_y = 0;
	int floor[FY * FX];

	for (size_t i = 0; i < FY * FX; ++i) {
		floor[i] = INT_MAX;
	}

	size_t linear_index = 0;

	while (fgets(line_buffer, LINE_CAPACITY, stdin) == line_buffer) {
		floor_x = 0;

		for (size_t x = 0; line_buffer[x] >= '0' && line_buffer[x] <= '9'; ++x) {
			floor[linear_index] = line_buffer[x] - '0';
			linear_index += 1;
			floor_x += 1;
		}

		floor_y += 1;
	}

#ifdef PART1
	int sum_of_risk_levels = 0;
#else
	PriorityQueue pq[1];
	pq_new(pq);
#endif

	for (int y = 0; y < floor_y; ++y) {
		for (int x = 0; x < floor_x; ++x) {
			int lower_neighbors = 0;

#define TRY_INCREMENT(nx, ny)                                                                      \
	if (nx >= 0 && nx < floor_x && ny >= 0 && ny < floor_y &&                                      \
		floor[idx(ny, nx, floor_x)] <= floor[idx(y, x, floor_x)])                                  \
		lower_neighbors += 1;

			TRY_INCREMENT(x - 1, y);
			TRY_INCREMENT(x + 1, y);
			TRY_INCREMENT(x, y - 1);
			TRY_INCREMENT(x, y + 1);

#undef TRY_INCREMENT

			if (lower_neighbors != 0)
				continue;

#ifdef PART1
			sum_of_risk_levels += floor[idx(y, x, floor_x)] + 1;
#else
			int *new_floor = (int *) malloc((size_t) (floor_x * floor_y) * sizeof(int));
			floor_copy((const int *) floor, floor_x, floor_y, new_floor);

			const int basin_size = floor_traverse(new_floor, floor_x, floor_y, x, y);

			free(new_floor);

			pq_insert(pq, basin_size);
			// pq_log(pq);
#endif
		}
	}

#ifdef PART1
	printf("%d\n", sum_of_risk_levels);
#else
	int sizes_multiple = 1;

	for (size_t i = 0; i < 3; ++i) {
		sizes_multiple *= pq->elements[i];
	}

	printf("%d\n", sizes_multiple);
#endif

	return 0;
}
