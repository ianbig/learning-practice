#include <stdio.h>
#include "state.h"

#include <stdio.h>
#include "state.h"

static ppl_state_enum g_current_status = PPL_SINGAL;

ppl_state_enum do_singal_state(ppl_s *ppl);
ppl_state_enum do_dated_state(ppl_s *ppl);
ppl_state_enum do_marriage_state(ppl_s *ppl);

calculate_new_state_func * const state_table[NUM_STATES] = {
    do_singal_state,
    do_dated_state,
    do_marriage_state
};

void do_singal_to_dated(ppl_s *ppl);
void do_dated_to_singal(ppl_s *ppl);
void do_dated_to_marriage(ppl_s *ppl);
void do_marriage_to_singal(ppl_s *ppl);
void do_marriage_to_dated(ppl_s *ppl);


state_transition_table_func * const transition_table[NUM_STATES][NUM_STATES] = {
    {NULL, do_singal_to_dated, NULL},
    {do_dated_to_singal, NULL, do_dated_to_marriage},
    {do_marriage_to_singal, do_marriage_to_dated, NULL}
};

void do_singal_to_dated(ppl_s *ppl) {
    if(ppl->action == FALL_IN_LOVE) {
        ppl->emotion = HAPPY;
    }
}

void do_dated_to_singal(ppl_s *ppl) {
    if(ppl->action == DO_NO_MAKE_IT) {
        ppl->emotion = SAD;
    }
}

void do_dated_to_marriage(ppl_s *ppl) {
    if(ppl->action == FALL_IN_TRAP) {
        ppl->emotion = HAPPY;
    }
}

void do_marriage_to_singal(ppl_s *ppl) {
    if(ppl->action == FIND_THE_TRUTH) {
        ppl->emotion = SAD;
    }
}

void do_marriage_to_dated(ppl_s *ppl) {
    if(ppl->action == REGRET_IN_TIME) {
        ppl->emotion = SAD;
    }
}

ppl_state_enum do_singal_state(ppl_s *ppl) {
    ppl_state_enum ret = PPL_SINGAL;
    
    if(ppl->action == FALL_IN_LOVE) {
        ret = PPL_DATED;
    }
    
    return ret;
}

ppl_state_enum do_dated_state(ppl_s *ppl) {
    ppl_state_enum ret = PPL_DATED;

    if(ppl->action == DO_NO_MAKE_IT) {
        ret = PPL_SINGAL;
    }
    else if(ppl->action == FALL_IN_TRAP) {
        ret = PPL_MARRIAGE;
    }

    return ret;
}

ppl_state_enum do_marriage_state(ppl_s *ppl) {
    ppl_state_enum ret = PPL_MARRIAGE;

    if(ppl->action == REGRET_IN_TIME) {
        ret = PPL_DATED;
    }
    else if(ppl->action == FIND_THE_TRUTH) {
        ret = PPL_SINGAL;
    }

    return ret;
}

ppl_state_enum state_ppl_transition(ppl_state_enum curstate, ppl_s *ppl) {
    ppl_state_enum new_state = state_table[curstate](ppl);
    state_transition_table_func *transition = transition_table[curstate][new_state];

    if(transition) {
        transition(ppl);
    }

    return new_state;
}

ppl_state_enum getCurrentState() {
    return g_current_status;
}

void setCurrentState(ppl_state_enum state) {
    g_current_status = state;
}