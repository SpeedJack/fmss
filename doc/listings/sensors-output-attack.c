State* tick(State* st)
{
	assert(per_tick(st));

	/* reset attack cycle if needed */
	if (st->mode == X1 && st->cyclic && st->attack_duration > 0.0f
			&& ((st->time + 0.00001f) > (st->attack_time + st->attack_duration)))
		st->time = 0;

	if (st->mode == X1 /* attack */
			&& ((st->time + 0.00001f) > st->attack_time)
			&& ((st->attack_duration - 0.00001f) <= 0.0f
				|| ((st->time - st->attack_time + 0.00001f) < st->attack_duration))) {
		leave(X1, st);
		st->output = st->input + st->input * st->attack_value;
		if (st->output > 255.0f)
			st->output = 255.0f;
		if (st->output < 0.0f)
			st->output = 0.0f;
		st->time = st->time + st->step_size;
		enter(X1, st);
	} else if (st->mode == X1) { /* do nothing: forward input */
		leave(X1, st);
		st->output = st->input;
		st->time = st->time + st->step_size;
		enter(X1, st);
	}

	return st;
}
