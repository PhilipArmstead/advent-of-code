#pragma once

#include <stdio.h>
#include <sys/time.h>

#include "types.h"


static void printChallengeSummary(
	const char day,
	const struct timeval startTime,
	const u64 answerPartOne,
	const u64 answerPartTwo
) {
	struct timeval now;
	gettimeofday(&now, NULL);

	u64 duration = now.tv_sec * (u32) 1e6 + now.tv_usec - (startTime.tv_sec * (u32) 1e6 + startTime.tv_usec);

	char *timeChar = "μ";
	if (duration > 3000000) {
		duration /= 1000000;
		timeChar = "";
	} else if (duration > 3000) {
		duration /= 1000;
		timeChar = "m";
	}

	printf(
		"Day %d (ran in %ld%ss)\n"
		"-----\n"
		"Part one: %lu\n"
		"Part two: %lu\n\n",
		day,
		duration,
		timeChar,
		answerPartOne,
		answerPartTwo
	);
}

