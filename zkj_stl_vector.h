
#ifndef _ZKJ_STL_VECTOR_H_
#define _ZKJ_STL_VECTOR_H_

#include  <cstddef>             //for ptrdiff_t
#include  <utility>             //for std::move

namespace zkj_stk{

    class simple_malloc;
    class fl_malloc;

    template<class T,class Alloc=fl_malloc>
    class vector{
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef ptrdiff_t   difference_type;
        typedef T*          iterator;
        typedef const T*    const_iterator;
    protected:
        typedef simple_alloc<value_type, Alloc> data_allocator;
        iterator start;
        iterator finish;
        iterator end_of_storage;
    public:
        iterator begin(){ return start; }
        iterator end(){ return finish; }
        size_t size()const { return static_cast<size_t>(finish - start); }
        size_t capacity()const{ return static_cast<size_t>(end_of_storage - start); }
        bool empty()const { return start == finish; }
        reference operator[](size_t _n){ return *(begin + _n); }
        reference front(){ return *start; }
        const reference front()const{ return *start; }
        reference back(){ return *(finish - 1); }
        const reference back()const{ return *(finish - 1); }

        //constructor
        vector() :start(nullptr), finish(nullptr), end_of_storage(nullptr){};

        vector(size_t _n, const reference _value){
            initialize(_n, _value);
        }

        vector(int _n, const reference _value){
            initialize(_n, _value);
        }

        vector(long _n, const reference _value){
            initialize(_n, _value);
        }

        explicit vector(size_t n){
            initialize(_n, T());
        }

        void initialize(size_t _n, const reference _value){
            iterator res = data_allocator::allocate(_n);
            uninitialized_fill_n(result, _n, _value);
            start = res;
            finish = start + _n;
            end_of_storage = finish;
        }

        //destructor
        ~vector(){
            destroy(start, finish);
            deallocate();
        }

        void deallocate(){
            if (start){
                data_allocator::deallocate(start, end_of_storage - start);
            }
        }

        void reserve(size_t _n){
            if (capacity() < _n){
                const size_t old_size = size();
                iterator temp = allocate_and_copy(_n, start, finish);
                destroy(start, finish);
                deallocate();
                start = temp;
                finish = temp + old_size();
                end_of_storage = start + _n;
            }
        }

        void push_back(const reference _value){
            if (finish != end_of_storage){
                construct(finish, _value);
                ++finish;
            }
            else{
                _insert(end(), _value);
            }
        }

        void pop_back(){
            --finish;
            destroy(finish);
        }

        void swap(vector<T, Alloc>& _vec){
            _swap(finish, _vec.finish);
            _swap(start, _vec.start);
            _swap(end_of_storage, _vec.end_of_storage);
        }

        void resize(size_t _n, const reference _value){
            if (_n < size()){
                erase(start + _n, finish);
            }
            else{
                fill_insert(finish, _n - size(), _value);
            }
        }

        void resize(size_t _n){
            return resize(_n, T());
        }

        void clear(){
            erase(start, finish);
        }

        //erase
        iterator erase(iterator _pos){
            if (_pos + 1 != end()){
                copy(_pos + 1, finish, _pos);
            }
            --finish;
            destroy(finish);
            return _pos;
        }

        iterator erase(iterator _first, iterator _last){
            iterator temp = copy(_last, finish, _first);
            destroy(_i, finish);
            finish += _first - _last;
            return _first;
        }

        // equal to std::swap
        template<class T>
        void _swap(T& _v1, T& _v2){
            T v(std::move(_v1));
            v1 = std::move(_v2);
            v2 = std::move(v);
        }

        //insert
        iterator insert(iterator _pos, const reference _value){
            size_t n = _pos - begin();
            if (finish != end_of_storage&&_pos == finish){
                construct(finish, _value);
                ++finish;
            }
            else{
                _insert(_pos, _value);
            }
            return begin() + n;
        }

        void fill_insert(iterator _pos, size_t _n, const reference _value);

        //assign
        void assign(size_t _n, const_reference _value);

        template<class Iter>
        void assign(Iter _first, Iter _last){
            typedef typename type_traits<Iter>::is_POD valueType;
            _assign(_first, _last, valueType());
        }

        template<class Iter>
        _assign(Iter _first, Iter _last, true_type);

        template<class Iter>
        _assign(Iter _first, Iter _last, false_type);

        vector<T, Alloc>& operator=(const vector<T, Alloc>& vec);
        iterator allocate_and_copy(size_t, const_iterator, const_iterator);
    };


}//namespace zkj_Stl

//mode:c++

#endif