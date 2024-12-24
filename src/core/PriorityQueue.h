//
// Created by Lukas Berntsen on 24/12/2024.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <QList>

class Node;

class PriorityQueue {
public:
    PriorityQueue();
    ~PriorityQueue();

    void append(Node *aNode);
    Node *pop();
    int length() const;

private:
    QList<Node *> mQueue;
};

#endif //PRIORITYQUEUE_H