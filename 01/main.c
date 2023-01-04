#include <stdio.h>

int main1() {
	int x, y;
	scanf("%d", &x);

	int c;

	while (scanf("%d", &y) != EOF) {
		if (y > x)
			c += 1;
		x = y;
	}

	printf("%d\n", c);

	return 0;
}

int main2() {
	int x, y, z;

	scanf("%d", &x);
	scanf("%d", &y);
	scanf("%d", &z);

	int s = x + y + z;
	int n;

	int c = 0;

	while (scanf("%d", &n) != EOF) {
		if (s - x + n > s)
			c += 1;

		s -= x;
		s += n;
		x = y;
		y = z;
		z = n;
	}

	printf("%d\n", c);

	return 0;
}

int main() {
#ifdef PART1
	main1();
#else
	main2();
#endif
}
