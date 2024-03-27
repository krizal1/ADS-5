// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
    T *arr;
    int top;

public:
    TStack() {
        arr = new T[size];
        top = -1;
    }

    ~TStack() {
        delete[] arr;
    }

    void push(T value) {
        if (top < size - 1) {
            arr[++top] = value;
        }
    }

    T pop() {
        if (top >= 0) {
            return arr[top--];
        }
        return T();
    }

    T get() const {
        return arr[top];
    }

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == size - 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
