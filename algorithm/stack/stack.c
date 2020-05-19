#include "common.h"


char stack[64];

int top = 0;

void push(char c) {
    stack[top++] = c;
}

char pop() {
    return stack[--top];
}

char getTop() {
    return stack[top - 1];
}

bool isStackEmpty() {
    return top == 0;
}

bool isValid(char* s) {
    char ch = 0;
    if (s && !*s)
        return true;
    while (s && *s) {
        if (*s == '(' || *s == '[' || *s == '{')
            push(*s);
        else if (*s == ')') {
            ch = pop();
            if (ch != '(')
                return false;
        }
        else if (*s == ']') {
            ch = pop();
            if (ch != '[')
                return false;
        }
        else if (*s == '}') {
            ch = pop();
            if (ch != '{')
                return false;
        }

        s++;
    }

    return isStackEmpty();
}

void stackTest()
{
    isValid("{[]}");
}