#include "../src/LRUCache.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>

using namespace std;

// --------------------------------------------------
// Read Heavy
// 90% GET
// 10% PUT
// --------------------------------------------------

long long runReadHeavy()
{
    LRUCache cache(10000);

    // Preload cache
    for(int i=0;i<5000;i++)
    {
        cache.put(i,i);
    }

    auto start = chrono::high_resolution_clock::now();

    for(int i=0;i<100000;i++)
    {
        if(rand()%10 < 9)
        {
            cache.get(rand()%5000);
        }
        else
        {
            cache.put(i+5000,i);
        }
    }

    auto end = chrono::high_resolution_clock::now();

    return chrono::duration_cast<
        chrono::milliseconds
    >(end-start).count();
}

// --------------------------------------------------
// Write Heavy
// 90% PUT
// 10% GET
// --------------------------------------------------

long long runWriteHeavy()
{
    LRUCache cache(10000);

    auto start = chrono::high_resolution_clock::now();

    for(int i=0;i<100000;i++)
    {
        if(rand()%10 < 9)
        {
            cache.put(i,i);
        }
        else
        {
            cache.get(rand()%5000);
        }
    }

    auto end = chrono::high_resolution_clock::now();

    return chrono::duration_cast<
        chrono::milliseconds
    >(end-start).count();
}

// --------------------------------------------------
// Mixed Workload
// 50% GET
// 50% PUT
// --------------------------------------------------

long long runMixed()
{
    LRUCache cache(10000);

    auto start = chrono::high_resolution_clock::now();

    for(int i=0;i<100000;i++)
    {
        if(rand()%2)
        {
            cache.put(i,i);
        }
        else
        {
            cache.get(rand()%5000);
        }
    }

    auto end = chrono::high_resolution_clock::now();

    return chrono::duration_cast<
        chrono::milliseconds
    >(end-start).count();
}

// --------------------------------------------------
// Main
// --------------------------------------------------

int main()
{
    srand(time(nullptr));

    ofstream file("workload_results.csv");

    file << "workload,time_ms\n";

    long long readHeavyTime = runReadHeavy();
    long long writeHeavyTime = runWriteHeavy();
    long long mixedTime = runMixed();

    file << "read-heavy," << readHeavyTime << "\n";
    file << "write-heavy," << writeHeavyTime << "\n";
    file << "mixed," << mixedTime << "\n";

    file.close();

    cout << "========== Results ==========\n";
    cout << "Read Heavy  : " << readHeavyTime << " ms\n";
    cout << "Write Heavy : " << writeHeavyTime << " ms\n";
    cout << "Mixed       : " << mixedTime << " ms\n";

    cout << "\nCSV Generated Successfully\n";

    return 0;
}