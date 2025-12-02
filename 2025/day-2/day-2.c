#include <errno.h>
#include <math.h>
#include <stdlib.h>

#include "../helpers/challenge.h"
#include "../helpers/types.h"


typedef struct {
	u64 value;
	u8 log10;
	bool hasEvenDigits;
} Range;

int day2(char *filepath) {
	struct timeval startTime;
	gettimeofday(&startTime, NULL);

	FILE *fp = fopen(filepath, "r");
	if (!fp || ferror(fp)) {
		printf("Error reading file: %s. Error #: %d\n", filepath, errno);
		return 2;
	}

	char *line = NULL;
	size_t size = 0;

	u64 answerPartOne = 0;
	u64 answerPartTwo = 0;

	Range start;
	Range end;

	while (getline(&line, &size, fp) != -1) {
		while (line[0] != '\0' && line[0] != '\n') {
			start.value = strtol(line, &line, 10);
			end.value = strtol(line + 1, &line, 10);
			++line;

			start.log10 = log10(start.value);
			end.log10 = log10(end.value);
			start.hasEvenDigits = start.log10 & 1;
			end.hasEvenDigits = end.log10 & 1;

			// Only numbers with an even number of digits can contain doubles (duh)
			if (!start.hasEvenDigits && !end.hasEvenDigits) {
				continue;
			}

			// If only the start or end has even digits, we need to adjust the range
			if (!start.hasEvenDigits) {
				start.value = pow(10, start.log10 + 1);
				start.log10++;
				start.hasEvenDigits = true;
			}
			if (!end.hasEvenDigits) {
				end.value = pow(10, end.log10) - 1;
				end.log10--;
				end.hasEvenDigits = true;
			}

			u32 power;
			switch (start.log10) {
				default:
				case 1:
					power = 10;
					break;
				case 3:
					power = 100;
					break;
				case 5:
					power = 1000;
					break;
				case 7:
					power = 10000;
					break;
				case 9:
					power = 100000;
					break;
			}

			// If range < power, build double by duplicating left half
			//	and check if it's within range.
			// if (range < power) {
			// 	const u32 leftHalf = start.value / power;
			// 	const u64 d = leftHalf * power + leftHalf;
			//
			// 	if (start.value <= d && d <= end.value) {
			// 		answerPartOne += d;
			// 	}
			//
			// 	continue;
			// }

			const u64 leftHalf = start.value / power;
			u64 d = leftHalf * power + leftHalf;
			if (d < start.value) {
				d += power + 1;
			}

			while (d <= end.value) {
				answerPartOne += d;
				d += power + 1;
			}

			// Take the start, find the nearest double.
			// If it's < start, find the next.
			// Adding 11, 111, 1111, etc will get the next double.
			// Then keep adding until > end.

			// For 2-digit numbers:
			//	floor(range / 10) gives the number of doubles in the range
			//	e.g. 13-23 has 1 double (22)
			//	and +1 if the start is also a double
			// As the number of digits increases by 2, the divisor increases by 10*
			//	So for 4-digit numbers, it's floor(range / 100)
			//	For 6=digit numbers, it's floor(range / 1000)
			// To check doubles, divide the 2-digit number by 10 and check the remainder.
			//	If the division result == the remainder result, it's a double.
			//	This value (10) also increases by a factor of 10 for every 2 digits.
			// If the end number is a double, add one to the doubles list.
		}
	}


	fclose(fp);

	printChallengeSummary(2, startTime, answerPartOne, answerPartTwo);

	return 0;
}


#ifndef IS_MAIN
int main(void) {
	day2("input.txt"); // Answers are 1227775554, 0
}
#endif
