void actuator_attack(State* st)
{
	/* reset attack cycle if needed */
	if (st->mode == AUTO && st->attack_duration > 0.0f
			&& ((st->time + 0.00001f) > (st->attack_time + st->attack_duration)))
		st->time = 0;

	/* attack */
	if (st->mode == AUTO
			&& ((st->time + 0.00001f) > st->attack_time)
			&& ((st->attack_duration - 0.00001f) <= 0.0f
				|| ((st->time - st->attack_time + 0.00001f) < st->attack_duration))
			&& ((st->time - st->attack_time + 0.00001f) < (st->attack_duration))) {
		st->servoLeftVal = - st->forwardSpeed;
		st->servoRightVal = st->forwardSpeed;
	}

	/* update time */
	st->time = st->time + st->step_size;
}
