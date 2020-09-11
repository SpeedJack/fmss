#include "line_following_robot_4S.h"

#define LSR_THRESHOLD 150.0f /* 0 = black; 255 = white; line color = white */


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
}

void enter(Mode m, State* st)
{
	st->mode = m;
}

void leave(Mode m, State* st)
{
	st->previous_mode = m;
}

State* tick(State* st)
{
	float64_t lfRightVal = 0.0f;
	float64_t lfLeftVal = 0.0f;
	if(st->mode == AUTO) {
		lfRightVal = (st->lfFarRightVal + st->lfMidRightVal) / 2.0f;
		lfLeftVal = (st->lfFarLeftVal + st->lfMidLeftVal) / 2.0f;
		if (lfRightVal <= LSR_THRESHOLD && lfLeftVal <= LSR_THRESHOLD) { /* left black, right black -> forward */
#ifdef DBG
			_dbg_print_condition("st->mode == AUTO && (lfRightVal <= LSR_THRESHOLD && lfLeftVal <= LSR_THRESHOLD)");
#endif
			leave(AUTO, st);
			st->servoLeftVal = st->forwardSpeed;
			st->servoRightVal = -st->forwardSpeed;
			enter(AUTO, st);
		} else if (lfRightVal <= LSR_THRESHOLD && lfLeftVal > LSR_THRESHOLD) { /* left black, right white -> right */
#ifdef DBG
			_dbg_print_condition("st->mode == AUTO && (lfRightVal <= LSR_THRESHOLD && lfLeftVal > LSR_THRESHOLD)");
#endif
			leave(AUTO, st);
			st->servoLeftVal = st->highRotate;
			st->servoRightVal = -st->lowRotate;
			enter(AUTO, st);
		} else if (lfRightVal > LSR_THRESHOLD && lfLeftVal <= LSR_THRESHOLD) { /* left white, right black -> left */
#ifdef DBG
			_dbg_print_condition("st->mode == AUTO && (lfRightVal > LSR_THRESHOLD && lfLeftVal <= LSR_THRESHOLD)");
#endif
			leave(AUTO, st);
			st->servoLeftVal = st->lowRotate;
			st->servoRightVal = -st->highRotate;
			enter(AUTO, st);
		} else if (lfRightVal > LSR_THRESHOLD && lfLeftVal > LSR_THRESHOLD) { /* left white, right white -> continue */
#ifdef DBG
			_dbg_print_condition("st->mode == AUTO && (lfRightVal > LSR_THRESHOLD && lfLeftVal > LSR_THRESHOLD)");
#endif
			leave(AUTO, st);
			st->servoLeftVal = st->servoLeftVal;
			st->servoRightVal = st->servoRightVal;
			enter(AUTO, st);
		}
	}

#ifdef DBG
	_dbg_print_state(st);
#endif
	return st;
}
