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


bool
Node::isLeaf()
{
    if(mLeftChild == nullptr && mRightChild == nullptr)
        return true;
    return false;
}


Node *
Node::getLeftChild()
{
    return mLeftChild;
}


Node *
Node::getRightChild()
{
    return mRightChild;
}
