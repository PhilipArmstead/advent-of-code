#include <stdio.h>

#include "day-1/day-1.c"
#include "day-2/day-2.c"
#include "day-3/day-3.c"

int main () {
	printf(
		"\nAdvent of Code 2024\n"
		"===================\n"
	);
	day1("day-1/input.txt");
	day2("day-2/input.txt");
	day3("day-3/input.txt");
}
