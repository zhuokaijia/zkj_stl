/*  NOTE:This is an internal header file,included by other header file.
 *  you should not attempt to use it directly
 */

#include  <utility>

#ifndef _ZKJ_STL_RB_TREE_H_
#define _ZKJ_STL_RB_TREE_H_

namespace zkj_stl{

    //rb_tree_node
    typedef bool color_type;
    const color_type red = false;
    const color_type black = true;

    struct rb_tree_node_base{

        typedef rb_tree_node_base* pointer;

        color_type  color;
        pointer     parent;
        pointer     left;
        pointer     right;

        static pointer mininum(pointer _p){
            while (_p->left != nullptr){
                _p = _p->left;
            }

            return _p;
        }

        static pointer maxinum(pointer _p){
            while (_p->right != nullptr){
                _p = _p->right;
            }

            return _p;
        }
    };

    template<class T>
    struct rb_tree_node :public rb_tree_node_base{
        T value;
    };

    //rb_tree iterator
    struct rb_tree_iterator_base{
        typedef typename rb_tree_node_base::pointer     base_ptr;
        typedef ptrdiff_t                               difference_type;

        base_ptr    node;

        void increase(){
            //case 1
            if (node->right != nullptr){
                node = node->right;
                while (node->left != nullptr){
                    node = node->left;
                }
            }
            //case 2
            else{
                base_ptr y = node->parent;
                while (y->right == node){
                    node = y;
                    y = y->parent;
                }
                if (node->right != y){
                    node = y;
                }
            }
        }

        void decrease(){
            //case 1
            if (node->color == red&&node->parent->parent == node){
                node = node->right;
            }
            //case 2
            else if (node->left != nullptr){
                base_ptr y = node->left;
                while (y->right){
                    y = y->right;
                }
                node = y;
            }
            //case 3
            else{
                base_ptr y = node->parent;
                while (node == y->left){
                    node = y;
                    y = y->parent;
                }
                node = y;
            }
        }

        template<class T,class Ref,class Ptr>
        struct rb_tree_iterator :public rb_tree_iterator_base{
            typedef T                                               value_type;
            typedef Ref                                             reference;
            typedef Ptr                                             pointer;
            typedef rb_tree_iterator<T, T&, T*>                     iterator;
            typedef rb_tree_iterator<T, const T&, const T*>         const_iterator;
            typedef rb_tree_iterator<T, Ref, Ptr>                   self;
            typedef rb_tree_node<T>*                                link_type;

            //constructor
            rb_tree_iterator(){}
            rb_tree_iterator(link_type _p){ node = _p; }
            rb_tree_iterator(const rb_tree_iterator& _itr){ node = _itr->node; }

            reference operator*()const{ return link_type(node)->value; }
            pointer operator->()const{ return &(operator*()); }
            self& operator++(){
                increase();
                return *this;
            }
            self& operator++(int){
                self tmp = *this;
                increase();
                return tmp;
            }
            self& operator--(){
                decrease();
                return *this;
            }
            self& operator--(int){
                self tmp = *this;
                desrease();
                return tmp;

            }
        };

    };

    //forward-declared
    class fl_malloc;

    //forward-declared
    template<class T,class Alloc=fl_malloc>
    class simple_alloc;


    //rb_tree
    template<class Key,class Value,class KeyOfValue,class Compare,class Alloc=fl_malloc>
    class rb_tree{

    protected:
        typedef rb_tree_node<Value>                                 rb_tree_node;
        typedef rb_tree_node_base*                                  base_ptr;
        typedef simple_alloc<rb_tree_node, Alloc>                   node_allocator;

    public:
        typedef Key                                                 key_type;
        typedef Value                                               value_type;
        typedef value_type*                                         pointer;
        typedef const value_type*                                   const_pointer;
        typedef value_type&                                         reference;
        typedef const value_type&                                   const_reference;
        typedef rb_tree_node*                                       link_type;
        typedef ptrdiff_t                                           difference_type;
        typedef rb_tree_iterator<value_type, reference, pointer>    iterator;

    protected:

        size_t              node_nums;
        link_type           header;
        Compare             comp;

        link_type get_node(){ return node_allocator::allocate(); }
        void del_node(link_type _p){ return node_allocator::deallocate(_p); }

        link_type creat_node(const value_type _value){
            link_type p = get_node();
            construct(&(p->value), _value);
        }

