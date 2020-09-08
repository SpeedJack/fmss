#ifndef _misraC_actuator_scale_attack_fmu_
#define _misraC_actuator_scale_attack_fmu_

#include <assert.h>
#include <stdio.h>
#include "misraC_basic_types.h"

typedef enum { X1 } Mode;

typedef struct { 
	Mode mode;
	Mode previous_mode;
	float64_t time;
	float64_t step_size;
	bool cyclic;
	float64_t attack_time;
	float64_t attack_duration;
	float64_t attack_value;
	float64_t input;
	float64_t output;
} State;

void init(State* st);

bool per_tick(State* st);
State* tick(State* st);

void enter(Mode m, State* st);
void leave(Mode m, State* st);

#endif
