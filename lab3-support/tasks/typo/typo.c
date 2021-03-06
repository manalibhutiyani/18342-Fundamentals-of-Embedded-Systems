/** @file typo.c
 *
 * @brief Echos characters back with timing data.
 *
 * Links to libc.
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *		   Group Member 2: Jiten Mehta <jitenm>
 *		   Group Member 3: Ankit Chheda <achheda>
 *

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 120

int main(int argc, char** argv)
{
	char input[MAX_LINE_LENGTH];
	unsigned long orig_time, final_time, time_to_type;
	int r;
	unsigned long x;

	while(1)
	{
		write(STDOUT_FILENO, "> ", 2);
		orig_time = time();
		r = read(STDIN_FILENO, input, MAX_LINE_LENGTH);
		final_time = time();
		write(STDOUT_FILENO, input, r);
		time_to_type = final_time - orig_time;
		x = time_to_type / 1000;
		printf("\n%lu.", x);
		x = time_to_type - (x * 1000);
		if (x < 100)
		{
			printf("0");
			if (x < 10)
			{
				printf("0");
			}
		}
		printf("%lus\n", x);
	}
	return 0;
}
