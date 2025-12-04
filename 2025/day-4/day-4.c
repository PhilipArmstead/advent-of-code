#include <errno.h>
#include <stdlib.h>

#include "../helpers/challenge.h"
#include "../helpers/types.h"


#ifndef IS_MAIN
#define GRID_SIZE (10)
#else
#define GRID_SIZE (139)
#endif


int day4(char *filepath) {
	struct timeval startTime;
	gettimeofday(&startTime, NULL);

	FILE *fp = fopen(filepath, "r");
	if (!fp || ferror(fp)) {
		printf("Error reading file: %s. Error #: %d\n", filepath, errno);
		return 2;
	}

	char *line = NULL;
	size_t size = 0;

	char map[GRID_SIZE][GRID_SIZE] = {0};

	{
		u8 row = 0;
		while (getline(&line, &size, fp) != -1) {
			for (u8 col = 0; col < GRID_SIZE; ++col) {
				map[row][col] = line[col];
			}
			++row;
		}
	}

	u16 answerPartOne = 0;
	u16 answerPartTwo = 0;

	bool endLoop = false;
	while (!endLoop) {
		endLoop = true;

		for (u8 row = 0; row < GRID_SIZE; ++row) {
			for (u8 col = 0; col < GRID_SIZE; ++col) {
				if (map[row][col] != '@') {
					continue;
				}

				u8 adjacentRollsPartOne = 0;
				u8 adjacentRollsPartTwo = 0;
				const bool notColumn0 = col > 0;
				const bool notColumnMax = col < GRID_SIZE - 1;
				const bool notRow0 = row > 0;
				const bool notRowMax = row < GRID_SIZE - 1;
				if (notColumn0) {
					adjacentRollsPartOne += map[row][col - 1] != '.';
					adjacentRollsPartTwo += map[row][col - 1] == '@';
					if (notRow0) {
						adjacentRollsPartOne += map[row - 1][col - 1] != '.';
						adjacentRollsPartTwo += map[row - 1][col - 1] == '@';
					}
					if (notRowMax) {
						adjacentRollsPartOne += map[row + 1][col - 1] != '.';
						adjacentRollsPartTwo += map[row + 1][col - 1] == '@';
					}
				}
				if (notColumnMax) {
					adjacentRollsPartOne += map[row][col + 1] != '.';
					adjacentRollsPartTwo += map[row][col + 1] == '@';
					if (notRow0) {
						adjacentRollsPartOne += map[row - 1][col + 1] != '.';
						adjacentRollsPartTwo += map[row - 1][col + 1] == '@';
					}
					if (notRowMax) {
						adjacentRollsPartOne += map[row + 1][col + 1] != '.';
						adjacentRollsPartTwo += map[row + 1][col + 1] == '@';
					}
				}
				if (notRow0) {
					adjacentRollsPartOne += map[row - 1][col] != '.';
					adjacentRollsPartTwo += map[row - 1][col] == '@';
				}
				if (notRowMax) {
					adjacentRollsPartOne += map[row + 1][col] != '.';
					adjacentRollsPartTwo += map[row + 1][col] == '@';
				}

				if (adjacentRollsPartOne < 4) {
					++answerPartOne;
				}

				if (adjacentRollsPartTwo < 4) {
					++answerPartTwo;
					map[row][col] = 'x';
					endLoop = false;
				}
			}
		}
	}

	fclose(fp);

	printChallengeSummary(4, startTime, answerPartOne, answerPartTwo);

	return 0;
}


#ifndef IS_MAIN
int main(void) {
	day4("ex1.txt");
}
#endif
