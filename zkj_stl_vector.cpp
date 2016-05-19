#include  "zkj_stl_vector.h"

namespace zkj_stl{
    

    template<class T,class Alloc>
    void vector<T,Alloc>::_insert(iterator _pos, const_reference _value){
        if (finish != end_of_storage){
            construct(finish, *(finish - 1));
            ++finish;
            copy_backward(_pos, finish - 2, finish - 1);
            *_pos = _value;
        }
        else{
            const size_t old_size = size();
            const size_t new_size = old_size()!=0 ? 2 * old_size : 1;
            new_start = data_allocator::allocate(new_size);
            new_finish = new_start;
            new_finish = uninitialized_copy(start, _pos, new_start);
            construct(new_finish, _value);
            ++new_finish;
            new_finish = uninitialized_copy(_pos, finish, new_finish);
            destroy(start, finish);
            deallocate();
            start = new_start;
            finish = new_finish;
            end_of_storage = start + new_size;
        }
        return 0;
    }

    template<class T,class Alloc>
    void vector<T, Alloc>::fill_insert(iterator _pos, size_t _n, const_reference _value){
        if (size_t(end_of_storage - finish) >= _n) {
            T _x_copy = _value;
            const size_t elems_after = finish - _pos;
            iterator old_finish = finish;
            if (elems_after > _n) {
                uninitialized_copy(finish - _n, finish, finish);
                finish += _n;
                copy_backward(_pos, old_finish - _n, old_finish);
                fill(_pos, _pos + _n, _x_copy);
            }
            else {
                uninitialized_fill_n(finish, _n - elems_after, _x_copy);
                _finish += _n - elems_after;
                uninitialized_copy(_pos, old_finish, finish);
                finish += elems_after;
                fill(_pos, old_finish, _x_copy);
            }
        }
        else {
            const size_t old_size = size();
            const size_t len = old_size + max(old_size, _n);
            iterator new_start = data_allocator::allocate(len);
            iterator new_finish = new_start;

            new_finish = uninitialized_copy(start, _pos, new_start);
            new_finish = uninitialized_fill_n(new_finish, _n, _value);
            new_finish = uninitialized_copy(_pos, finish, new_finish);

            destroy(start, finish);
            deallocate(start, end_of_storage - start);
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;
        }
    }

    template<class T,class Alloc>
    void vector<T,Alloc>::assign(size_t _n, const_reference _value){
        if (_n > capacity()){
            vector<T, Alloc> vec(_n, _value);
            _vec.swap(*this);
            //_vec.~vector();
        }
        else{
            fill(begin(), end(), _value);
            finish = uninitialized_fill_n(end(), _n - size(), _value);

        }
        else{
            fill(begin(), begin() + _n, _value);
            earse(begin() + _n, end());
            finish = begin() + _n;
        }
    }

    template<class T, class Alloc>
    vector<T, Alloc>& vector<T, Alloc>::operator=(const vector<T, Alloc>& _vec){
        if (&vec != this){
            const size_t s = vec.size();
            if (s > capacity()){
                iterator i = allocate_and_copy(s, _vec.begin(), _vec.end());
                destroy(start, finish);
                deallocate(start, end_of_storage);
                start = i;
                finsh = end_of_storage = i + s;
            }
            else if (s < size()){
                iterator i = copy(_vec.begin(), _vec.end(), begin());
                destroy(i, finish);
                finish = begin() + s;
            }
            else{
                copy(_vec.begin(), _vec.begin() + s, begin());
                uninitialized_copy(_vec.begin() + s, _vec.end(), end());
                finish = begin() + s;
            }
        }
        return *this;
    }
    
    

    
}//namespace zkj_stl

//mode:c++