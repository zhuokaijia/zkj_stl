#include  "zkj_stl_deque.h"

namespace zkj_stl{
    
    template<class T,class Alloc,size_t buffer_size>
    void deque<T, Alloc, buffer_size>::fill_initialize(size_t _n, const_reference _value){
        creat_map_and_node(_n);
        map_pointer cur;
        for (cur = start.node; cur < finish.node; ++cur){
            uninitialized_fill(*cur, *cur + deque_buf_size(buff_size, sizeof(T)), _value);
        }
        uninitialized_fill(*cur, iterator(*cur).cur, _value);
    }

    template<class T,class Alloc,size_t buffer_size>
    void deque<T, Alloc, buffer_size>::creat_map_and_node(size_t _n){
        size_t node_nums = _n / deque_buf_size(buff_size, sizeof(T)) + 1;
        map_size = max(initial_map_size(), node_nums + 2);
        map = map_allocate(map_size);

        //make sure  the reservations on the both sides are equal
        map_pointer nstart = map + (map_size - node_nums) / 2;
        map_pointer nend = nstart + node_nums - 1;

        map_pointer cur;
        //allocate
        for (cur = nstart; cur <= nend; ++cur){
            *cur = node_allocate();
        }
        start.set_node(nstart);
        finish.set_node(nend);
        start.cur = start.first;
        finish.cur = finish.start + _n % deque_buf_size();
    }

    template<class T, class Alloc, size_t buffer_size>
    void deque<T, Alloc, buffer_size>::push_back_aux(const_reference _value){
        reserve_map_at_back();
        *(finish.node + 1) = node_allocate();
        construct(finish.cur, _value);
        finish.set_node(finish.node + 1);
        finish.cur = finish.start;
    }

    template<class T, class Alloc, size_t buffer_size>
    void deque<T, Alloc, buffer_size>::push_front_aux(const_reference _value){
        reserve_map_at_front();
        *(start.node - 1) = node_allocate();
        start.set_node(start.node - 1);
        start.cur = start.finish - 1;
        construct(start.cur, _value);
    }

    template<class T, class Alloc, size_t buffer_size>
    void deque<T, Alloc, buffer_size>::reserve_map_at_back(size_t node_to_add = 1){
        size_t old_nums = finish.node - first.node + 1;
        size_t new_nums = old_nums + node_to_add;

        map_pointer new_start;

        if (map_size > 2 * new_nums){
            new_start = map + (map_size - new_nums) / 2;
            if (new_start < start){
                copy(start.node, finish.node + 1, new_start);
            }
            else{
                copy_backward(start.node, finish.node + 1, new_start);
            }
        }
        else{
            size_t new_map_size = 2 * map_size + 2;
            map_pointer new_map = map_allocate(new_map_size);
            new_start = new_map + (new_map_size - old_nums) / 2;

            copy(start.node, finish.node + 1, new_start);
            map_deallocate(map, map_size);
            map = new_map;
            map_size = new_map_size;

        }
        start.set_node(new_start);
        finsh.set_node(new_start + old_nums - 1);
    }

    template<class T,class Alloc,size_t buffer_size>
    void 
    deque<T, Alloc, buffer_size>::reserve_map_at_front(size_t node_to_add = 1){
        size_t old_nums = finish.node - first.node + 1;
        size_t new_nums = old_nums + node_to_add;

        map_pointer new_start;

        if (map_size > 2 * new_nums){
            new_start = map + (map_size - new_nums) / 2 + node_to_add;
            if (new_start < start){
                copy(start.node, finish.node + 1, new_start);
            }
            else{
                copy_backward(start.node, finish.node + 1, new_start);
            }
        }
        else{
            size_t new_map_size = 2 * map_size + 2;
            map_pointer new_map = map_allocate(new_map_size);
            new_start = new_map + (new_map_size - old_nums) / 2 + node_to_add;

            copy(start.node, finish.node + 1, new_start);
            map_deallocate(map, map_size);
            map = new_map;
            map_size = new_map_size;

        }
        start.set_node(new_start);
        finsh.set_node(new_start + old_nums - 1);
    }

    template<class T, class Alloc, size_t buffer_size>
    typename deque<T,Alloc,buffer_size>::iterator   // QAQ
    deque<T, Alloc, buffer_size>::insert_aux(iterator _pos, const_reference _value){
        difference_type i = _pos - start;           // equals to _pos.cur - start.cur 
        if (i < size() / 2){
            push_front(front());
            iterator tmp1 = front;
            iterator tmp2 = tmp1;
            ++tmp2;
            copy(tmp2, _pos, tmp1);                 //move the element
        }
        else{
            push_back(end());
            iterator tmp1 = finish;
            iterator tmp2 = tmp1;
            --tmp2;
            copy_backward(_pos, tmp2, tmp1);
        }
        *_pos = _value;
        return _pos;
    }

    template<class T, class Alloc, size_t buffer_size>
    void deque<T, Alloc, buffer_size>::clear(){

        for (map_pointer i = start.node + 1; i < finish.node; ++i){
            destroy(*i, *i + deque_buf_size(buff_size, sizeof(T)));
            node_deallocate(*node, deque_buf_size(buff_size, sizeof(T)));
        }

        if (start.node != finish.node){
            destroy(start.cur, start.last);
            destroy(finish.first, finish.cur);
            node_deallocate(finish.node, deque_buf_size(buff_size, sizeof(T)));
        }
        else{
            destroy(start.cur, finish.cur);
        }

        start = finish;
    }

    template<class T, class Alloc, size_t buffer_size>
    typename deque<T, Alloc, buffer_size>::iterator   
    deque<T, Alloc, buffer_size>::earse(iterator _pos){
        difference_type i = _pos - start;
        iterator tmp = _pos;
        ++tmp;

        if (i < size() / 2){
            copy_backward(start, pos, next);
            pop_front();
        }
        else{
            copy(next, finish, pos);
            pop_back();
        }
        return start + i;
    }

}//namespace zkj_stl

//mode:c++