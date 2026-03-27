#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int key;
    int value;
    Node* prev;
    Node* next;

    Node(int k,int v);
};

class LRUCache{
private:
    int capacity;
    shared_mutex mtx;

    unordered_map<int,Node*> cache;

    Node* head;
    Node* tail;

    atomic<long long> hits{0};
    atomic<long long> misses{0};
    atomic<long long> evictions{0};

    void addToFront(Node* node);
    void removeNode(Node* node);
    void moveToFront(Node* node);

public:
    LRUCache(int capacity);

    int get(int key);

    void put(int key,int value);

    string getStats();

    size_t getSize();

    vector<pair<int,int>> getCacheState();

    ~LRUCache();
};

#endif