void sensor_attack(State* st)
{
	/* attack */
	st->lfFarRightVal = 255.0f - st->lfFarRightVal;
	st->lfMidRightVal = 255.0f - st->lfMidRightVal;
	st->lfFarLeftVal = 255.0f - st->lfFarLeftVal;
	st->lfMidLeftVal = 255.0f - st->lfMidLeftVal;
}

State* tick(State* st)
{
	if(st->mode == AUTO) {
		sensor_attack(st);
		...........
	}

	return st;
}
