// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack;
    std::string pst;

    for (char c: inf) {
        if (std::isdigit(c)) {
            pst.push_back(c);
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.get() != '(') {
                pst.push_back(' ');
                pst.push_back(stack.pop());
            }
            stack.pop();
        } else if (isOperator(c)) {

            while (!stack.isEmpty() && priority(stack.get()) >= priority(c)) {
                pst.push_back(' ');
                pst.push_back(stack.pop());
            }
            stack.push(c);
        }
    }
    while (!stack.isEmpty()) {
        pst.push_back(' ');
        pst.push_back(stack.pop());
    }

    return pst;
}

int eval(std::string pref) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0])) {
            stack.push(std::stoi(token)); // Если это число, помещаем его в стек
        } else if (isOperator(token[0])) {
            int operand2 = stack.pop();
            int operand1 = stack.pop();

            switch (token[0]) {
                case '+':
                    stack.push(operand1 + operand2);
                    break;
                case '-':
                    stack.push(operand1 - operand2);
                    break;
                case '*':
                    stack.push(operand1 * operand2);
                    break;
                case '/':
                    stack.push(operand1 / operand2);
                    break;
            }
        }
    }

    return stack.pop();
}


