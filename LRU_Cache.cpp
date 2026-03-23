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
    shared_mutex mtx;

    unordered_map<int,Node*> cache;
    Node* head;
    Node* tail;

    // Metrices
    long long hits;
    long long misses;
    long long evictions;

    public:
    LRUCache(int capacity){
        this->capacity=capacity;

        head=new Node(-1,-1);
        tail=new Node(-1,-1);
        head->next=tail;
        tail->prev=head;

        hits=0;
        misses=0;
        evictions=0;
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

        unique_lock<shared_mutex> lock(mtx);

        // Key is not found
        if(cache.find(key)==cache.end()){
            misses++;
            return -1;
        }

        // Key exist;
        Node* node=cache[key];

        moveToFront(node);
        hits++;
        return node->value;
    }

    void put(int key,int value){

        unique_lock<shared_mutex> lock(mtx);

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
            evictions++;
            delete lru;
        }

        // Case 3: Create New Node
        Node* newNode=new Node(key,value);
        
        // insert in DLL
        addToFront(newNode);

        // insert in hashmap
        cache[key]=newNode;
    }

    string getStats(){
        shared_lock<shared_mutex> lock(mtx);
        long long total = hits + misses;
        double hitRate = 0.0;
        if(total > 0){
            hitRate = (double)hits / total * 100.0;
        }

        stringstream ss;
        ss << "{";
        ss << "\"hits\": " << hits << ",";
        ss << "\"misses\": " << misses << ",";
        ss << "\"evictions\": " << evictions << ",";
        ss << "\"hit_rate\": " << fixed << setprecision(1) << hitRate;
        ss << "}";

        return ss.str();
    }

    // Add Destruction 
    ~LRUCache(){
        Node* curr=head;
        while(curr){
            Node* nextNode=curr->next;
            delete curr;
            curr=nextNode;
        }
    }
};

int main(int argc,char* argv[]){
    LRUCache* cache=nullptr;
    string command; 
    
    while(cin >> command){ 
        // create cache
        if(command=="create"){
            int capacity;
            cin>>capacity;

            // delete old cache if exist 
            if(cache!=nullptr){
                delete cache;
            }

            cache=new LRUCache(capacity);
            cout<<"Cache Created Successfully"<<endl;
        }

        else if(command == "put"){ 
            if(cache==nullptr){
                cout<<"Cache Not Initialized"<<endl;
                continue;
            }
            int key,value; 
            cin >> key >> value; 
            cache->put(key,value); 
            cout << "Inserted Successfully" << endl; 
        } 
        else if(command == "get"){ 
            if(cache==nullptr){
                cout<<"Cache Not Initialized"<<endl;
                continue;
            }
            int key; 
            cin >> key; 
            int result = cache->get(key); 
            if(result == -1){ 
                cout << "Key Not Found" << endl; 
            }
            else{ 
                cout << result << endl; 
            } 
        } 
        else if(command == "stats"){ 
            if(cache==nullptr){
                cout<<"Cache Not Initialized"<<endl;
                continue;
            }
            cout<<cache->getStats()<<endl; 
        } 
        else if(command == "exit"){ 
            cout << "Shutting Down" << endl; 
            break; 
        } 
        else{ 
            cout << "Invalid Command" << endl; 
        } 
        cout.flush(); 
    } 
    if(cache!=nullptr){
        delete cache;
    }
    return 0;
}