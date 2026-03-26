#include "LRUCache.h"

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