/*! \file skeleton.c
 * In this file there are the implementations
 * of the fuctions declared in fmu.h
 * along with the data needed.
 */
#include "fmu.h"
#include "misraC/sensor_output_attack_fmu.h"


State st; /*!< structure containing the state of the model */
int first = 0; /* variable for execution of setup option during first step only */

void initialize(const char* location)
{
	init(&st);
	fmiBuffer.realBuffer[1] = st.time;
	fmiBuffer.realBuffer[8] = st.output;
}

/**
 * function that performs a step of the simulation model.
 * At first the inputs of the are updated with the values fom the master algorithm
 * Then the tick function is called
 * Finally the outputs of the model are forwarded to the master algorithm
 * @param action is the action to perform. Might be used in future version
 */
void doStep(const char* action)
{
	if(first == 0) {
		st.time = fmiBuffer.realBuffer[1];
		st.step_size = fmiBuffer.realBuffer[2];
		st.cyclic = fmiBuffer.booleanBuffer[3];
		st.attack_time = fmiBuffer.realBuffer[4];
		st.attack_duration = fmiBuffer.realBuffer[5];
		st.attack_value = fmiBuffer.realBuffer[6];
		first = 1;
	}

	st.input = fmiBuffer.realBuffer[7];

	tick(&st);

	fmiBuffer.realBuffer[1] = st.time;
	fmiBuffer.realBuffer[8] = st.output;
}

void terminate()
{
}
