// Copyright 2021 NNTU-CS
#include <map>
#include "tstack.h"

int Priority(char operand) {
    if (operand == '+' || operand == '-') return 1;
    if (operand == '*' || operand == '/') return 2;
    return 0;
}
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

std::string infx2pstfx(std::string inf) {
    std::string postfix;
    TStack<char, 100> stack;
    for (char c : inf) {
        if (isdigit(c)) {
            postfix = postfix + c + ' ';
        }else if (c == '(') {
            stack.push(c);
        }else if (isOperator(c)) {
            while (!stack.isEmpty() && Priority(stack.get()) >= Priority(c)) {
                postfix = postfix + stack.get() + ' ';
                stack.pop();
            }
            stack.push(c);
        }else if (c == ')') {
            while (!stack.isEmpty() && stack.get() != '(') {
                postfix = postfix + stack.get() + ' ';
                stack.pop();
            }
            stack.pop();
        }
    }
    while (!stack.isEmpty()) {
        postfix = postfix + stack.get() + ' ';
        stack.pop();
    }
    if (!postfix.empty()) {
        postfix.pop_back();
    }
    return postfix;
}
int eval(std::string post) {
    TStack<int, 100> stack;
    std::string Number;
    for (char c : post) {
        if (isdigit(c)) {
            Number += c;
        }else if (Number != "") {
            stack.push(std::atoi(Number.c_str()));
            Number = "";
        }
        if (isOperator(c)) {
            int op2 = stack.get();
            stack.pop();
            int op1 = stack.get();
            stack.pop();
            switch (c) {
            case '+':
                stack.push(op1 + op2);
                break;
            case '-':
                stack.push(op1 - op2);
                break;
            case '*':
                stack.push(op1 * op2);
                break;
            case '/':
                stack.push(op1 / op2);
                break;
            }
        }
    }
    if (Number != "") {
        stack.push(std::atoi(Number.c_str()));
    }
    return stack.get();
}



