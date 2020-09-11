State* tick(State* st)
{
	float64_t lfRightVal = 0.0f;
	float64_t lfLeftVal = 0.0f;
	if(st->mode == AUTO) {
		/* compute sensor mean */
		lfRightVal = (st->lfFarRightVal + st->lfMidRightVal) / 2.0f;
		lfLeftVal = (st->lfFarLeftVal + st->lfMidLeftVal) / 2.0f;
		if (lfRightVal <= LSR_THRESHOLD && lfLeftVal <= LSR_THRESHOLD) { /* left black, right black -> forward */

			leave(AUTO, st);
			st->servoLeftVal = st->forwardSpeed;
			st->servoRightVal = -st->forwardSpeed;
			enter(AUTO, st);
		} else if (lfRightVal <= LSR_THRESHOLD && lfLeftVal > LSR_THRESHOLD) { /* left black, right white -> right */

			leave(AUTO, st);
			st->servoLeftVal = st->highRotate;
			st->servoRightVal = -st->lowRotate;
			enter(AUTO, st);
		} else if (lfRightVal > LSR_THRESHOLD && lfLeftVal <= LSR_THRESHOLD) { /* left white, right black -> left */

			leave(AUTO, st);
			st->servoLeftVal = st->lowRotate;
			st->servoRightVal = -st->highRotate;
			enter(AUTO, st);
		} else if (lfRightVal > LSR_THRESHOLD && lfLeftVal > LSR_THRESHOLD) { /* left white, right white -> continue */

			leave(AUTO, st);
			st->servoLeftVal = st->servoLeftVal;
			st->servoRightVal = st->servoRightVal;
			enter(AUTO, st);
		}
	}


	return st;
}
