#include "line_following_robot_4S.h"
/**
 * user-defined constants
 */
const LSR_THRESHOLD

/**
 * init function
 */
void init(State* st) { 
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

/**
 * leave/enter functions
 */
void enter(Mode m, State* st) { 
    st->mode = m;
}
void leave(Mode m, State* st) { 
    st->previous_mode = m;
}

/**
 * triggers
 */

/**
* TODO: Implement tick (This tick function has been copied from 2 Sensors LFR) 
*/
State* tick(State* st) {
    if (st->mode == AUTO && ( st->lfFarRightVal <= LSR_THRESHOLD && st->lfLeftVal <= LSR_THRESHOLD )) {
        #ifdef DBG
        _dbg_print_condition("st->mode == AUTO && ( st->lfRightVal <= LSR_THRESHOLD && st->lfLeftVal <= LSR_THRESHOLD )");
        #endif
        leave(AUTO, st);
        st->servoLeftVal = st->forwardSpeed;
        st->servoRightVal = - st->forwardSpeed;
        enter(AUTO, st);
    } else if (st->mode == AUTO && ( st->lfRightVal <= LSR_THRESHOLD && st->lfLeftVal > LSR_THRESHOLD )) {
        #ifdef DBG
        _dbg_print_condition("st->mode == AUTO && ( st->lfRightVal <= LSR_THRESHOLD && st->lfLeftVal > LSR_THRESHOLD )");
        #endif
        leave(AUTO, st);
        st->servoLeftVal = st->forwardRotate;
        st->servoRightVal = - st->backwardRotate;
        enter(AUTO, st);
    } else if (st->mode == AUTO && ( st->lfRightVal > LSR_THRESHOLD && st->lfLeftVal <= LSR_THRESHOLD )) {
        #ifdef DBG
        _dbg_print_condition("st->mode == AUTO && ( st->lfRightVal > LSR_THRESHOLD && st->lfLeftVal <= LSR_THRESHOLD )");
        #endif
        leave(AUTO, st);
        st->servoLeftVal = st->backwardRotate;
        st->servoRightVal = - st->forwardRotate;
        enter(AUTO, st);
    } else if (st->mode == AUTO && ( st->lfRightVal > LSR_THRESHOLD && st->lfLeftVal > LSR_THRESHOLD )) {
        #ifdef DBG
        _dbg_print_condition("st->mode == AUTO && ( st->lfRightVal > LSR_THRESHOLD && st->lfLeftVal > LSR_THRESHOLD )");
        #endif
        leave(AUTO, st);
        st->servoLeftVal = st->servoLeftVal;
        st->servoRightVal = st->servoRightVal;
        enter(AUTO, st);
    }
    #ifdef DBG
    _dbg_print_state(st);
    #endif
    return st;
}




