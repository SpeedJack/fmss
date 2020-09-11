State* tick(State* st)
{
	/* restart attack cycle if needed */
	if (st->mode == X1 && st->cyclic && st->attack_duration > 0.0f
			&& ((st->time + 0.00001f) > (st->attack_time + st->attack_duration)))
		st->time = 0;

	if (st->mode == X1 /* first part of the attack */
			&& ((st->time + 0.00001f) > st->attack_time)
			&& ((st->attack_duration - 0.00001f) <= 0.0f
				|| ((st->time - st->attack_time + 0.00001f) < st->attack_duration))
			&& ((st->time - st->attack_time + 0.00001f) < (st->attack_duration / 2))) {

		leave(X1, st);
		st->output = st->input * st->attack_value;
		st->time = st->time + st->step_size;
		enter(X1, st);
	} else if (st->mode == X1 /* second part of the attack */
			&& ((st->time + 0.00001f) > st->attack_time)
			&& ((st->attack_duration - 0.00001f) <= 0.0f
				|| ((st->time - st->attack_time + 0.00001f) < st->attack_duration))
			&& ((st->time - st->attack_time - 0.00001f) > (st->attack_duration / 2))) {

		leave(X1, st);
		st->output = st->input / st->attack_value;
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
