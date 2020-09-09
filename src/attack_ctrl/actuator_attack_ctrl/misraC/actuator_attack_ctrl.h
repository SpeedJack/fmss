#ifndef _misraC_complementary_attack_ctrl_
#define _misraC_complementary_attack_ctrl_

#include <assert.h>
#include <stdio.h>
#include "misraC_basic_types.h"

typedef enum { AUTO } Mode;

typedef struct {
	Mode mode;
	Mode previous_mode;
	float64_t forwardSpeed;
	float64_t highRotate;
	float64_t lfFarLeftVal;
	float64_t lfFarRightVal;
	float64_t lfMidLeftVal;
	float64_t lfMidRightVal;
	float64_t lowRotate;
	float64_t mediumRotate;
	float64_t servoLeftVal;
	float64_t servoRightVal;
	float64_t attack_time;
	float64_t attack_duration;
	float64_t time;
	float64_t step_size;	
	
} State;

void init(State* st);

bool per_tick(State* st);
void sensor_attack(State* st);
State* tick(State* st);

void enter(Mode m, State* st);
void leave(Mode m, State* st);

#endif
