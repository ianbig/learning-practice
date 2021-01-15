/** 
 * What I am testing 
    * a sample that obj content cannot be modified
    * a sample that pointer could only point to obj
*/
/** 
 * Prove
    * read-only pointer-to-non-const can change value of variable instead of address
    * read-only value-to-non-const can change value instead of address
    * read-only value-to-const can change address instead of value
    * read-only pointer-to-const can change value instead of address
*/


#include<string.h>
#include<stdlib.h>
#include <stdio.h>


typedef char INT;
typedef int (*ADD_FUNCTION_POINTER)(int a, int b);

static int callbackFunc_callee_add(int a, int b);
static int callbackFunc_callee_multi(int a, int b);
static int callbackFunc_callee_minus(int a, int b);

typedef struct {
    ADD_FUNCTION_POINTER mod_1;
    ADD_FUNCTION_POINTER mod_2;
    ADD_FUNCTION_POINTER mod_3;
}ADD_CALLBACK_S;


ADD_CALLBACK_S obj= {
    callbackFunc_callee_add,
    callbackFunc_callee_multi,
    callbackFunc_callee_minus
};

const ADD_CALLBACK_S obj_const = {
    callbackFunc_callee_add,
    callbackFunc_callee_multi,
    callbackFunc_callee_minus
};


ADD_CALLBACK_S const obj_middle_const = {
    callbackFunc_callee_add,
    callbackFunc_callee_multi,
    callbackFunc_callee_minus
};

static int callbackFunc_callee_add(int a, int b) {
    return a + b;
}

static int callbackFunc_callee_multi(int a, int b) {
    return a * b;
}

static int callbackFunc_callee_minus(int a, int b) {
    return a - b;
}

int erroFunct(int a, int b) {
    printf("haha I change\n");
    return 0;
}

void callbackFunc_caller_value_read_only(const ADD_CALLBACK_S *funcObj, int a, int b) {
    int mod = 3;
    scanf("%d", &mod);
    int result = -1;
    ADD_CALLBACK_S changObj = {
        callbackFunc_callee_minus,
        callbackFunc_callee_add,
        erroFunct
    };

    // it is value read only; thus, it could not change value
    // funcObj->mod_1 = erroFunct;
    // it is value read only; thus, it could change pointer
    funcObj = &changObj;

    if( mod == 0) {
        result =  funcObj->mod_1(a, b);
    } else if (mod == 1 ) {
        result = funcObj->mod_2(a, b);
    } else if( mod == 2) {
        result = funcObj->mod_3(a, b);
    } else {
        printf("ERROR: mod is too big\n");
        return;
    }

    printf("%d\n", result);
}

void callbackFunc_caller_pointer_read_only(ADD_CALLBACK_S *const funcObj, int a, int b) {
    int mod = 3;
    scanf("%d", &mod);
    int result = -1;
    ADD_CALLBACK_S changObj = {
        callbackFunc_callee_minus,
        callbackFunc_callee_add,
        erroFunct
    };

    // it is pointer read only; thus, it can change value
    funcObj->mod_1 = erroFunct;
    funcObj->mod_2 = callbackFunc_callee_add;
    // it is pointer read only; thus, it could not chage pointer
    //funcObj = &changObj;

    if( mod == 0) {
        result =  funcObj->mod_1(a, b);
    } else if (mod == 1 ) {
        result = funcObj->mod_2(a, b);
    } else if( mod == 2) {
        result = funcObj->mod_3(a, b);
    } else {
        printf("ERROR: mod is too big\n");
        return;
    }

    printf("%d\n", result);
}


int main () {

    printf("testing obj to const ADD_CALLBACK_S *funcObj\n");
    callbackFunc_caller_value_read_only(&obj_middle_const, 100,20);
    printf("testing obj to ADD_CALLBACK_S *const funcObj\n");
    callbackFunc_caller_pointer_read_only(&obj, 100,20);
    printf("testing const obj to const ADD_CALLBACK_S *funcObj\n");
    callbackFunc_caller_value_read_only(&obj_const, 100, 20);
    
    /** Below is an type conversion code (const ADD_CALLBACK_S to ADD_CALLBACK_S) since the agrument is an read-only pointer with type ADD_BLACK_S **/
    // printf("testing const obj to ADD_CALLBACK_S *const funcObj\n");
    // callbackFunc_caller_pointer_read_only(&obj_const, 100, 20); // this is an warning, but its code logic is flaw since passing an const variable into a const pointer type with ADD_CALLBACK_S would potentially change its value
    return 0;
}
