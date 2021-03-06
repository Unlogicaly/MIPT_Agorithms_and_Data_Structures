//
// Created by tarog on 3/19/2020.
//

#ifndef UNTITLED_QUICK_SORT_H
#define UNTITLED_QUICK_SORT_H

#include <functional>
#include <vector>
#include <random>

template <typename _Iter, class _Cmp>
_Iter pivot(_Iter begin, _Iter end, _Cmp cmp = {}) {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> uni(0, end - begin - 1);

    auto _a = begin + uni(rng), _b = begin + uni(rng), _c = begin + uni(rng);

    if (cmp(*_a, *_b)) {
        if (cmp(*_b, *_c))
            return _b;
        if (cmp(*_a, *_c))
            return _c;
        return _a;
    }
    if (cmp(*_a, *_c))
        return _a;
    if (cmp(*_b, *_c))
        return _c;
    return _b;
}

template <typename _Iter, class _Cmp>
_Iter partition(_Iter begin, _Iter end, _Cmp cmp = {}) {

    auto p = pivot(begin, end, cmp);

    auto pivot = *p;

    std::swap(*p, *(end - 1));
    --end;

    auto i = begin, j = end - 1;

    while (i < j) {
        while (i != end and cmp(*i, pivot))
            ++i;
        while (j != begin and !cmp(*j, pivot))
            --j;

        if (i < j)
            std::swap(*i, *j);
    }

    std::swap(*end, *i);

    return i;
}

template <typename _Iter, class _Cmp>
void quick_sort(_Iter begin, _Iter end, _Cmp cmp = {}) {

    while (end - begin > 2) {
        _Iter p_ind = partition<_Iter, _Cmp>(begin, end);
        if (p_ind - begin < end - p_ind + 1) {
            quick_sort(begin, p_ind, cmp);
            begin = p_ind + 1;
        }
        else {
            quick_sort(p_ind + 1, end, cmp);
            end = p_ind;
        }
    }
    if (end - begin == 2 and cmp(*(begin + 1), *begin))
        std::swap(*begin, *(begin + 1));
}

template <typename _Iter>
_Iter pivot(_Iter begin, _Iter end) {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> uni(0, end - begin - 1);

    auto _a = begin + uni(rng), _b = begin + uni(rng), _c = begin + uni(rng);

    if (*_a < *_b) {
        if (*_b < *_c)
            return _b;
        if (*_a < *_c)
            return _c;
        return _a;
    }
    if (*_a < *_c)
        return _a;
    if (*_b < *_c)
        return _c;
    return _b;
}

template <typename _Iter>
_Iter partition(_Iter begin, _Iter end) {

    auto p = pivot(begin, end);

    auto pivot = *p;

    std::swap(*p, *(end - 1));
    --end;

    auto i = begin, j = end - 1;

    while (i < j) {
        while (i != end and *i < pivot)
            ++i;
        while (j != begin and *j >= pivot)
            --j;

        if (i < j)
            std::swap(*i, *j);
    }

    std::swap(*end, *i);

    return i;
}

template <typename _Iter>
void quick_sort(_Iter begin, _Iter end) {

    while (end - begin > 2) {
        _Iter p_ind = partition(begin, end);
        if (p_ind - begin < end - p_ind + 1) {
            quick_sort(begin, p_ind);
            begin = p_ind + 1;
        }
        else {
            quick_sort(p_ind + 1, end);
            end = p_ind;
        }
    }
    if (end - begin == 2 and *(begin + 1) < *begin)
        std::swap(*begin, *(begin + 1));
}

#endif //UNTITLED_QUICK_SORT_H
