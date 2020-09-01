#include "Attack_fmu.h"
/**
 * init function
 */
void init(State* st) { 
    st->previous_mode = X1;
    st->mode = X1;
    st->attack_time = 0.0f;
    st->attack_value = 0.0f;
    st->input = 0.0f;
    st->output = 0.0f;
    st->step_size = 0.0f;
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
    return (st->mode == X1 && ( st->time < st->attack_time ))
            || (st->mode == X1 && ( st->time >= st->attack_time ));
}
State* tick(State* st) {
    // assert( per_tick(st) );
    if (st->mode == X1 && ( st->time < st->attack_time )) {
        #ifdef DBG
        _dbg_print_condition("st->mode == X1 && ( st->time < st->attack_time )");
        #endif
        leave(X1, st);
        st->output = st->input;
        st->time = st->time + st->step_size;
        enter(X1, st);
    } else if (st->mode == X1 && ( st->time >= st->attack_time )) {
        #ifdef DBG
        _dbg_print_condition("st->mode == X1 && ( st->time >= st->attack_time )");
        #endif
        leave(X1, st);
        st->output = st->attack_value;
        st->time = st->time + st->step_size;
        enter(X1, st);
    }
    #ifdef DBG
    _dbg_print_state(st);
    #endif
    return st;
}




