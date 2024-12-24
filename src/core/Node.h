//
// Created by Lukas Berntsen on 24/12/2024.
//

#ifndef NODE_H
#define NODE_H

class Node {
public:
    Node(int aValue, Node *aLeftChild = nullptr, Node *aRightChild = nullptr);
    ~Node();
    int getValue() const;
    bool isLeaf();
    Node *getLeftChild();
    Node *getRightChild();

private:
    int mValue;
    Node *mLeftChild;
    Node *mRightChild;
};

#endif //NODE_H
