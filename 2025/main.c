#include <stdio.h>

#define IS_MAIN

#include "day-1/day-1.c"
#include "day-2/day-2.c"


int main(void) {
	printf(
		"\nAdvent of Code 2025\n"
		"===================\n"
	);
	day1("day-1/input.txt");
	day2("day-2/input.txt");
}
