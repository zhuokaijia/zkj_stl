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
        }
    }

    template<class T,class Alloc>
    void list<T, Alloc>::splice(iterator, list&){
        
    }


}//namespace zkj_stl

//mode:c++