#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define LINE_CAPACITY 1000
#define CRAB_CAPACITY 1200
#define LINES_CAPACITY 500

int cmp_u64(const void *left, const void *right) {
	uint64_t x = *(uint64_t *) left;
	uint64_t y = *(uint64_t *) right;
	if (x < y)
		return -1;
	if (x == y)
		return 0;
	return 1;
}

int main1() {
	char line_buffer[LINE_CAPACITY];

	char closures[128] = {'\0'};
	closures[')'] = '(';
	closures[']'] = '[';
	closures['}'] = '{';
	closures['>'] = '<';

	uint64_t total_syntax_error_score = 0;

	uint64_t line_scores[LINES_CAPACITY] = {0};
	size_t lines_count = 0;

	while (fgets(line_buffer, LINE_CAPACITY, stdin) == line_buffer) {
		for (size_t idx = 0; line_buffer[idx] != '\0'; ++idx) {
			if (line_buffer[idx] == '\n')
				line_buffer[idx] = '\0';
		}

		size_t idx = 0;
		char charstack[LINE_CAPACITY] = {'\0'};
		size_t stack_ptr = 0;

		int corrupted_flag = 0;

		for (; line_buffer[idx] != '\0'; ++idx) {
			const char c = line_buffer[idx];

			if (c == '(' || c == '[' || c == '{' || c == '<') {
				charstack[stack_ptr] = c;
				stack_ptr += 1;
				continue;
			}

			if (stack_ptr == 0 || charstack[stack_ptr - 1] != closures[(size_t) c]) {
				switch (c) {
					case ')':
						total_syntax_error_score += 3;
						break;
					case ']':
						total_syntax_error_score += 57;
						break;
					case '}':
						total_syntax_error_score += 1197;
						break;
					case '>':
						total_syntax_error_score += 25137;
						break;
						
				}

				corrupted_flag = 1;
				break;
			}

			stack_ptr -= 1;
			charstack[stack_ptr] = '\0';
		}

		if (corrupted_flag) {
			continue;
		}

		uint64_t total_score = 0;

		while (stack_ptr > 0) {
			total_score *= 5;

			switch (charstack[stack_ptr - 1]) {
				case '<':
					total_score += 4;
					break;
				case '{':
					total_score += 3;
					break;
				case '[':
					total_score += 2;
					break;
				case '(':
					total_score += 1;
					break;
			}

			stack_ptr -= 1;
		}

		line_scores[lines_count] = total_score;
		lines_count += 1;
	}

	printf("%"PRIu64"\n", total_syntax_error_score);

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