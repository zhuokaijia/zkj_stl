/*  NOTE:This is an internal header file,included by other header file.
 *  you should not attempt to use it directly
 */

#include  "zkj_stl_construct.h"

#ifndef  _ZKJ_STL_UNINITIALIZED_H_
#define  _ZKJ_STL_UNINITIALIZED_H_

namespace zkj_stl{

    template<class IIter,class FIter>
    FIter uninitialized_copy(IIter _first, IIter _last, FIter _res);

    template<class T,class FIter>
    void uninitialized_fill(FIter _first, FIter _last, const T& _value);

    template<class T,class FIter,class Type>
    FIter uninitialized_fill_n(FIter _frist, Type _type, const T& _value);

}//namespace zkj_stl


//mode: c++
#endif
