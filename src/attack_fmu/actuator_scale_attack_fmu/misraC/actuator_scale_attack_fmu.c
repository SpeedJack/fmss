#include "actuator_scale_attack_fmu.h"

void init(State* st)
{
	st->previous_mode = X1;
	st->mode = X1;
	st->time = 0.0f;
	st->step_size = 0.1f;
	st->cyclic = false;
	st->attack_time = 5.0f;
	st->attack_duration = 5.0f;
	st->attack_value = 2.0f;
	st->input = 0.0f;
	st->output = 0.0f;
}

void enter(Mode m, State* st)
{
	st->mode = m;
}

void leave(Mode m, State* st)
{
	st->previous_mode = m;
}

bool per_tick(State* st)
{
	return st->mode == X1;
}

State* tick(State* st)
{
	assert(per_tick(st));

	if (st->mode == X1 && st->cyclic && st->attack_duration > 0.0f && ((st->time + 0.00001f) > (st->attack_time + st->attack_duration)))
		st->time = 0;

	if (st->mode == X1 && ((st->time + 0.00001f) < st->attack_time)) {
#ifdef DBG
		_dbg_print_condition("st->mode == X1 && ((st->time + 0.00001f) < st->attack_time)");
#endif
		leave(X1, st);
		st->output = st->input;
		st->time = st->time + st->step_size;
		enter(X1, st);
	} else if (st->mode == X1 && ((st->time + 0.00001f) > st->attack_time) && ((st->attack_duration - 0.00001f) <= 0.0f || ((st->time - st->attack_time + 0.00001f) < st->attack_duration)) && ((st->time - st->attack_time + 0.00001f) < (st->attack_duration / 2))) {
#ifdef DBG
		_dbg_print_condition("st->mode == X1 && ((st->time + 0.00001f) > st->attack_time) && ((st->attack_duration - 0.00001f) <= 0.0f || ((st->time - st->attack_time + 0.00001f) < st->attack_duration)) && ((st->time - st->attack_time + 0.00001f) < (st->attack_duration / 2))");
#endif
		leave(X1, st);
		st->output = st->input * st->attack_value;
		st->time = st->time + st->step_size;
		enter(X1, st);
	} else if (st->mode == X1 && ((st->time + 0.00001f) > st->attack_time) && ((st->attack_duration - 0.00001f) <= 0.0f || ((st->time - st->attack_time + 0.00001f) < st->attack_duration)) && ((st->time - st->attack_time - 0.00001f) > (st->attack_duration / 2))) {
#ifdef DBG
		_dbg_print_condition("st->mode == X1 && ((st->time + 0.00001f) > st->attack_time) && ((st->attack_duration - 0.00001f) <= 0.0f || ((st->time - st->attack_time + 0.00001f) < st->attack_duration)) && ((st->time - st->attack_time + 0.00001f) < (st->attack_duration / 2))");
#endif
		leave(X1, st);
		st->output = st->input / st->attack_value;
		st->time = st->time + st->step_size;
		enter(X1, st);
	}

	else if (st->mode == X1) {
#ifdef DBG
		_dbg_print_condition("st->mode == X1");
#endif
		leave(X1, st);
		st->output = st->input;
		st->time = st->time + st->step_size;
		enter(X1, st);
	}

#ifdef DBG
	_dbg_print_state(st);
#endif
	return st;
}
