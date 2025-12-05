#include <errno.h>
#include <stdlib.h>

#include "../helpers/challenge.h"
#include "../helpers/types.h"


typedef struct {
	u64 start;
	u64 end;
} Range;

void mergeSortBottomUp(Range *values, u16 length);

int day5(char *filepath) {
	struct timeval startTime;
	gettimeofday(&startTime, NULL);

	FILE *fp = fopen(filepath, "r");
	if (!fp || ferror(fp)) {
		printf("Error reading file: %s. Error #: %d\n", filepath, errno);
		return 2;
	}

	char *line = NULL;
	size_t size = 0;

	u8 rangeCount = 0;
	Range ranges[200];

	u16 answerPartOne = 0;
	u64 answerPartTwo = 0;

	bool isReadingRanges = true;
	while (getline(&line, &size, fp) != -1) {
		// Encountered the line break between reading ranges and reading IDs.
		// Sort the ranges and calculate answer #2
		if (line[0] == '\n') {
			mergeSortBottomUp(ranges, rangeCount);

			u64 start = 0;
			u64 end = 0;
			for (u8 i = 0; i < rangeCount; ++i) {
				const u64 rangeStart = ranges[i].start;
				const u64 rangeEnd = ranges[i].end;

				if (rangeStart > start) {
					start = rangeStart;
				}
				if (rangeEnd >= end) {
					end = rangeEnd + 1;
				}
				answerPartTwo += end - start;
				start = start < end ? end : start;
			}

			isReadingRanges = false;
			continue;
		}

		if (isReadingRanges) {
			const u64 rangeStart = strtol(line, &line, 10);
			const u64 rangeEnd = strtol(line + 1, &line, 10);
			ranges[rangeCount++] = (Range){rangeStart, rangeEnd};
		} else {
			const u64 ingredientId = strtol(line, NULL, 10);
			for (u8 i = 0; i < rangeCount; ++i) {
				if (ingredientId >= ranges[i].start && ingredientId <= ranges[i].end) {
					++answerPartOne;
					break;
				}
			}
		}
	}

	fclose(fp);

	printChallengeSummary(5, startTime, answerPartOne, answerPartTwo);

	return 0;
}


/** bottom up merge sort */
void mergeBottomUp(const Range *values, const u16 left, const u16 right, const u16 end, Range *copy) {
	u16 i = left;
	u16 j = right;

	for (u16 k = left; k < end; k++) {
		if (i < right && (j >= end || values[i].start <= values[j].start)) {
			copy[k] = values[i];
			++i;
		} else {
			copy[k] = values[j];
			++j;
		}
	}
}

void mergeSortBottomUp(Range *values, const u16 length) {
	Range copy[length];

	for (u16 width = 1; width < length; width *= 2) {
		for (u16 i = 0; i < length; i += 2 * width) {
			const u16 iWidth = i + width;
			const u16 i2Width = i + 2 * width;
			mergeBottomUp(values, i, length < iWidth ? length : iWidth, length < i2Width ? length : i2Width, copy);
		}

		for (u16 i = 0; i < length; ++i) {
			values[i] = copy[i];
		}
	}
}


#ifndef IS_MAIN
int main(void) {
	day5("ex1.txt");
}
#endif
