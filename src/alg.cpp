// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include <sstream>
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
    std::string numBuffer; 

    for (char c : inf) {
        if (std::isdigit(c)) {
            numBuffer.push_back(c);
        } else {
            if (!numBuffer.empty()) {
                pst += numBuffer + ' '; 
                numBuffer.clear(); 
            }
            if (c == '(') {
                stack.push(c);
            } else if (c == ')') {
                while (!stack.isEmpty() && stack.get() != '(') {
                    pst.push_back(stack.pop());
                    pst.push_back(' ');
                }
                stack.pop();
            } else if (isOperator(c)) {
                while (!stack.isEmpty() && priority(stack.get()) >= priority(c)) {
                    pst.push_back(stack.pop());
                    pst.push_back(' ');
                }
                stack.push(c);
            }
        }
    }

    if (!numBuffer.empty()) {
        pst += numBuffer + ' '; 
    }

    while (!stack.isEmpty()) {
        pst.push_back(stack.pop());
        pst.push_back(' ');
    }

    return pst;
}

int eval(std::string post) {
    std::istringstream iss(post);
    std::string token;
    TStack<int, 100> stack;

    while (iss >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            stack.push(std::stoi(token)); 
        } else if (isOperator(token[0])) {
            int operand2 = stack.pop();
            int operand1 = stack.pop();
            if (operand2 == 0 && token[0] == '/') {
                throw std::invalid_argument("Division by zero!");
            }
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



