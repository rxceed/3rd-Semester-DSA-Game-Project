#include "LinkedList.h"
/*
Node<class T>::Node(T *data_)
{
    data = data_;
    next = nullptr;
}
Node<class T>::~Node()
{

}

LinkedList<class T>::LinkedList()
{
    head = nullptr;
}
LinkedList<class T>::LinkedList(Node<T> *node)
{
    head = node;
}
LinkedList<class T>::~LinkedList()
{
    delete head;
}
void LinkedList<class T>::AppendToHead(Node<T>  *node)
{
    head = node;
}
void LinkedList<class T>::AppendToTail(Node<T>  *node)
{
    Node<T> *CurrentNode = head;
    for(int i = 1; i < GetSize(); i++)
    {
        CurrentNode = CurrentNode->next;
    }
    CurrentNode->next = node;
}
void LinkedList<class T>::Insert(Node<T>  *node, int index)
{
    Node<T> *CurrentNode = head;
    Node<T> *TempNode;
    for(int i = 0; i < index; i++)
    {
        if(i == index-1)
        {
            TempNode = CurrentNode;
        }
        CurrentNode = CurrentNode->next;
    }
    node->next = CurrentNode;
    CurrentNode = node;
    TempNode->next = CurrentNode;
}
void LinkedList<class T>::DeleteHead()
{
    Node<T> *CurrentHead = head->next;
    delete head;
    head = CurrentHead;
}
void LinkedList<class T>::DeleteTail()
{
    Node<T> *CurrentNode = head;
    for(int i = 1; i < GetSize()-1; i++)
    {
        CurrentNode = CurrentNode->next;
    }
    delete CurrentNode->next;
}
void LinkedList<class T>::Delete(int index)
{
    Node<T> *CurrentNode = head;
    Node<T> *TempNode;
    for(int i = 0; i < index; i++)
    {
        if(i == index-2)
        {
            TempNode = CurrentNode;
        }
        CurrentNode = CurrentNode->next;
    }
    delete TempNode->next;
    TempNode->next = CurrentNode;
}
int LinkedList<class T>::GetSize()
{
    int size =1;
    Node<T> *CurrentNode = head;
    while(CurrentNode->next != nullptr)
    {
        size++;
        CurrentNode = CurrentNode->next;
    }
    return size;
}
Node<class T> *LinkedList<class T>::GetNode(int index)
{
    Node<T> *CurrentNode = head;
    for(int i = 0; i < index; i++)
    {
        CurrentNode = CurrentNode->next;
    }
    return CurrentNode;
}*/