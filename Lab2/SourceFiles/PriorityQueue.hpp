#pragma once
#include <vector>
#include "WL_Pair.hpp"
using namespace std;


using PData = vector<WL_Pair>;

class PriorityQueue
{
    // PriorityQueue as min-heap

public:
    PriorityQueue() = default;
    PriorityQueue(const PData, const unsigned, const unsigned);
    WL_Pair Top() const { return heap.front(); }
    bool Empty() const { return heap.empty(); }
    unsigned Size() const { return heap.size(); }
    void Pop();
    void Change(const unsigned, const unsigned, const double);

private:
    void UpHeapify(unsigned);
    void DownHeapify(unsigned);
    void BuildHeap();

    unsigned Left(const unsigned i) const { return 2*i; }
    unsigned Right(const unsigned i) const { return 2*i+1; }
    bool DownHeapCheck(const unsigned child, const unsigned target) const {
        return child<heap.size() and heap[child] < heap[target];
    }


    PData heap;                             // The actual data managed
    unsigned S, W;                          // Number of stores and warehouses
    vector<vector<unsigned>> index;         // Index of pair (s, w) in min-heap
};