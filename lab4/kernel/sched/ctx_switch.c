/** @file ctx_switch.c
 * 
 * @brief C wrappers around assembly context switch routines.
 *
 * @author: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 *
 * @date:   Nov 18, 2013 9:00 PM
 */
 
#include <types.h>
#include <assert.h>

#include <config.h>
#include <kernel.h>
#include <arm/exception.h>
#include <arm/psr.h>
#include <inline.h>

#include "sched_i.h"

#ifdef DEBUG_MUTEX
#include <exports.h>
#endif

static __attribute__((unused)) tcb_t* cur_tcb; /* use this if needed */

/**
 * @brief Initialize the current TCB and priority.
 *
 * Set the initialization thread's priority to IDLE so that anything
 * will preempt it when dispatching the first task.
 */
void dispatch_init(tcb_t* idle __attribute__((unused)))
{
		
}


/**
 * @brief Context switch to the highest priority task while saving off the 
 * current task state.
 *
 * This function needs to be externally synchronized.
 * We could be switching from the idle task.  The priority searcher has been tuned
 * to return IDLE_PRIO for a completely empty run_queue case.
 */
void dispatch_save(void)
{
	uint8_t next_highest_prio;
    tcb_t *next_tcb, *prev_tcb;

	/* Add the task back to the runqueue */
    runqueue_add(cur_tcb, cur_tcb->cur_prio);

    /* Take the next highest priority task and remove it from the queue */
    next_highest_prio = highest_prio();
    next_tcb = runqueue_remove(next_highest_prio);

    prev_tcb = cur_tcb;
    cur_tcb = next_tcb;
	disable_interrupts();
	//printf("SB=%u\n", highest_prio());
 	ctx_switch_full((sched_context_t*) &(next_tcb->context),
 		(sched_context_t*) &(prev_tcb->context));
	//printf("SA=%u\n", highest_prio());
 	enable_interrupts();
}

/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * don't save the current task state.
 *
 * There is always an idle task to switch to.
 */
void dispatch_nosave(void)
{
	uint8_t next_highest_prio;
    tcb_t *next_tcb;

     /* Take the next highest priority task and remove it from the queue */
    next_highest_prio = highest_prio();
    printf("NS=%u\n", highest_prio());
    next_tcb = runqueue_remove(next_highest_prio);
    printf("1=%u\n", next_tcb->native_prio);
    cur_tcb = next_tcb;
    ctx_switch_half((sched_context_t*) &(next_tcb->context));
}


/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * and save the current task but don't mark is runnable.
 *
 * There is always an idle task to switch to.
 */
void dispatch_sleep(void)
{
	uint8_t next_highest_prio;
    tcb_t *next_tcb, *prev_tcb;

	/* Take the next highest priority task and remove it from the queue */
    next_highest_prio = highest_prio();
    next_tcb = runqueue_remove(next_highest_prio);

    prev_tcb = cur_tcb;
    cur_tcb = next_tcb;
	disable_interrupts();
	printf("LB=%u\n", highest_prio());
 	ctx_switch_full((sched_context_t*) &(next_tcb->context),
 		(sched_context_t*) &(prev_tcb->context));
	printf("LA=%u\n", highest_prio());
	enable_interrupts();
}

/**
 * @brief Returns the priority value of the current task.
 */
uint8_t get_cur_prio(void)
{
	return cur_tcb->cur_prio;
}

/**
 * @brief Returns the TCB of the current task.
 */
tcb_t* get_cur_tcb(void)
{
	return cur_tcb;
}
