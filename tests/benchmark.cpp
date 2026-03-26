#include "../src/LRUCache.h"
#include <chrono>
#include <fstream>

using namespace std;

void benchmark(
    int operations,
    ofstream& file
)
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

    auto duration =
    chrono::duration_cast<
        chrono::milliseconds
    >(end-start);

    file
        << operations
        << ","
        << duration.count()
        << "\n";

    cout
        << operations
        << " -> "
        << duration.count()
        << " ms\n";
}

int main()
{
    ofstream file(
        "benchmark_results.csv"
    );

    file<<"operations,time_ms\n";

    benchmark(10000,file);

    benchmark(100000,file);

    benchmark(1000000,file);

    file.close();
}