#ifndef _ZKJ_STL_DEQUE_H_
#define _ZKJ_STL_DEQUE_H_

#include  <cstddef> // for ptrdiff_t 
#include  <cmath>   // for ceil()
#include  "zkj_stl_uninitialized.h"

namespace zkj_stl{

    struct RIter_tag;

    template<class T,class Alloc>
    class simple_alloc;

    class fl_malloc;

    //deque iterator
    template<class T,class REF,class PTR,size_t buff_size>
    struct deque_iterator{
        typedef RIter_tag Iter_type;
        typedef deque_iterator<T,T&,T*,buff_size>                 iterator;
        typedef deque_iterator<T, const T&, const T*,buff_size>   const_iterator;
        typedef T                                                 value_type;
        typedef T&                                                reference;
        typedef T*                                                pointer;
        typedef const T&                                          const_reference;
        typedef const T*                                          const_pointer;
        typedef ptrdiff_t                                         difference_type;
        typedef T**                                               map_pointer;
        typedef deque_iterator                                    self;

        T*          cur;
        T*          first;
        T*          last;
        map_pointer node;

        static size_t buffer_size(){ return deque_buf_size(buff_size,sizeof(T)); }

        //constructor
        deque_iterator(T* _x, map_pointer _y) :cur(_x), first(*_y),
            last(*y + buffer_size()), node(*_y){}
        deque_iterator() :cur(nullptr), first(nullptr), last(nullptr), node(nullptr){}
        deque_iterator(const iterator& _x) :cur(_x.cur), first(_x.first)
            last(_x.last), node(_x.node){}

        reference operator*()const{ return *cur; }
        pointer operator->()const{ return &(operator*()); }

        void set_node(map_pointer _x){
            node = _x;
            first = *_x;
            last = first + difference_type(buffer_size());
        }

        difference_type operator-(const self&_x){
            return difference_type(buffer_size())*(node - _x.node - 1)
                + (cur - first) + (last - _x.cur);
        }

