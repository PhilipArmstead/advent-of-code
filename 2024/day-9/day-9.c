#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../helpers/challenge.h"
#include "../helpers/types.h"


int day9(char *filepath) {
	struct timeval startTime;
	gettimeofday(&startTime, NULL);

	char *line = malloc(20008);

	FILE *fp = fopen(filepath, "r");
	if (!fp || ferror(fp)) {
		printf("Error reading file: %s. Error #: %d\n", filepath, errno);
		return -1;
	}

	fgets(line, 20008, fp);
	fclose(fp);

	u64 answerPartOne = 0;
	u16 answerPartTwo = 0;

	u16 *data = malloc(131072);

	u32 head = 0;
	u16 id = 1;
	u32 length = 0;
	while (true) {
		u8 value = (line[head++] - 48);
		while (value--) {
			data[length++] = id;
		}

		if (line[head] == '\0' || line[head] == '\n') {
			break;
		}

		value = line[head++] - 48;
		while (value--) {
			data[length++] = 0;
		}

		++id;
	}

	head = 0;
	while (head < length - 1) {
		if (data[head] == 0) {
			data[head] = data[length - 1];
			--length;
		}
		++head;

		while (data[length - 1] == 0) {
			--length;
		}
	}

	for (u32 i = 0; i < length; ++i) {
		answerPartOne += (data[i] - 1) * i;
	}

	free(line);
	free(data);

	printChallengeSummary(9, startTime, answerPartOne, answerPartTwo);

	return 0;
}

#ifndef IS_MAIN

int main() {
	day9("input.txt");
}

#endif
