// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#pragma once
#include <stdexcept>

template<typename T>
class TPQueue {
 private:
 struct Node {
 T data;
 Node* next;
 Node(const T& data) : data(data), next(nullptr) {}
};
  Node<T>* start;
  Node<T>* end;
};
public:
    TPQueue() : start(nullptr), end(nullptr) {}
    ~TPQueue() {
        while (start) {
            Node<T>* temp = start;
            start = start->next;
            delete temp;
        }
    }

    void push(const T& item) {
        Node<T>* newNode = new Node<T>(item);
        if (!start || item.prior > start->data.prior) {
            newNode->next = start;
            start = newNode;
            if (!end) end = start;
            return;
        }
        Node<T>* current = start;
        while (current->next && current->next->data.prior >= item.prior) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        if (!newNode->next) {
            end = newNode;
        }
    }
    T pop() {
        if (!start) {
            throw std::runtime_error("Очередь пуста!");
        }
        Node<T>* temp = start;
        T result = temp->data;
        start = start->next;
        if (!start) {
            end = nullptr;
        }
        delete temp;
        return result;
    }
    bool isEmpty() const {
        return start == nullptr;
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
