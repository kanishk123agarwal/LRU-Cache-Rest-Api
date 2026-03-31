#include "../src/LRUCache.h"

#include <chrono>
#include <fstream>
#include <vector>

using namespace std;

struct BenchmarkResult
{
    int operations;
    long long time_ms;
};

BenchmarkResult runBenchmark(int operations)
{
    LRUCache cache(10000);

    auto start =
        chrono::high_resolution_clock::now();

    for(int i=0;i<operations;i++)
    {
        cache.put(i,i);
        cache.get(i);
    }

    auto end =
        chrono::high_resolution_clock::now();

    long long duration =
        chrono::duration_cast<
            chrono::milliseconds
        >(end-start).count();

    return {
        operations,
        duration
    };
}

int main()
{
    vector<int> testCases =
    {
        1000,
        10000,
        100000,
        1000000
    };

    vector<BenchmarkResult> results;

    for(int ops : testCases)
    {
        results.push_back(
            runBenchmark(ops)
        );
    }

    ofstream file(
        "../report/benchmark_results.json"
    );

    file << "[\n";

    for(size_t i=0;i<results.size();i++)
    {
        file
        << "  {"
        << "\"operations\":"
        << results[i].operations
        << ","
        << "\"time_ms\":"
        << results[i].time_ms
        << "}";

        if(i+1<results.size())
            file << ",";

        file << "\n";
    }

    file << "]";

    file.close();

    cout
    << "benchmark_results.json generated\n";

    return 0;
}