#pragma once

class Queue {
public:
    Queue():
    head{nullptr}, tail{nullptr}{}

    void pushBack(int v) {

    }

    struct ListNode{
        int val;
        ListNode* next;
        ListNode(int v):val{v}, next{nullptr}{}
    };
private:
    ListNode* head;
    ListNode* tail;
};