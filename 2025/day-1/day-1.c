#include <errno.h>
#include <stdlib.h>

#include "../helpers/challenge.h"
#include "../helpers/types.h"


#define DIAL_MAX (100)
#define DIAL_START (50)
#define DIAL_MIN (0)

int day1(char *filepath) {
	struct timeval startTime;
	gettimeofday(&startTime, NULL);

	FILE *fp = fopen(filepath, "r");
	if (!fp || ferror(fp)) {
		printf("Error reading file: %s. Error #: %d\n", filepath, errno);
		return 2;
	}

	char *line = NULL;
	size_t size = 0;

	i16 dialValue = DIAL_START;
	u64 endedOnZero = 0;
	u64 sawZero = 0;

	while (getline(&line, &size, fp) != -1) {
		const i8 direction = line[0] == 'R' ? 1 : -1;
		const u16 turnValue = strtol(line + 1, NULL, 10);

		for (u16 i = 0; i < turnValue; ++i) {
			dialValue += direction;
			if (dialValue == 0) {
				++sawZero;
			} else if (dialValue == DIAL_MIN - 1) {
				dialValue = DIAL_MAX - 1;
			} else if (dialValue == DIAL_MAX) {
				dialValue = DIAL_MIN;
				++sawZero;
			}
		}

		endedOnZero += dialValue == 0;
	}

	fclose(fp);

	printChallengeSummary(1, startTime, endedOnZero, sawZero);

	return 0;
}


#ifndef IS_MAIN
int main(void) {
	day1("ex1.txt");
}
#endif
