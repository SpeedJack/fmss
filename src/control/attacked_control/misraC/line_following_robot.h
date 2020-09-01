#ifndef _misraC_line_following_robot_
#define _misraC_line_following_robot_

#include <assert.h>
#include <stdio.h>
#include "misraC_basic_types.h"
/**
 * operating modes
 */
typedef enum { AUTO } Mode;

/**
 * state attributes
 */
typedef struct { 
    Mode mode;
    Mode previous_mode;
    float64_t backwardRotate; //-- real
    float64_t forwardRotate; //-- real
    float64_t forwardSpeed; //-- real
    float64_t lfLeftVal; //-- real
    float64_t lfRightVal; //-- real
    float64_t LSR_THRESHOLD; //-- real
    float64_t servoLeftVal; //-- real
    float64_t servoRightVal; //-- real
    float64_t step_size; //-- real
    float64_t time; //-- real
} State;

/**
 * init function
 */
void init(State* st);

/**
 * triggers
 */
bool per_tick(State* st);
State* tick(State* st);


/**
 * leave/enter functions
 */
void enter(Mode m, State* st);
void leave(Mode m, State* st);

#endif
