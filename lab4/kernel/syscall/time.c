/** @file time.c
 *
 * @brief Kernel timer based syscall implementations
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-16
 */

#include <types.h>
#include <config.h>
#include <bits/errno.h>
#include <arm/timer.h>
#include <syscall.h>

extern volatile unsigned long timer_counter;

unsigned long time_syscall(void)
{
	return (timer_counter * OS_TIMER_RESOLUTION);
}

/** @brief Waits in a tight loop for atleast the given number of milliseconds.
 *
 * @param millis  The number of milliseconds to sleep.
 *
 * 
 */
void sleep_syscall(unsigned long millis  __attribute__((unused)))
{
	/* Invalid args or zero, then simply return */
	//if(millis <= 0)
		//return;

	/* Wait till the time, rounding-up to the nearest multiple of 10 */
	uint32_t ticks_to_sleep = timer_counter + (millis / OS_TIMER_RESOLUTION);
	while(timer_counter < ticks_to_sleep);
}