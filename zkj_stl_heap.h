#ifndef _ZKJ_STL_HEAP_H_
#define _ZKJ_STL_HEAP_H_

#include  <utility>

namespace zkj_stl{

    //heap-manipulation functions

    //note:the last_iterator in heap fuction is point to the last element in container
    // by default,heap = MAX_HEAP
    template<class RIter,class T>
    void push_heap(RIter _first, ptrdiff_t _pos, const T& _value){
        ptrdiff_t parent = (_pos - 1) / 2;
        while (_pos > 0 && *(_first + parent) < *(_first + _pos)){
            *(_first + parent) =std::move( *(_first + _pos));
            _pos = parent;
            parent = (_pos - 1) / 2;
        }
        *(_first + _pos) = _value;
    }

    template<class RIter,class T ,class Compare>
    void push_heap(RIter _first, ptrfidd_t _pos, const T& _value,Compare comp){
        ptrdiff_t parent = (_pos - 1) / 2;
        while (_pos > 0 && comp(*(_first + parent) , *(_first + _pos))){
            *(_first + parent) = std::move(*(_first + _pos));
            _pos = parent;
            parent = (_pos - 1) / 2;
        }
        *(_first + _pos) = _value;
    }

    template<class RIter, class T>
    void push_heap(RIter _first, RIter _pos, const T& _value){
        push_heap(_first, (_pos - _first), _value);
    }

    template<class RIter, class T, class Compare>
    void push_heap(RIter _first, RIter _pos, const T& _value, Compare comp){
        push_heap(_first, _pos - _first, _value, comp);
    }

    //note:after pop_heap function,the maximum was only move to the end of container
    //you should  remove it by container.pop_back() function
    template<class RIter,class T>
    void pop_heap(RIter _first,ptrdiff_t _start, ptrdiff_t _pos,const T& _value){
        int i = _start;
        int next = 2 * i + 2;
        while (next <= _pos){
            if (*(_first + next) < *(_first + next - 1)){
                --next;
            }
            *(_first + i) = std::move(*(_first + next));
            i = next;
            next = 2 * i + 2;
        }

        if (next - 1 == _pos){
            *(_first + i) = std::move(*(_first + next - 1));
            i = next - 1;
        }

        push_heap(_first, i, _value);
    }

    template<class RIter, class T,class Compare>
    void pop_heap(RIter _first, ptrdiff_t _start, ptrdiff_t _pos, const T& _value, Compare comp){
        int i = _start;
        int next = 2 * i + 2;
        while (next <= _pos){
            if (comp(*(_first + next) , *(_first + next - 1))){
                --next;
            }
            *(_first + i) = std::move(*(_first + next));
            i = next;
            next = 2 * i + 2;
        }

        if (next - 1 == _pos){
            *(_first + i) = std::move(*(_first + next - 1));
            i = next - 1;
        }

        push_heap(_first, i, _value, comp);
    }

    template<class RIter, class T>
    void pop_heap(RIter _first, RIter _pos, const T& _value){
        pop_heap(_first, 0, _pos - _first, _value);
    }

    template<class RIter, class T,class Compare>
    void pop_heap(RIter _first, RIter _pos, const T& _value,Compare comp){
        pop_heap(_first, 0, _pos - _first, _value, comp);
    }

    template<class RIter,class T>
    void sort_heap(RIter _first, RIter _last){
        while (_last != _first){
            std::swap(*_first, *_last);
            T tmp = *_first;
            pop_heap(_first, _last--,tmp);
        }
    }

    template<class RIter,class T,class Compare>
    void sort_heap(RIter _first, RIter _last, Compare comp){
        while (_last != _first){
            std::swap(*_first, *_last);
            T tmp = *_first;
            pop_heap(_first, _last--, tmp,comp);
        }
    }

    template<class RIter,class T>
    void make_heap(RIter _first, RIter _last){
        if (_last - _first < 1){
            return;
        }
        ptrdiff_t len = _last - _first;
        ptrdiff_t parent = (_last - _first - 1) / 2;
        while (parent > 0){
            pop_heap(_first, parent, len, *parent);
        }
    }

    template<class RIter, class T,class Compare>
    void make_heap(RIter _first, RIter _last,Compare comp){
        if (_last - _first < 1){
            return;
        }
        ptrdiff_t len = _last - _first;
        ptrdiff_t parent = (_last - _first - 1) / 2;
        while (parent > 0){
            pop_heap(_first, parent, len, *parent,comp);
        }
    }

    // bug free please

}//namespace zkj_stl

//mode:c++

#endif