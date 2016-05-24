#ifndef _ZKJ_STL_PRIORITY_QUEUE_H_
#define _ZKJ_STL_PRIORITY_QUEUE_H_

#include  "zkj_stl_heap.h"

namespace zkj_stl{
    
    //forward-declared
    template<class T,class Alloc>
    class vector;

    template<class T, class Sequence = vector < T > , class Compare>
    class priority_queue{
    public:
        typedef typename Sequence::value_type              value_type;
        typedef typename Sequence::reference               reference;
        typedef typename Sequence::const_reference         const_reference;
    protected:
        Sequence c;
        Compare comp;
    public:
        priority_queue(){}
        explicit priority_queue(const Compare& _comp) :c(), comp(_comp){}

        template<class IIter>
        priority_queue(IIter _first, IIter _last,Compare _comp)
                        : c(_first, _last), comp(_comp){
            make_heap(c.begin(), c.end() - 1, comp);
        }

        template<class IIter>
        priority_queue(IIter _first, IIter _last) : c(_first, _last){
            make_heap(c.begin(), c.end() - 1);
        }

        bool empty()const{ return c.empty(); }
        size_t size()const{ return c.size(); }
        const_reference top()const{ return c.front(); }
        void push(const_reference _value){
            c.push_back(_value);
            push_heap(c.begin(), size() - 1, _value, comp);
        }
        void pop(){
            swap(c.front(), c.end());
            c.pop_back();
            pop_heap(c.begin(), 0, c.size() - 1, c.front(), comp);
        }
    };


}//namespace zkj_stl

//mode:c++

#endif
