#include "../src/LRUCache.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct BenchmarkMetrics
{
    long long latency;
    double hitRate;
    double throughput;
};

// --------------------------------------------------
// Read Heavy
// 90% GET
// 10% PUT
// --------------------------------------------------

BenchmarkMetrics runReadHeavy(int operations)
{
    LRUCache cache(10000);

    long long hits = 0;
    long long misses = 0;

    for(int i=0;i<5000;i++)
    {
        cache.put(i,i);
    }

    auto start =
        chrono::high_resolution_clock::now();

    for(int i=0;i<operations;i++)
    {
        if(rand()%10 < 9)
        {
            int key =
                rand()%5000;

            int value =
                cache.get(key);

            if(value==-1)
                misses++;
            else
                hits++;
        }
        else
        {
            cache.put(i+5000,i);
        }
    }

    auto end =
        chrono::high_resolution_clock::now();

    auto duration =
        chrono::duration_cast<
            chrono::milliseconds
        >(end-start).count();

    double hitRate = 0;

    if(hits+misses>0)
    {
        hitRate =
            (double)hits*100.0/
            (hits+misses);
    }

    double throughput =
        duration>0
        ?
        (double)operations*1000.0/duration
        :
        operations;

    return {
        duration,
        hitRate,
        throughput
    };
}

// --------------------------------------------------
// Write Heavy
// 90% PUT
// 10% GET
// --------------------------------------------------

BenchmarkMetrics runWriteHeavy(int operations)
{
    LRUCache cache(10000);

    long long hits = 0;
    long long misses = 0;

    auto start =
        chrono::high_resolution_clock::now();

    for(int i=0;i<operations;i++)
    {
        if(rand()%10 < 9)
        {
            cache.put(i,i);
        }
        else
        {
            int value =
                cache.get(rand()%5000);

            if(value==-1)
                misses++;
            else
                hits++;
        }
    }

    auto end =
        chrono::high_resolution_clock::now();

    auto duration =
        chrono::duration_cast<
            chrono::milliseconds
        >(end-start).count();

    double hitRate = 0;

    if(hits+misses>0)
    {
        hitRate =
            (double)hits*100.0/
            (hits+misses);
    }

    double throughput =
        duration>0
        ?
        (double)operations*1000.0/duration
        :
        operations;

    return {
        duration,
        hitRate,
        throughput
    };
}

// --------------------------------------------------
// Mixed Workload
// 50% GET
// 50% PUT
// --------------------------------------------------

BenchmarkMetrics runMixed(int operations)
{
    LRUCache cache(10000);

    long long hits = 0;
    long long misses = 0;

    auto start =
        chrono::high_resolution_clock::now();

    for(int i=0;i<operations;i++)
    {
        if(rand()%2)
        {
            cache.put(i,i);
        }
        else
        {
            int value =
                cache.get(rand()%5000);

            if(value==-1)
                misses++;
            else
                hits++;
        }
    }

    auto end =
        chrono::high_resolution_clock::now();

    auto duration =
        chrono::duration_cast<
            chrono::milliseconds
        >(end-start).count();

    double hitRate = 0;

    if(hits+misses>0)
    {
        hitRate =
            (double)hits*100.0/
            (hits+misses);
    }

    double throughput =
        duration>0
        ?
        (double)operations*1000.0/duration
        :
        operations;

    return {
        duration,
        hitRate,
        throughput
    };
}

// --------------------------------------------------
// Main
// --------------------------------------------------

int main(
    int argc,
    char* argv[]
)
{
    if(argc < 3)
    {
        cout
        << "Usage: "
        << "./workload_benchmark "
        << "<operations> "
        << "<workload>\n";

        return 1;
    }

    srand(time(nullptr));

    int operations =
        stoi(argv[1]);

    string workload =
        argv[2];

    BenchmarkMetrics result;

    if(workload == "read-heavy")
    {
        result =
    runReadHeavy(operations);
    }
    else if(workload == "write-heavy")
    {
        result =
    runReadHeavy(operations);
    }
    else
    {
        result =
    runReadHeavy(operations);
    }

    ofstream file(
        "reports/workload_results.json"
    );

    if(!file.is_open())
    {
        cerr
        << "Failed to open workload_results.json\n";

        return 1;
    }

    file
    << "[{"
    << "\"workload\":\""
    << workload
    << "\","
    << "\"latency\":"
<< result.latency
<< ","
<< "\"hit_rate\":"
<< fixed
<< setprecision(2)
<< result.hitRate
<< ","
<< "\"throughput\":"
<< result.throughput
    << "}]";

    file.close();

    cout
    << "Benchmark completed successfully\n";

    return 0;
}