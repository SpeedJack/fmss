#include "line_following_robot.h"
/**
 * init function
 */
void init(State* st) { 
    st->previous_mode = AUTO;
    st->mode = AUTO;
    st->backwardRotate = 1.0f;
    st->forwardRotate = 5.0f;
    st->forwardSpeed = 4.0f;
    st->lfLeftVal = 0.0f;
    st->lfRightVal = 0.0f;
    st->LSR_THRESHOLD = 400.0f;
    st->servoLeftVal = 0.0f;
    st->servoRightVal = 0.0f;
    st->step_size = 0.01f;
    st->time = 0.0f;
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
bool per_tick(State* st) {
    return (st->mode == AUTO && ( st->lfRightVal <= st->LSR_THRESHOLD && st->lfLeftVal <= st->LSR_THRESHOLD ))
            || (st->mode == AUTO && ( st->lfRightVal <= st->LSR_THRESHOLD && st->lfLeftVal > st->LSR_THRESHOLD ))
            || (st->mode == AUTO && ( st->lfRightVal > st->LSR_THRESHOLD && st->lfLeftVal <= st->LSR_THRESHOLD ))
            || (st->mode == AUTO && ( st->lfRightVal > st->LSR_THRESHOLD && st->lfLeftVal > st->LSR_THRESHOLD ));
}


void sensor_attack(State* st) {
 if (st->time >= 2.0f) st->lfRightVal = 100.0f;
}

void actuator_attack(State* st) {
 if (fabs(st->time - 1.0f) < 0.00001f){ // st->time == 1.0f
  st->servoLeftVal = 0.1f;
  st->servoRightVal = 0.1f;
 } 
}

State* tick(State* st) {
    sensor_attack(st);
    // assert( per_tick(st) );
    if (st->mode == AUTO && ( st->lfRightVal <= st->LSR_THRESHOLD && st->lfLeftVal <= st->LSR_THRESHOLD )) {
        #ifdef DBG
        _dbg_print_condition("st->mode == AUTO && ( st->lfRightVal <= st->LSR_THRESHOLD && st->lfLeftVal <= st->LSR_THRESHOLD )");
        #endif
        leave(AUTO, st);
        st->servoLeftVal = st->forwardSpeed;
        st->servoRightVal = - st->forwardSpeed;
        st->time = st->time + st->step_size;
        enter(AUTO, st);
    } else if (st->mode == AUTO && ( st->lfRightVal <= st->LSR_THRESHOLD && st->lfLeftVal > st->LSR_THRESHOLD )) {
        #ifdef DBG
        _dbg_print_condition("st->mode == AUTO && ( st->lfRightVal <= st->LSR_THRESHOLD && st->lfLeftVal > st->LSR_THRESHOLD )");
        #endif
        leave(AUTO, st);
        st->servoLeftVal = st->forwardRotate;
        st->servoRightVal = - st->backwardRotate;
        st->time = st->time + st->step_size;
        enter(AUTO, st);
    } else if (st->mode == AUTO && ( st->lfRightVal > st->LSR_THRESHOLD && st->lfLeftVal <= st->LSR_THRESHOLD )) {
        #ifdef DBG
        _dbg_print_condition("st->mode == AUTO && ( st->lfRightVal > st->LSR_THRESHOLD && st->lfLeftVal <= st->LSR_THRESHOLD )");
        #endif
        leave(AUTO, st);
        st->servoLeftVal = st->backwardRotate;
        st->servoRightVal = - st->forwardRotate;
        st->time = st->time + st->step_size;
        enter(AUTO, st);
    } else if (st->mode == AUTO && ( st->lfRightVal > st->LSR_THRESHOLD && st->lfLeftVal > st->LSR_THRESHOLD )) {
        #ifdef DBG
        _dbg_print_condition("st->mode == AUTO && ( st->lfRightVal > st->LSR_THRESHOLD && st->lfLeftVal > st->LSR_THRESHOLD )");
        #endif
        leave(AUTO, st);
        st->servoLeftVal = st->servoLeftVal;
        st->servoRightVal = st->servoRightVal;
        st->time = st->time + st->step_size;
        enter(AUTO, st);
    }

//    actuator_attack(st);
    #ifdef DBG
    _dbg_print_state(st);
    #endif
    return st;
}




