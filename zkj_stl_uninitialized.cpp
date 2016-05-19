#include  "zkj_stl_uninitialized.h"

namespace zkj_stl{

    struct true_type;
    struct false_type;

    template<class IIter, class FIter>
    FIter uninitialized_copy(IIter _first, IIter _last, FIter _res){
        if (Iter_traits<*value_type(_first)>::is_POD == true_type){
            return copy(_first, _last, _res);
        }
        FIter cur = _res;
        while (first != last){
            construct(&*cur, *first);
            ++first;
            ++cur;
        }
        return cur;
    }

    template<class T, class FIter>
    void uninitialized_fill(FIter _first, FIter _last, const T& _value){
        if (Iter_traits<*value_type(_first)>::is_POD == true_type){
            fill(_first, _last, _value);
        }
        else{
            FIter cur = _first;
            while (cur != _last){
                construct(&*cur, _value);
                ++cur;
            }
        }
    }


    template<class T, class FIter, class Type>
    FIter uninitialized_fill_n(FIter _first, Type _type, const T& _value){
        if (Iter_traits<*value_type(_first)>::is_POD == true_type){
            return fill_n(_first, _type, _value);
        }
 
        FIter cur = _first;
        while (n--){
           construct(&*cur, _value);
            cur++;
        }
        return cur;
    }

}//namespace zkj_stl