        void destroy_node(link_type _p){
            destroy(_p);
            del_node(_p);
        }

        link_type clone_node(link_type _p){
            link_type tmp = creat_node(_p->value);
            tmp->color = base_ptr(_p)->color;
            tmp->left = nullptr;
            tmp->right = nullptr;
            return tmp;
        }

        link_type& root()const{ return (link_type&)header->parent; }
        link_type& leftmost()const{ return (link_type&)header->left; }
        link_type& rightmost()const{ return (link_type&)header->right; }


        static link_type& left(link_type _x){
            return _x->left;
        }
        static link_type& right(link_type _x){
            return _x->right;
        }
        static link_type& parent(link_type _x){
            return  _x->parent;
        }
        static link_type& value(link_type _x){
            return _x->value;
        }
        static link_type& key(link_type _x){
            return KeyOfValue()(value(_x));
        }
        static link_type& color(link_type _x){
            return _x->color;
        }

        static link_type& left(base_ptr _x){
            return _x->left;
        }
        static link_type& right(base_ptr _x){
            return _x->right;
        }
        static link_type& parent(base_ptr _x){
            return  _x->parent;
        }
        static link_type& value(base_ptr _x){
            return link_type(_x)->value;
        }
        static link_type& key(base_ptr _x){
            return KeyOfValue()(value(link_type(_x)));
        }
        static link_type& color(base_ptr _x){
            return _x->color;
        }

        //get maximum
        static link_type maximum(link_type _p){
            return static_cast<link_type>(rb_tree_node_base::maxinum(_p));
        }

        //get minimum
        static link_type minimum(link_type _p){
            return static_cast<link_type>(rb_tree_node_base::mininum(_p));
        }

    private:

        void init(){
            header = get_node();
            color(header) = red;

            root() = nullptr;
            leftmost() = header;
            rightmost() = header;
        }

        //_y is _x's parent node
        iterator _insert(base_ptr _x, base_ptr _y, const Value _value);

        link_type node_copy(link_type _x, link_type _y);

    public:
        rb_tree(const Compare& _comp=Compare()):comp(_comp),node_nums(0){
            init();
        }

        rb_tree(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& _x){
            if (_x->node_nums == 0){
                init();
            }
            else{
                color(header) = red;
                root() = node_copy(_x.root(), header);
                leftmost() = minimum(root());
                rightmost() = maximum(root());

            }
            node_nums = _x.node_nums;
        }

        ~rb_tree(){
            clear();
            del_node(header);
        }

        void earse(iterator _pos){
            link_type y = rb_tree_banlance_for_earse(_pos.node, root(), leftmost(), rightmost());
            destroy_node(_pos.node);
            node_nums--;
        }

        iterator begin(){ return leftmost(); }
        iterator end(){ return header; }
        size_t size(){ return node_nums; }
        size_t max_size(){ return static_cast<size_t>(-1); }
        bool empty(){ return node_nums == 0; }
        Compare key_comp(){ return comp; }

        //allow duplicate
        iterator insert_equal(const Value& _value);
        //disalloc duplicate
        iterator insert_unique(const Value& _value);
        iterator find(const Key& _key);
        
    };

    inline void rb_tree_rotate_left(rb_tree_node_base* _x,
                                rb_tree_node_base*& _root /* pass by reference*/){
        rb_tree_node_base* y = _x->right;
        _x->right = y->left;
        if (y->left != nullptr){
            y->left->parent = _x;
        }
        y->parent = _x->parent;
        
        if (_x == _root){
            _root = y;
        }
        else if (_x->parent->left == _x){
            _x->parent->left = y;
        }
        else{
            _x->parent->right = y;
        }

        y->left = _x;
        _x->parent = y;
    }

    inline void rb_tree_rotate_right(rb_tree_node_base* _x,
                            rb_tree_node_base*& _root /* pass by reference*/){
        rb_tree_node_base* y = _x->left;
        _x->left = y->right;
        if (y->right != nullptr){
            y->right->parent = _x;
        }
        y->parent = _x->parent;

        if (_x == _root){
            _root == y;
        }
        else if (_x == _x->parent->left){
            _x->parent->left = y;
        }
        else{
            _x->parent->right = y;
        }

        y->right = _x;
        _x->parent = y;
    }

