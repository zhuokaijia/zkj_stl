#include "zkj_stl_list.h"

namespace zkj_stl{
    
    template<class T,class Alloc>
    void list<T, Alloc>::clear(){
        link_type tmp = node->next;
        while (tmp != node){
            link_type cur = tmp->next;
            tmp = tmp->next;
            destroy(cur);
        }
        node->next = node;
        node->pre = node;
    }

    template<class T, class Alloc>
    void list<T, Alloc>::remove(const T& _value){
        iterator first = begin();
        iterator last = end();
        while (first != last){
            if (first.node->data == _value){
                first = erase(first);
            }
            else{
                first = first.node->next;
            }
        }
    }

    template<class T,class Alloc>
    void list<T, Alloc>::unique(){
        iterator first = begin();
        iterator last = end();
        if (first == last){
            return;
        }

        iterator next = first;
        while (++next != last){
            if (first.node->data == next.node->date){
                erase(next);
                next = first;
            }
            else{
                first = next;
            }
            
        }
    }

    template<class T,class Alloc>
    void list<T, Alloc>::transfer(iterator _pos, iterator _first, iterator _last){
        if (_pos != _last){
            (link_type((link_type(_last->node))->pre))->next = _pos->node;
            (link_type((link_type(_first->node))->pre))->next = _last->node;
            (link_type((link_type(_pos->node))->pre))->next = _first->node;
            link_type tmp=(link_type(link_type(_pos->node))->pre);
            (link_type(_pos->node))->pre = (link_type(_last->node))->pre);
            (link_type(_last->node))->pre = (link_type(_first->node))->pre);
            (link_type(_first->node))->pre = tmp;
        }
    }

    template<class T,class Alloc>
    void list<T, Alloc>::splice(iterator _pos, list<T,Alloc>& _list){
        if (!_list.empty()){
            transfer(_pos, _list.begin(), _list.end());
        }
    }

    template<class T,class Alloc>
    void list<T, Alloc>::splice(iterator _pos, list<T,Alloc>& _list, iterator _i){
        iterator j = _i;
        j++;
        if (_pos != _i&&_pos != j){
            transfer(_pos, _i, j);
        }
    }

    template<class T,class Alloc>
    void list<T, Alloc>::splice(iterator _pos, iterator _first, iterator _last){
        if (_first != _last){
            transfer(_pos, _first, _last);
        }
    }

    template<class T,class Alloc>
    void list<T, Alloc>::merge(list<T, Alloc>& _list){
        iterator first1 = begin();
        iterator last1 = end();
        iterator first2 = _list.begin();
        iterator last2 = _list.end();
        while (first1 != last1&&first2 != last2){
            if (*first2 < *first1){
                iterator next = first2.node->next;
                transfer(first1, first2, next);
                first2 = next;
            }
            else{
                ++first1;
            }
        }

        if (first2 != last2){
            transfer(last1, first2, last2); 
        }
    }

    template<class T,class Alloc>
    void list<T, Alloc>::reverse(){
        if (node->next == node || node->next->next == node) return;
        iterator first = begin();
        ++first;
        while (first != end()){
            iterator pre = fisrt;
            ++first;
            transfer(begin(), old, first);
        }
    }

    // merge sort
    template<class T,class Alloc>
    void list<T, Alloc>::sort(){
        list<T, Alloc> carry;
        list<T, Alloc> counter[64];
        int fill = 0;
        while (!empty()){
            carry.splice(carry.begin(), *this, begin());
            int i = 0;
            while (i < fill&&!counter[i].empty()){
                carry.merge(counter[i]);
                i++;
            }

            carry.swap(count[i]);
            if (i == fill) ++fill;
        }

        for (int i = 1; i < fill; ++i){
            counter[i].merge(counter[i - 1]);
        }
        swap(counter[fill - 1]);
    }

    template<class T,class Alloc>
    void list<T, Alloc>::assign(size_t _n, const T& _value){
        link_type cur = begin();
        while (_n-- && cur!= nullptr){
            cur->data = _value;
            cur = cur->next;
        }
        if (_n != 0){
            while (_n--){
                push_back(_value);
            }
        }
        else{
            while (cur != nullptr){
                cur = erase(cur);
            }
        }
    }

    template<class T,class Alloc>
    void list<T, Alloc>::assign(iterator _first, iterator _last){
        link_type cur = begin();
        while (cur != nullptr&&_first!=_last){
            cur->data = (link_type(_first->node))->data;
            cur = cur->next;
            ++_first;
        }
        if (_first != _last){
            do{
                push_back(link_type(_first->node))->data);
                _first++;
            } while (_first!=_last)
        }
        else{
            while (cur != nullptr){
                cur = erase(cur);
            }
        }
    }
    

    template<class T,class Alloc>
    list<T, Alloc>& list<T, Alloc>::operator=(const list<T, Alloc>& _list){
        assign(_list.begin(), _list.end());
        return *this;
    }

}//namespace zkj_stl

//mode:c++