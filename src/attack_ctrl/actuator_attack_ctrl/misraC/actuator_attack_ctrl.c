#include "actuator_attack_ctrl.h"

#define LSR_THRESHOLD 150.0f

void init(State* st)
{
	st->previous_mode = AUTO;
	st->mode = AUTO;
	st->forwardSpeed = 0.4f;
	st->highRotate = 0.3f;
	st->lfFarLeftVal = 0.0f;
	st->lfFarRightVal = 0.0f;
	st->lfMidLeftVal = 0.0f;
	st->lfMidRightVal = 0.0f;
	st->lowRotate = 0.0f;
	st->mediumRotate = 0.2f;
	st->servoLeftVal = 0.0f;
	st->servoRightVal = 0.0f;
	st->attack_time = 0.0f;
	st->attack_duration = 0.0f;
	st->time = 0.0f;
	st->step_size = 0.1f;
}

void enter(Mode m, State* st)
{
	st->mode = m;
}

void leave(Mode m, State* st)
{
	st->previous_mode = m;
}

void actuator_attack(State* st) {
	/*Reset for cyclic attack*/
	
	if (st->mode == AUTO && st->attack_duration > 0.0f && ((st->time + 0.00001f) > (st->attack_time + st->attack_duration)))
		st->time = 0;

	/*Attack if in [attack_time, attack_time + attack_duration]*/
	if (st->mode == AUTO && ((st->time + 0.00001f) > st->attack_time) && ((st->attack_duration - 0.00001f) <= 0.0f || ((st->time - st->attack_time + 0.00001f) < st->attack_duration)) && ((st->time - st->attack_time + 0.00001f) < (st->attack_duration))) {
		st->servoLeftVal = - st->forwardSpeed;
		st->servoRightVal = st->forwardSpeed;
	}

	st->time = st->time + st->step_size;
	
}

State* tick(State* st)
{
	float64_t lfRightVal = 0.0f;
	float64_t lfLeftVal = 0.0f;
	if(st->mode == AUTO) {
		
		lfRightVal = (st->lfFarRightVal + st->lfMidRightVal) / 2.0f;
		lfLeftVal = (st->lfFarLeftVal + st->lfMidLeftVal) / 2.0f;

		if (lfRightVal <= LSR_THRESHOLD && lfLeftVal <= LSR_THRESHOLD) {
#ifdef DBG
			_dbg_print_condition("st->mode == AUTO && (lfRightVal <= LSR_THRESHOLD && lfLeftVal <= LSR_THRESHOLD)");
#endif
			leave(AUTO, st);
			st->servoLeftVal = st->forwardSpeed;
			st->servoRightVal = -st->forwardSpeed;
			enter(AUTO, st);
		} else if (lfRightVal <= LSR_THRESHOLD && lfLeftVal > LSR_THRESHOLD) {
#ifdef DBG
			_dbg_print_condition("st->mode == AUTO && (lfRightVal <= LSR_THRESHOLD && lfLeftVal > LSR_THRESHOLD)");
#endif
			leave(AUTO, st);
			st->servoLeftVal = st->highRotate;
			st->servoRightVal = -st->lowRotate;
			enter(AUTO, st);
		} else if (lfRightVal > LSR_THRESHOLD && lfLeftVal <= LSR_THRESHOLD) {
#ifdef DBG
			_dbg_print_condition("st->mode == AUTO && (lfRightVal > LSR_THRESHOLD && lfLeftVal <= LSR_THRESHOLD)");
#endif
			leave(AUTO, st);
			st->servoLeftVal = st->lowRotate;
			st->servoRightVal = -st->highRotate;
			enter(AUTO, st);
		} else if (lfRightVal > LSR_THRESHOLD && lfLeftVal > LSR_THRESHOLD) {
#ifdef DBG
			_dbg_print_condition("st->mode == AUTO && (lfRightVal > LSR_THRESHOLD && lfLeftVal > LSR_THRESHOLD)");
#endif
			leave(AUTO, st);
			st->servoLeftVal = st->servoLeftVal;
			st->servoRightVal = st->servoRightVal;
			enter(AUTO, st);
		}
		actuator_attack(st);
	}
	
#ifdef DBG
	_dbg_print_state(st);
#endif
	return st;
}
