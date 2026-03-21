#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int key;
    int value;
    Node* prev;
    Node* next;

    // Making Constructor
    Node(int k,int v){
        key=k;
        value=v;
        prev=nullptr;
        next=nullptr;
    }
};

class DoublyLinkedList{
    public:
    Node* head;
    Node* tail;

    DoublyLinkedList(){
        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->prev = head;
    }

    void addToFront(Node* node){
        node->prev=head;
        node->next=head->next;
        head->next->prev=node;
        head->next=node;
    }

    void removeNode(Node* node){
        node->prev->next=node->next;
        node->next->prev=node->prev;

        node->prev=nullptr;
        node->next=nullptr;
    }

    Node* removeLast(){
        if(head->next==tail){
            return nullptr;
        }
        Node* lastNode=tail->prev;
        removeNode(lastNode);
        return lastNode;
    }

    void printList(){
        Node* curr = head->next;
        while(curr != tail){
            cout << curr->key << " ";
            curr = curr->next;
        }
    cout << endl;
}
};