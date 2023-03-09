#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "arch/x86/include/generated/uapi/asm/unistd_64.h"
#include <sys/types.h>

void empty_the_stack();
void put_message();
void assert_empty();

void test_put_and_get_with_output();
void test_put_gives_right_returnval_on_negative_length();
void test_stack_structure_works_as_expected(); // test stack functions as LIFO
void test_concurency();

void empty_the_stack() {
    int done = 0;
    char buffer[1000];
    while(done == 0) {
        int d = syscall(__NR_dm510_msgbox_get, buffer);
        if((d ==-1)) done = 1;
    } 
    assert_empty();
}

void put_message(const char *message) {
    char msg[strlen(message) + 1];

    int putResponse = syscall(__NR_dm510_msgbox_put, message, strlen(message) + 1);

    assert(putResponse == 0);
}

void assert_empty() {
    char msg[10];

    int getReturnVal = syscall(__NR_dm510_msgbox_get, msg);

    assert(getReturnVal == -1);
}

void test_put_and_get_with_output() {
    assert_empty();

    char *in = "This is a stupid message.";
    int msglen = strlen(in) + 1;
    char getMsg[msglen];
    int putResponse;
    int getResponse;

    printf("\nputting the message: %s\nthe message is %d long.\n", in, msglen);
    putResponse = syscall(__NR_dm510_msgbox_put, in, msglen);
    printf("the put response is %d\n", putResponse);

    printf("calling to get the message\n");
    getResponse = syscall(__NR_dm510_msgbox_get, getMsg);
    printf("got the message: %s\nthe message is %d long\n\n", getMsg, getResponse);

    assert_empty();
}

void test_put_gives_right_returnval_on_negative_length() {
    printf("test_put_gives_right_returnval on negative length...\n");

    assert_empty();

    char *in = "This is a stupid message.";
    int putReturnVal = syscall(__NR_dm510_msgbox_put, in, -1);
    
    assert (putReturnVal == -EINVAL);

    assert_empty();
}

void test_stack_structure_works_as_expected() {
    printf("test stack structure works as expected... \n");

    assert_empty();

    int msglen;
    char buffer[50];
    char *first = "first message";
    char *second = "second message";
    
    put_message(first);
    put_message(second);

    /* test top of stack, i.e the second message */
    msglen = syscall(__NR_dm510_msgbox_get, buffer);
    assert(msglen == strlen(second) + 1);
    assert(strcmp(second, buffer) == 0);

    /* test top of stack, i.e the first message*/
    msglen = syscall(__NR_dm510_msgbox_get, buffer);
    assert(msglen == strlen(first) + 1);
    assert(strcmp(first, buffer) == 0);

    assert_empty();
}

void help_concurrency() {
    for(int i = 0; i < 10; i++) {
        fork();
        int getReturnVal;
        char *message = "hello";
        char buffer[50];

        put_message(message);

        // wait for message to be ready
        while((getReturnVal = syscall(__NR_dm510_msgbox_get, buffer)) == -1) {}
        assert(getReturnVal == strlen("hello") + 1);
    }

    // wait for all child processes to finish, as each parent to the children waits recursively
    while(wait(NULL) > 0);
    // exit the process
    exit(0);
}

void test_concurency() {
    printf("test concurrency... \n");
    assert_empty();

    pid_t pid, parentId;
    pid = fork();
    if(pid == 0) help_concurrency();
    // wait for child process, which wait for its child processes. i.e wait for all processes to be done, but the parent
    else while(wait(NULL) > 0);
    
    assert_empty();
}

int main(void) {
    empty_the_stack();
    test_put_and_get_with_output();
    test_put_gives_right_returnval_on_negative_length();
    test_stack_structure_works_as_expected();
    test_concurency();
    assert_empty();
}
