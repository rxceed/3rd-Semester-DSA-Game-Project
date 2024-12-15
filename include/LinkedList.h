#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template<class T> class Node
{
    public:
    T data;
    Node *next;
    bool IsTail;
    Node(T data_)
    {
        data = data_;
        next = NULL;
        IsTail = false;
    }
    ~Node()
    {

    }
};

template<class T> class LinkedList
{
    private:
    Node<T> *head;
    bool IsEmpty;
    public:
    LinkedList()
    {
        head = NULL;
        IsEmpty = true;
    }
    LinkedList(Node<T> *node)
    {
        head = node;
        IsEmpty = false;
        head->IsTail = true;
    }
    ~LinkedList()
    {
    }
    void AppendToHead(Node<T>  *node)
    {
        Node<T> *PrevHead = head;
        std::cout<<head<<std::endl;
        
        if(IsEmpty)
        {
            node->IsTail = true;  
            IsEmpty = false; 
            head = node;
            if(head->IsTail)
            {
                std::cout<<"tail"<<std::endl;
            }
        }
        else if(!IsEmpty)
        {
            if(head->IsTail)
            {
                std::cout<<"tail"<<std::endl;
            }
            node->next = head;
            head = node;
        }
        
        std::cout<<"Append Success"<<std::endl;
    }
    void AppendToTail(Node<T>  *node)
    {
        Node<T> *CurrentNode = head;
        for(int i = 1; i < GetSize(); i++)
        {
            if(CurrentNode->IsTail)
            {
                CurrentNode->IsTail = false;
            }
            CurrentNode = CurrentNode->next;
        }
        CurrentNode->next = node;
        CurrentNode->IsTail = true;
    }
    void Insert(Node<T>  *node, int index)
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
    void DeleteHead()
    {
        Node<T> *CurrentHead = head->next;
        //delete head;
        if(head->IsTail)
        {
            IsEmpty = true;
        }
        else
        {
            head = CurrentHead;
        }
    }
    void DeleteTail()
    {
        Node<T> *CurrentNode = head;
        for(int i = 1; i < GetSize()-1; i++)
        {
            CurrentNode = CurrentNode->next;
        }
        CurrentNode->IsTail = true;
        CurrentNode->next = NULL;
    }
    void Delete(int index)
    {
        Node<T> *CurrentNode = head;
        Node<T> *TempNode;
        if(index == GetSize())
        {
            DeleteTail();
        }
        else if(index == 1)
        {
            DeleteHead();
        }
        else
        {
            for(int i = 0; i < index; i++)
            {
                if(i == index-2)
                {
                    TempNode = CurrentNode;
                }
                CurrentNode = CurrentNode->next;
                TempNode->next = CurrentNode;
            }
        }
        //delete TempNode->next;
    }
    Node<T> *GetNode(int index)
    {
        Node<T> *CurrentNode = head;
        for(int i = 1; i < index; i++)
        {
            CurrentNode = CurrentNode->next;
        }
        return CurrentNode;
    }
    int GetSize()
    {
        int size = 0;
        Node<T> *CurrentNode = head;
        if(IsEmpty)
        {
            return 0;
        }
        while(true)
        {
            size++;
            if(CurrentNode->IsTail)
            {
                break;
            }
            else
            {
                CurrentNode = CurrentNode->next;
            }   
        }
        /*
        while(!CurrentNode->IsTail)
        {
            size++;
            CurrentNode = CurrentNode->next;
            if(CurrentNode == NULL)
            {
                break;
            }
        }*/
        return size;
    }
};
/*
void LinkedList<class T>::DeleteHead()
{

}
void LinkedList<class T>::DeleteTail()
{
    
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
template <> int LinkedList<class T>::GetSize()
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
}
*/
#endif