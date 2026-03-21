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

class LRUCache{
    private:
    int capacity;

    unordered_map<int,Node*> cache;
    Node* head;
    Node* tail;

    public:
    LRUCache(int capacity){
        this->capacity=capacity;

        head=new Node(-1,-1);
        tail=new Node(-1,-1);
        head->next=tail;
        tail->prev=head;
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

    void moveToFront(Node* node){
        removeNode(node);
        addToFront(node);
    }

    int get(int key){
        // Key is not found
        if(cache.find(key)==cache.end()){
            return -1;
        }

        // Key exist;
        Node* node=cache[key];

        moveToFront(node);
        return node->value;
    }

    void put(int key,int value){
        // Case 1: key already exists
        if(cache.find(key)!=cache.end()){
            Node* existingNode=cache[key];

            // Update value
            existingNode->value=value;

            // Make recent because its just call
            moveToFront(existingNode);
            return;
        }

        // Case 2: Cache full
        if(cache.size()==capacity){
            // Least recently used Node 
            Node* lru=tail->prev;

            // remove from hashmap
            cache.erase(lru->key);

            // remove from DLL
            removeNode(lru);

            delete lru;
        }

        // Case 3: Create New Node
        Node* newNode=new Node(key,value);
        
        // insert in DLL
        addToFront(newNode);

        // insert in hashmap
        cache[key]=newNode;
    }
};