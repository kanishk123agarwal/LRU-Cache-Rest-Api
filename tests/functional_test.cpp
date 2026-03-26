#include "../src/LRUCache.h"
#include <cassert>
#include <iostream>

using namespace std;

int main()
{
    // -------------------------
    // Test 1: Basic Put/Get
    // -------------------------

    {
        LRUCache cache(2);

        cache.put(1,10);

        assert(cache.get(1) == 10);

        cout << "Test 1 Passed\n";
    }

    // -------------------------
    // Test 2: Capacity Overflow
    // -------------------------

    {
        LRUCache cache(2);

        cache.put(1,10);
        cache.put(2,20);
        cache.put(3,30);

        assert(cache.get(1) == -1);

        cout << "Test 2 Passed\n";
    }

    // -------------------------
    // Test 3: Update Existing Key
    // -------------------------

    {
        LRUCache cache(2);

        cache.put(1,10);
        cache.put(1,50);

        assert(cache.get(1) == 50);

        cout << "Test 3 Passed\n";
    }

    // -------------------------
    // Test 4: LRU Correctness
    // -------------------------

    {
        LRUCache cache(2);

        cache.put(1,10);
        cache.put(2,20);

        cache.get(1);

        cache.put(3,30);

        assert(cache.get(2) == -1);

        cout << "Test 4 Passed\n";
    }

    // -------------------------
    // Test 5: Missing Key
    // -------------------------

    {
        LRUCache cache(2);

        assert(cache.get(999) == -1);

        cout << "Test 5 Passed\n";
    }

    cout << "\nAll Functional Tests Passed\n";

    return 0;
}