        self operator++(){
            ++cur;
            if (cur == last){
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }

        //post-position
        self operator++(int){
            self tmp = *this;
            ++tmp;
            return tmp;
        }

        self operator--(){
            if (cur == first){
                set_node(node - 1);
                cur = last;
            }
            --cur;
            return *this;
        }

        //post-position
        self operator--(int){
            self tmp = *this;
            --tmp;
            return tmp;
        }

        self operator+=(difference_type _n){
            difference_type offset = _n + (cur - first);
            if (offset >= 0 && offset < difference_type(buffer_size())){
                cur += n;
            }
            else{
                difference_type node_offset = (offset >= 0 ?
                    offset / difference_type(buffer_size())
                    : difference_type(floor((offset) / buffer_size()));
                set_node(node + node_offset);
                cur += first + (offset - node_offset*difference_type(buffer_size()));
            }
            return *this;
        }

        self operator+(difference_type _n)const{
            self tmp = *this;
            tmp += _n;
            return tmp;
        }

        self operator-=(difference_type _n){
            return *this += -_n;
        }

        self operator-(difference_type _n)const{
            self tmp = *this;
            tmp -= _n;
            return tmp;
        }

        reference operator[](difference_type _n)const{
            return *(*this + n);
        }

        bool operator==(const self _x)const{
            return cur == _x.cur;
        }

        bool operator!=(const self _x)const{
            return cur != _x.cur;
        }

        bool operator<(const self _x)const{
            return node == _x.node ? (cur < _x.cur) : (node < _x.node);
        }

        bool operator<=(const self _x)const{
            return node == _x.node ? (cur <= _x.cur) : (node < _x.node);
        }

        bool operator>(const self _x)const{
            return node == _x.node ? (cur > _x.cur) : (node > _x.node);
        }

        bool operator>=(const self _x)const{
            return node == _x.node ? (cur >= _x.cur) : (node >= _x.node);
        }
    };

    inline size_t deque_buf_size(size_t _n, size_t _sz){
        return _n != 0 ? _n : (_sz < 512 ? ceil(size_t(512 / _sz)) : size_t(1));
    }

    //deque
    template<class T,class Alloc=fl_malloc,size_t buff_size=0>
    class deque{
    public:
        typedef T                                                   value_type;
        typedef T*                                                  pointer;
        typedef T&                                                  reference;
        typedef const T*                                            const_pointer;
        typedef const T&                                            const_reference;
        typedef deque_iterator<T, T&, T*, buff_size>                iterator;
        typedef deque_iterator<T, const T&, const T*, buff_size>    const_iterator;
        typedef ptrdiff_t                                           difference_type;

    protected:
        typedef simple_alloc<T, Alloc>                              data_allocator;
        typedef simple_alloc<pointer, Alloc>                        map_pointer_allocator;
        typedef T**                                                 map_pointer;

        iterator                start;
        iterator                finish;
        map_pointer             map;
        size_t                  map_size;

    public:
        iterator begin(){ return start; }
        const_iterator begin()const{ return start; }
        iterator end(){ return finish; }
        const_iterator end()const{ return finish; }
        reference operator[](size_t _n){ return start[_n]; }
        const_reference operator[](size_t _n)const{ return start[_n };
        reference front(){ return *start; }
        const_reference front()const{ return *start; }
        reference back(){
            iterator tmp = finish;
            --tmp;
            return *tmp;
        }
        const_reference back()const{
            iterator tmp = finish;
            --tmp;
            return *tmp;
        }
        size_t size()const{ return finish - start; }
        bool empty()const{ return start == finish; }
        size_t initial_map_size()const{
            return 0x00000008;
        }


        //constructor
        pointer node_allocate(){
            return data_allocator::allocate(deque_buf_size(buff_size, sizeof(T)));
        }

        map_pointer map_allocate(size_t _n){
            return map_pointer_allocator::allocate(_n);
        }


        deque(int _n, const_reference& _value){
            fill_initialize(_n, _value);
        }

        deque(){ creat_map_and_node(0); }

        explicit deque(size_t _n){
            T tmp;
            fill_initialize(_n, tmp);
        }

        void push_back(const_reference _value){
            if (finish.cur != finish.last - 1){
                construct(finish.cur, _value);
                ++finish.cur;
            }
            else{
                push_back_aux(_value);
            }
        }

        void push_front(const_reference _value){
            if (finish.cur != start.first){
                --start.cur;
                construct(start.cur, _value);
            }
            else{
                push_front_aux(_value);
            }
        }

        iterator insert(iterator _pos, const_reference _value){
            if (_pos.cur == start.cur){
                push_front(_value);
                return start;
            }
            else if(_pos.cur==finish.cur){
                push_back(_value);
                iterator tmp = finish;
                --tmp;
                return tmp;
            }
            else{            
                return insert_aux(_pos, _value);
            }
        }

        //deallocate

        void node_deallocate(pointer _p){
            return data_allocator::deallocate(_p, deque_buf_size(buff_size, sizeof(T)));
        }


        void map_deallocate(map_pointer _p, size_t _n){
            return map_pointer_allocator::deallocate(_p, _n);
        }

        void pop_back(){
            if (finish.cur != finish.first){
                --finish.cur;
                destroy(finish.cur);
            }
            else{
                node_deallocate(finish.first);
                finish.set_node(finish.node - 1);
                finish.cur = finish.last - 1;
                destroy(finish.cur);
            }
        }

        void pop_front(){
            if (start.cur != start.last - 1){
                destroy(start.cur);
                --start.cur;
            }
            else{
                destroy(start.cur);
                node_deallocate(start.first);
                start.set_node(start.node + 1);
                start.cur = start.first;
            }
        }



        //implement in zkj_stl_deque.h

        void fill_initialize(size_t _n, const_reference _value);
        void creat_map_and_node(size_t _node_nums);
        void push_back_aux(const_reference _value);
        void push_front_aux(const_reference _value);
        void reserve_map_at_back(size_t _n = 1);
        void reserve_map_at_front(size_t _n = 1);
        iterator insert_aux(iterator _pos, const_reference _value);

        void clear();
        iterator earse(iterator _pos);

    };



}//namesapce skj_stl

//mode:c++

#endif