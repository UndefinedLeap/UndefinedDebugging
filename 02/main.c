#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INST_SIZE 20

int main1() {
	char ins[INST_SIZE];

	int position = 0;
	int depth = 0;

	while (fgets(ins, INST_SIZE, stdin) == ins) {
		char *space = strchr(ins, ' ');
		int offset = (int) strtol(space + 1, NULL, 10);
		switch (ins[0]) {
			case 'f':
				position += offset;
				break;
			case 'd':
				depth += offset;
				break;
			case 'u':
				depth -= offset;
				break;
			default:
				assert(0 && "Invalid instruction");
				break;
		}
	}

	printf("%d\n", position * depth);

	return 0;
}

int main2() {
	char ins[INST_SIZE];

	int position = 0;
	int depth = 0;
	int aim = 0;

	while (fgets(ins, INST_SIZE, stdin) == ins) {
		char *space = strchr(ins, ' ');
		int offset = (int) strtol(space + 1, NULL, 10);
		switch (ins[0]) {
			case 'f':
				position += offset;
				depth += aim * offset;
				break;
			case 'd':
				aim += offset;
				break;
			case 'u':
				aim -= offset;
				break;
			default:
				assert(0 && "Invalid instruction");
				break;
		}
	}

	printf("%d\n", position * depth);

	return 0;
}

int main() {
#ifdef PART1
	main1();
#else
	main2();
#endif
}
