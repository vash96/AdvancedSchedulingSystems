#include "PriorityQueue.hpp"
#include <algorithm>
// #include <numeric>

PriorityQueue::PriorityQueue(const PData load, const unsigned S, const unsigned W)
    : heap(move(load)), S(S), W(W)
{
    BuildHeap();
}


void PriorityQueue::Pop()
{
    swap(heap.front(), heap.back());
    heap.pop_back();

    if(not heap.empty()) {
        const auto& top = heap.front();
        index[top.s][top.w] = 0;
        DownHeapify(0);
    }
}


void PriorityQueue::Change(const unsigned s, const unsigned w, const double cost)
{
    unsigned idx = index[s][w];     // Index of (s, w) in heap
    auto & pp = heap[idx];          // Corresponding load
    double delta = cost - pp.cost;  // Cost difference

    pp.cost = cost;
    if(delta < 0.0) {
        UpHeapify(idx);
    }else {
        DownHeapify(idx);
    }
}

void PriorityQueue::BuildHeap()
{
    make_heap(heap.begin(), heap.end(), [this](const WL_Pair& a, const WL_Pair& b) {
        return b < a;
    });

    index.resize(S, vector<unsigned>(W));
    for(unsigned i=0; i<heap.size(); ++i) {
        const auto& el = heap[i];
        index[el.s][el.w] = i;
    }
}

void PriorityQueue::UpHeapify(unsigned u)
{
    auto curr = heap[u];
    auto par  = heap[u/2];
    while(u>0 and curr<par) {
        // If curr < parent, swap
        swap(index[curr.s][curr.w], index[par.s][par.w]);
        swap(heap[u], heap[u/2]);

        // Jump to parent
        u /= 2;
        curr = heap[u];
        par  = heap[u/2];
    }
}

void PriorityQueue::DownHeapify(unsigned u)
{
    unsigned left, right, target;

    do {
        target = u;
        left   = Left(u);
        right  = Right(u);

        if(DownHeapCheck(left, target)) {
            target = left;
        }
        if(DownHeapCheck(right, target)) {
            target = right;
        }

        if(target != u) {
            auto loadU = heap[u];
            auto loadT = heap[target];
            swap(index[loadU.s][loadU.w], index[loadT.s][loadT.w]);
            swap(heap[u], heap[target]);
            swap(u, target);
        }

    }while(target != u);
}