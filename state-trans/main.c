#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "state.h"

int main(int argc, char const *argv[])
{

    ppl_s ppl;
    mode_enum pre_mode;
    action_enum action;
    FILE *fptr = NULL;
    ppl_state_enum pre_state;

    fptr = fopen("./state.log", "a");

    snprintf(ppl.name, sizeof(ppl.name), "Ian");
    ppl.age = 22;
    ppl.action = NO_ACTION;
    ppl.emotion = HAPPY;

    srand(1);
    time_t start = time(NULL);
    while(time(NULL) - start < 3) {
        action = ( rand() % (5 - 1) ) + 1;
        ppl.action = action;
        pre_state = getCurrentState();
        pre_mode = ppl.emotion;

        setCurrentState(state_ppl_transition(getCurrentState(), &ppl));
        fprintf(fptr, "state_transition:%d->%d, emotion:%s->%s\n", \
        pre_state, getCurrentState(), (pre_mode == HAPPY)? "happy": "sad",(ppl.emotion == HAPPY)? "happy" : "sad" );
        
        usleep(0.5 * 1000);
    }

    fclose(fptr);
    return 0;
}
