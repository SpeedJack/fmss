void sensor_attack(State* st)
{
	/* reset attack cycle if needed */
	if (st->mode == AUTO && st->cyclic && st->attack_duration > 0.0f
			&& ((st->time + 0.00001f) > (st->attack_time + st->attack_duration)))
		st->time = 0;
	/* attack */
	if (st->mode == AUTO
			&& ((st->time + 0.00001f) > st->attack_time)
			&& ((st->attack_duration - 0.00001f) <= 0.0f
				|| ((st->time - st->attack_time + 0.00001f) < st->attack_duration))) {
		float64_t farRightTmp = st->lfFarRightVal;
		float64_t midRightTmp = st->lfMidRightVal;
		st->lfFarRightVal = st->lfFarLeftVal;
		st->lfMidRightVal = st->lfMidLeftVal;
		st->lfFarLeftVal = farRightTmp;
		st->lfMidLeftVal = midRightTmp;
	}
	st->time += st->step_size;
}

State* tick(State* st)
{
	if(st->mode == AUTO) {
		sensor_attack(st);
		/* ... */
	}
	return st;
}
