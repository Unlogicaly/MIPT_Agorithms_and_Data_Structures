//
// Created by tarog on 3/19/2020.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>

template <typename T, class Cmp = std::less<T>>
class Heap {
  private:
    Cmp cmp;

    std::vector<T> heap;

    void SiftUp(size_t index) {

        if (index > heap.size())
            return;

        while (index != 0 && cmp(heap[index], heap[Parent(index)])) {
            std::swap(heap[index], heap[Parent(index)]);
            index = Parent(index);
        }
    }

    size_t GetSwapIndex(size_t childIndex, size_t swapIndex) {

        if (childIndex < heap.size() && cmp(heap[childIndex], heap[swapIndex])) {
            swapIndex = childIndex;
        }
        return swapIndex;
    }

    void SiftDown(size_t index) {

        while (index < heap.size()) {
            size_t swapIndex = index;
            swapIndex = GetSwapIndex(Left(index), swapIndex);
            swapIndex = GetSwapIndex(Right(index), swapIndex);
            if (swapIndex != index) {
                std::swap(heap[index], heap[swapIndex]);
                index = swapIndex;
            }
            else {
                break;
            }
        }
    }

  public:
    Heap() = default;

    explicit Heap(const std::vector<T> &arr) : heap(arr) {

        for (size_t i = (heap.size() >> 1); i > 0; --i) {
            SiftDown(i - 1);
        }
    }

    template <typename _Iter>
    Heap(_Iter begin, _Iter end) : heap(begin, end) {

        for (auto i = (heap.size() >> 1); i > 0; --i) {
            SiftDown(i - 1);
        }
    }

    explicit Heap(const Heap<T> &rhs) : heap(rhs.heap) {}

    Heap(Heap &&rhs) noexcept : heap(std::move(rhs.heap)) {}

    Heap &operator=(const Heap<T> &rhs) {

        if (this != &rhs) {
            heap = rhs.heap;
        }
        return *this;
    }

    Heap &operator=(Heap<T> &&rhs) {

        if (this != &rhs) {
            heap = std::move(rhs.heap);
        }
    }

    bool operator==(const Heap &rhs) const {

        return heap == rhs.heap;
    }

    size_t Parent(size_t index) const {

        return (index - 1) >> 1;
    }

    size_t Left(size_t index) const {

        return (index << 1) + 1;
    }

    size_t Right(size_t index) const {

        return (index + 1) << 1;
    }

    bool empty() const {

        return heap.empty();
    }

    const T &top() const {

        return heap[0];
    }

    void pop() {

        if (!heap.empty()) {
            std::swap(heap.front(), heap.back());
            heap.resize(heap.size() - 1);
            SiftDown(0);
        }
    }

    void add(const T &element) {

        heap.push_back(element);
        SiftUp(heap.size() - 1);
    }

    size_t size() {

        return heap.size();
    }
};


#endif //HEAP_H
