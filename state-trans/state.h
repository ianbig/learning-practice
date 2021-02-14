#ifndef STATE_H
#define STATE_H

#define MAXNAME 128
#define NUM_STATES 3

typedef enum {
    PPL_SINGAL,
    PPL_DATED,
    PPL_MARRIAGE
} ppl_state_enum;

typedef enum {
    HAPPY,
    SAD
} mode_enum;

typedef enum {
    NO_ACTION,
    FALL_IN_LOVE,
    DO_NO_MAKE_IT,
    FALL_IN_TRAP,
    REGRET_IN_TIME,
    FIND_THE_TRUTH
} action_enum;

typedef struct {
    char name[MAXNAME];
    int age;
    mode_enum emotion;
    action_enum action;
} ppl_s;

typedef ppl_state_enum calculate_new_state_func(ppl_s *date);
typedef void state_transition_table_func(ppl_s *date);

ppl_state_enum getCurrentState(void);
ppl_state_enum state_ppl_transition(ppl_state_enum curstate, ppl_s *ppl);
void setCurrentState(ppl_state_enum state);

#endif

// question: why need const in function pointer