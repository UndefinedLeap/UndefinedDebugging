#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INST_SIZE 20

char* truncate_string_before(char* str, char delimiter){
	char* out_str = malloc(10 * sizeof(char));
	char cursor = 0;
	unsigned long len = strlen(str);
	char found = 0;
	for (int i = 0; i < len; i++) {
		if(str[i] == delimiter) found = 1;
		if(found == 1){
			out_str[cursor] = str[i];
			cursor++;
		}
	}
	out_str[cursor] = '\0';
	return out_str;
}

int char_to_int(char c){
	return c - 48;
}

int main1() {
	char ins[INST_SIZE];

	int position = 0;
	int depth = 0;

	while (fgets(ins, INST_SIZE, stdin) == ins) {
		char *space = truncate_string_before(ins, ' ');
		int offset = char_to_int(*(space + 1));
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
		free(space);
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
		char *space = truncate_string_before(ins, ' ');
		int offset = char_to_int(*(space + 1));
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
		free(space);
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
