#ifndef _misraC_Attack_fmu_
#define _misraC_Attack_fmu_

#include <assert.h>
#include <stdio.h>
#include "misraC_basic_types.h"
/**
 * operating modes
 */
typedef enum { X1 } Mode;

/**
 * state attributes
 */
typedef struct { 
    Mode mode;
    Mode previous_mode;
    float64_t attack_time; //-- real
    float64_t attack_value; //-- real
    float64_t input; //-- real
    float64_t output; //-- real
    float64_t step_size; //-- real
    float64_t time; //-- real
    float64_t last_attack_time;
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
