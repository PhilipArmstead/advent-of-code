#include <errno.h>
#include <math.h>
#include <stdlib.h>

#include "../helpers/challenge.h"
#include "../helpers/types.h"


#define PART_TWO_BATTERY_COUNT (12)

int day3(char *filepath) {
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

	while (getline(&line, &size, fp) != -1) {
		u8 first = 0;
		u8 second = 0;
		u8 partTwoValues[PART_TWO_BATTERY_COUNT] = {0};
		while (line[0] != '\0' && line[0] != '\n') {
			const u8 value = line[0] - '0';

			// Part one
			if (value > first && line[1] != '\n' && line[1] != '\0') {
				first = value;
				second = 0;
			} else if (value > second) {
				second = value;
			}

			// Part two
			for (u8 i = 0; i < PART_TWO_BATTERY_COUNT; ++i) {
				const u8 endOfLineIndex = PART_TWO_BATTERY_COUNT - 1 - i;
				if (value > partTwoValues[i] && line[endOfLineIndex] != '\n' && line[endOfLineIndex] != '\0') {
					partTwoValues[i] = value;
					for (u8 j = i + 1; j < PART_TWO_BATTERY_COUNT; ++j) {
						partTwoValues[j] = 0;
					}
					break;
				}
			}

			++line;
		}

		const u8 joltage = first * 10 + second;
		answerPartOne += joltage;

		u8 i = PART_TWO_BATTERY_COUNT;
		while (i--) {
			const u64 joltagePartial = partTwoValues[i] * (u64) pow(10, PART_TWO_BATTERY_COUNT - i - 1);
			answerPartTwo += joltagePartial;
		}
	}

	fclose(fp);

	printChallengeSummary(3, startTime, answerPartOne, answerPartTwo);

	return 0;
}


#ifndef IS_MAIN
int main(void) {
	day3("ex1.txt");
}
#endif
