//
// Created by Lukas Berntsen on 24/12/2024.
//

#include "PriorityQueue.h"

#include "Node.h"

PriorityQueue::PriorityQueue()
{

}


PriorityQueue::~PriorityQueue()
{

}


void
PriorityQueue::append(Node *aNode)
{
    if(length() == 0)
    {
        mQueue.append(aNode);
        return;
    }

    if(length() == 1)
    {
        if(mQueue.first()->getValue() < aNode->getValue())
            mQueue.append(aNode);
        else
            mQueue.insert(0, aNode);
        return;
    }

    for (int i = 0; i < length(); i++)
    {
        if (mQueue.at(i)->getValue() > aNode->getValue())
        {
            mQueue.insert(i, aNode);
            return;
        }
    }

    mQueue.append(aNode);
}


Node *
PriorityQueue::pop()
{
    Node *node = mQueue[0];
    mQueue.removeFirst();
    return node;
}


int
PriorityQueue::length() const
{
    return mQueue.length();
}
