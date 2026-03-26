#include "../src/LRUCache.h"
#include <thread>
#include <vector>
#include <iostream>

using namespace std;

void worker(LRUCache& cache)
{
    for(int i=0;i<10000;i++)
    {
        cache.put(i,i);

        cache.get(i);

        cache.get(i+1);
    }
}

int main()
{
    LRUCache cache(1000);

    vector<thread> threads;

    int threadCount = 8;

    for(int i=0;i<threadCount;i++)
    {
        threads.emplace_back(
            worker,
            ref(cache)
        );
    }

    for(auto &t : threads)
    {
        t.join();
    }

    cout<<"Concurrent Test Passed"<<endl;

    cout<<cache.getStats()<<endl;
}