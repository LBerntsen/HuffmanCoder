//
// Created by Lukas Berntsen on 24/12/2024.
//

#include "Node.h"

Node::Node(int aValue, Node *aLeftChild, Node *aRightChild)
{
    mValue = aValue;
    mLeftChild = aLeftChild;
    mRightChild = aRightChild;
}


Node::~Node()
{

}


int
Node::getValue() const
{
    return mValue;
}