    //to make sure the balance of rb_tree
    //case 1:_x's uncle node is red
    //case 2:_x's uncle node is black and _x is a left child
    //case 3:_x's uncle node is black and _x is a right child
    void rb_tree_node_balance(rb_tree_node_base* _x,
                            rb_tree_node_base*& _root /* pass by reference*/){
        
        _x->color = red;                //must be red
        while (_x != _root&&_x->parent->color == red){
            if (_x->parent == _x->parent->parent->left){
                rb_tree_node_base* y = _x->parent->parent->right;
                if (y != nullptr&&y->color == red){     //case 1
                    _x->parent->color = black;
                    y->color = black;
                    y->parent->color = red;
                    _x = _x->parent->parent;
                }
                else{
                    if (_x == _x->parent->right){               //case 3
                        _x = _x->parent;                //convert case 3 to case 2
                        rb_tree_rotate_left(_x, _root);
                    }
                    //case 2
                    _x->parent->color = black;
                    _x->parent->parent->color = red;
                    rb_tree_rotate_right(_x->parent->parent, _root);

                }
            }
            else{
                rb_tree_node_base* y = _x->parent->parent->left;
                if (y != nullptr&&y->color == red){     //case 1
                    _x->parent->color = black;
                    y->color = black;
                    y->parent->color = red;
                    _x = _x->parent->parent;
                }
                else{
                    if (_x == _x->parent->left){               //case 3
                        _x = _x->parent;                //convert case 3 to case 2
                        rb_tree_rotate_right(_x, _root);
                    }
                    //case 2
                    _x->parent->color = black;
                    _x->parent->parent->color = red;
                    rb_tree_rotate_left(_x->parent->parent, _root);

                }
            }
        }

        _root->color = black;                       //must be black
    }

    //to make sure the balance of rb_tree
    //we set w as _x's brother node
    //case 1:the color of w is red
    //case 2:the color of w is black,and both of w'children is black
    //case 3:the color of w is black, color(w->left)==red and color(w->right)==black
    //case 4:the color of w is black, color(w->right)==red
    rb_tree_node_base* rb_tree_banlance_for_earse(rb_tree_node_base* _z, rb_tree_node_base*& _root,
                            rb_tree_node_base*& _leftmost, rb_tree_node_base*& _rightmost){
        
        rb_tree_node_base* y = _z;
        rb_tree_node_base* x = nullptr;
        rb_tree_node_base* xp = nullptr;
        /*find the successor*/
        if (y->left == nullptr){
            x = y->right;                       //x might be null
        }
        else if (y->right == nullptr){
            x = y->left;                        //x might be null
        }
        else{
            y = y->right;
            while (y->left){
                y = y->left;
            }
            x = y->right;                       //x might be null
        }

        if (y == _z){
            xp = y->parent;

            if (x){
                x->parent = y->parent;
            }

            if (_root == _z){
                _root = x;
            }
            else if (_z->parent->left == _z){
                x = _z->parent->left;
            }
            else{
                x = _z->parent->right;
            }

            /*updata leftmost and right most*/
            if (_rightmost == _z){                      //_z->right must be null
                if (_z->left == nullptr){
                    _rightmost = _z->parent;
                }
                else{
                    _rightmost = rb_tree_node_base::maxinum(x);
                }
            }
            if (_leftmost == _z){                       //_z->left must be null
                if (_z->right == nullptr){          
                    _leftmost = _z->parent;
                }
                else{
                    _leftmost = rb_tree_node_base::mininum(x);
                }
            }

        }
        else{                                           //y != _z
            _z->left->parent = y;
            y->left = _z->left;
            if (y != _z->right){                         
                xp = y->parent;
                if (x){
                    x->parent = y->parent;
                }
                y->parent->left = x;
                y->right = _z->right;
                _z->right->parent = y;
            }
            else{
                xp = y;
            }

            if (_root == _z){
                _root = x;
            }
            else if (_z->parent->left == _z){
                _z->parent->left = y;
            }
            else{
                _z->parent->right = y;
            }

            y->parent = _z->parent;
            std::swap(y->color, _z->color);
            y = _z;
        }

        if (y->color == black){
            while (x != _root && (x == nullptr || x->color == black)){
                if (x == xp->left){
                    rb_tree_node_base* w = xp->right;
                    if (w->color == red){                                       //case 1
                        w->color = black;
                        xp->color = red;
                        rb_tree_rotate_left(xp, _root);
                        w = xp->right;
                    }
                    if ((w->left == nullptr || w->left->color == black) &&      //case 2
                        (w->right == nullptr || w->right->color == black)){

                        w->color = red;
                        x = xp;
                        xp = xp->parent;
                    }
                    else{
                        if (w->right == nullptr || w->right->color == black){   //case 3
                            if (w->left){
                                w->left->color = black;
                            }
                            w->color = red;
                            rb_tree_rotate_right(w, _root);
                            w = xp->right;
                        }
                        w->color = xp->color;                                   //case 4
                        xp->color = black;
                        if (w->right){
                            w->right->color = black;
                        }
                        rb_tree_rotate_left(xp, _root);
                        break;                                                  // loop completes
                    }
                }
                else{                    // same as then clause with "right" and "left" exchanged

                    rb_tree_node_base* w = xp->left;
                    if (w->color == red){                                       //case 1
                        w->color = black;
                        xp->color = red;
                        rb_tree_rotate_right(xp, _root);
                        w = xp->left;
                    }
                    if ((w->right == nullptr || w->right->color == black) &&    //case 2
                        (w->left == nullptr || w->left->color == black)){

                        w->color = red;
                        x = xp;
                        xp = xp->parent;
                    }
                    else{
                        if (w->left == nullptr || w->left->color == black){     //case 3
                            if (w->right){
                                w->right->color = black;
                            }
                            w->color = red;
                            rb_tree_rotate_left(w, _root);
                            w = xp->left;
                        }
                        w->color = xp->color;                                   //case 4
                        xp->color = black;
                        if (w->left){
                            w->left->color = black;
                        }
                        rb_tree_rotate_right(xp, _root);
                        break;                                                  // loop completes
                    }
                }
                if (x){
                    x->color = black;
                }
            }
        }

        return y;
    }


