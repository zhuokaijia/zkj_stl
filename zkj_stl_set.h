#ifndef _ZKJ_STL_SET_H_
#define _ZKJ_STL_SET_H_

#include "zkj_stl_rb_tree.h"

namespace zkj_stl{

    template<class T, class Alloc>
    class simple_alloc;

    class fl_malloc;

    template<class Key,class Compare=less<Key>,class Alloc=fl_malloc>
    class set{

    public:
        typedef Key     key_type;
        typedef Key     value_type;
        typedef Compare key_compare;
        typedef Compare value_compare;

    private:
        typedef rb_tree<key_type, value_type, identity<value_type>, key_compare, Alloc> rbt_type;
        rbt_type t;

    public:
        typedef typename rbt_type::const_pointer        pointer;
        typedef typename rbt_type::const_pointer        const_pointer;
        typedef typename rbt_type::const_reference      reference;
        typedef typename rbt_type::const_reference      const_reference;
        typedef typename rbt_type::const_iterator       iterator;
        typedef typename rbt_type::const_iterator       const_iterator;
        typedef typename rbt_type::difference_type      difference_type;


        set() :t(Compare()){};
        explicit set(const Compare&comp) :t(comp){}

        set(const set<Key, Compare, Alloc>& _X) :t(x.t){}
        set<Key, Compare, Alloc>& operator=(const set<Key, Compare, Alloc>& _x){
            t = x.t;
            return *this;
        }
        
        iterator begin()const{ return t.begin(); }
        iterator end()const{ return t.end(); }
        bool empty()const{ return t.empty(); }
        size_t size()const{ return t.size(); }
        size_t max_size()const{ return t.max_size(); }
        
        iterator insert(const value_type& _value){
            return t.insert_unique(_value);
        }
        void erase(const key_type& _x){
            return t.erase(_x);
        }
        void clear(){ return t.clear(); }
        iterator find(const key_type&_x)const{
            return t.find(x);
        }
    };

}//namespace zkj_stl

//mode:c++

#endif