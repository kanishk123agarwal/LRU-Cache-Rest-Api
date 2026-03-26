#include "LRUCache.h"

Node::Node(int k,int v){
    key=k;
    value=v;
    prev=nullptr;
    next=nullptr;
}

LRUCache::LRUCache(int capacity){
    this->capacity=capacity;

    head=new Node(-1,-1);
    tail=new Node(-1,-1);

    head->next=tail;
    tail->prev=head;

    hits=0;
    misses=0;
    evictions=0;
}

void LRUCache::addToFront(Node* node){
    node->prev=head;
    node->next=head->next;

    head->next->prev=node;
    head->next=node;
}

void LRUCache::removeNode(Node* node){
    node->prev->next=node->next;
    node->next->prev=node->prev;

    node->prev=nullptr;
    node->next=nullptr;
}

void LRUCache::moveToFront(Node* node){
    removeNode(node);
    addToFront(node);
}

int LRUCache::get(int key){

    unique_lock<shared_mutex> lock(mtx);

    if(cache.find(key)==cache.end()){
        misses++;
        return -1;
    }

    Node* node=cache[key];

    moveToFront(node);

    hits++;

    return node->value;
}

void LRUCache::put(int key,int value){

    unique_lock<shared_mutex> lock(mtx);

    if(cache.find(key)!=cache.end()){

        Node* existingNode=cache[key];

        existingNode->value=value;

        moveToFront(existingNode);

        return;
    }

    if(cache.size()==capacity){

        Node* lru=tail->prev;

        cache.erase(lru->key);

        removeNode(lru);

        evictions++;

        delete lru;
    }

    Node* newNode=new Node(key,value);

    addToFront(newNode);

    cache[key]=newNode;
}

string LRUCache::getStats(){

    shared_lock<shared_mutex> lock(mtx);

    long long total=hits+misses;

    double hitRate=0.0;

    if(total>0){
        hitRate=(double)hits/total*100.0;
    }

    stringstream ss;

    ss<<"{";
    ss<<"\"hits\": "<<hits<<",";
    ss<<"\"misses\": "<<misses<<",";
    ss<<"\"evictions\": "<<evictions<<",";
    ss<<"\"hit_rate\": "<<fixed<<setprecision(1)<<hitRate;
    ss<<"}";

    return ss.str();
}

size_t LRUCache::getSize(){

    shared_lock<shared_mutex> lock(mtx);

    return cache.size();
}

LRUCache::~LRUCache(){

    Node* curr=head;

    while(curr){

        Node* nextNode=curr->next;

        delete curr;

        curr=nextNode;
    }
}