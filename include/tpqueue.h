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
  explicit Node(T data) : data(data), next(nullptr) {}
  Node* start;
  Node* end;
};
 public:
    TPQueue() : start(nullptr), end(nullptr) {}
    ~TPQueue() {
        while (start) {
            Node* temp = start;
            start = start->next;
            delete temp;
        }
    }

    void push(T item) {
        Node* newNode = new Node(item);
        if (!start || item.prior > start->data.prior) {
            newNode->next = start;
            start = newNode;
            if (!end) end = start;
            return;
        }
        Node* current = start;
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
        Node* temp = start;
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