    template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::link_type 
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
    node_copy(link_type _x, link_type _y){
        
        link_type tmp = clone_node(_x);
        tmp->parent = _y;
        if (_x->right){
            tmp->right = node_copy(right(_x), tmp);
        }
        _y = tmp;
        _x = left(_x);
        while (_x != nullptr){
            link_type t = clone_node(_x);
            _y->left = t;
            t->parent = _y;
            if (_x->right){
                _y->right = node_copy(right(_x), _y);
            }
            _y = t;
            _x = left(_x);
        }
        return tmp;
    }


    template<class Key,class Value,class KeyOfValue,class Compare,class Alloc>
    typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
    _insert(rb_tree_node_base* _x, rb_tree_node_base* _y, const Value _value){

        typedef rb_tree_node*          link_type;
        link_type tmp=creat_node(_value);
        if (_y == header || _x != nullptr || comp(key(tmp), key(_y))){
            left(_y) = tmp;
            if (_y == header){
                root() = tmp;
                rightmost() = tmp;
            }
            else if (_y == leftmost()){
                leftmost() == tmp;
            }
        }
        else{
            right(_y) = tmp;
            if (_y == rightmost()){
                rightmost()= tmp;
            }
        }
        parent(tmp) = _y;
        left(tmp) = nullptr;
        right(tmp) = nullptr;
        rb_tree_node_balance(tmp, root());
        ++node_nums;
        return iterator(tmp);

    }   



    template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
    insert_equal(const Value& _value){
        link_type y = header;
        link_type x = root();
        while (x != nullptr){
            y = x;
            x = comp(KeyOfValue()(_value), key(x)) ? left(x), right(x);
        }
        return _insert(x, y, _value);
    }


    template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
    insert_unique(const Value& _value){
        
        link_type y = header;
        link_type x = root();
        bool cp = true;
        while (x != nullptr){
            y = x;
            cp = comp(key(x), KeyOfValue()(_value));
            x = cp ? right(x) : left(x);
        }

        iterator j = iterator(y);
        if (!cp){

            if (j == begin()){
                return insert(x, y, _value);
            }
            else{
                j--;
            }
        }

        if (comp(key(j.node), KeyOfValue()(_value))){
            return insert(x, y, _value);
        }

        return j;
    }


    template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
    find(const Key& _key){
        
        link_type y = header;
        link_type x = root();
        while (x != nullptr){
            if (comp(k, key(x))){
                y = x;
                x = left(x);
            }
            else{
                x = right(x);
            }
        }

        iterator j = iterator(y);
        if (j == end() || comp(k, key(j.node))){
            return end();
        }
        else{
            return j;
        }
    }




}//namespace zkj_stl

#endif

//mode:c++