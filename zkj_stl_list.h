#ifndef _ZKJ_STL_LIST_H_
#define _ZKJ_STL_LIST_H_

#include  <cstddef>             //for ptrdiff_t

namespace zkj_stl{
     
    template<class T, class Alloc>
    class simple_alloc;

    //list node
    template<class T>
    struct list_node{
        void* pre;
        void* next;
        T data;
    };

    struct BIter_tag;
    
    template<class T>
    inline list_node<T>* 
        list_prev_node(list_node<T>*_head, list_node<T>*_node){
        if (_head&&_head->next != _node){
            _head = _head->next;
        }
        return _head;
    }

    template<class T>
    inline const list_node<T>*
        list_prev_node(const list_node<T>*_head, const list_node<T>*_node){
        if (_head&&_head->next != _node){
            _head = _head->next;
        }
        return _head;
    }


    //list iterator
    template<class T>
    struct list_iterator{
        typedef list_iterator iterator;
        typedef list_iterator self;

        typedef BIter_tag           Iter_type;
        typedef T                   value_type;
        typedef T*                  pointer;
        typedef T&                  reference;
        typedef list_node<T>*       link_type;
        typedef ptrdiff_t           difference_type;
        
        link_type node; `

        list_iterator(){ node = nullptr; }
        list_iterator(pointer _p){ node = _p; }
        list_iterator(const iterator& _i){ node = _i.node; }


        bool operator== (const iterator&_x) const{ return node == _x.node; }
        bool operator!= (const iterator&_x) const{ return node != _x.node; }
        reference operator*() const{ return (*node).data; }
        pointer operator ->() const{ return &(operator*()); }

        self& operator++(){
            node = static_cast<link_type>((*node).next);
            return *this;
        }

        self operator++(int){
            self tmp = *this;
            ++*this;
            return tmp;
        }

        self& operator--(){
            node = static_cast<link_type>((*node).pre);
            return *this;
        }

        self operator--(int){
            self tmp = *this;
            --*this;
            return tmp;
        }
    };

    class fl_malloc;

    template<class T,class Alloc=fl_malloc>
    class list{
    public:
        typedef list_node<T>            list_nde;
        typedef list_node*              link_type;
        typedef list_iterator<T>        iterator;
        typedef const list_iterator<T>  const_iterator;
        typedef T                       value_type;
        typedef value_type*             pointer;
        typedef const value_type*       const_pointer;
        typedef value_type&             reference;
        typedef const value_type&       const_reference;
        typedef ptrdiff_t               difference_type;

    protected:
        link_type node;
        typedef typename simple_alloc<T,Alloc> list_node_allocator;

    public:
        link_type get_node()const{ return list_node_allocator::allocate(); }
        void empty_init(){
            node = get_node();
            node->next = node;
            node->pre = node;
        }
        //delete list_node
        void del_node(link_type _p){ list_node_allocator::deallocate(_p); }
        link_type create_node(const T& _value){
            link_type _P = get_node;
            construct(_p->data, _value);
            return _p;
        }

        iterator begin(){ return (link_type)((*node).next); }
        iterator end(){ return node; }
        reference front(){ return *begin(); }
        reference back(){ return *(back()--); }

        bool empty()const{ return node->next == node; }
        size_t size()const{
            size_t res=0;
            distance(begin(), end(), res);
            return res;
        }


        void push_front(const T& _value){
            insert(begin(), _value);
        }

        void push_back(const T& _value){
            insert(end(), _value);
        }

        iterator insert(iterator _pos, const T& _value){
            link_type tmp = create_node(_value);
            tmp->next = _pos.node;
            tmp->pre = _pos.node->pre;
            (link_type(_pos.node->pre))->next = tmp;
            _pos.node->pre = tmp;
            return static_cast<iterator>(tmp);
        }

        iterator earse(iterator _pos){
            link_type pre_node = static_cast<link_type>(_pos.node->pre);
            link_type next_node = static_cast<link_type>(_pos.node->next);
            pre_node->next = next_node;
            next_node->pre = pre_node;
            destroy(_pos);
            return static_cast<iterator>(next_node);
        }

        void pop_back(){ earse(begin()); }
        void pop_front(){ earse((--end())); }

        //implement in zkj_stl_list.cpp
        void clear();
        void remove(const T&);
        void unique();
        void splice(iterator, list&);
        void splice(iterator, list&, iterator);
        void splice(iterator, iterator, iterator);
        void merge(list&);
        void reverse();
        void sort();
        void transfer(iterator, iterator, iterator);
    };
}//namespace zkj_stl

#endif

//mode:c++