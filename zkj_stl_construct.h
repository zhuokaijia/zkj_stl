/*  NOTE:This is an internal header file,included by other header file.
 *  you should not attempt to use it directly
 */

#ifndef _ZKJ_STL_CONSTRUCT_H_
#define _ZKJ_STL_CONSTRUCT_H_

#include  <new>           //placement new

namespace zkj_stl{

    // construct()
    template<class T1,class T2>
    inline void construct(T1* _p, const T2& value){
        new reinterpret_cast<void*>(_p) T1(value);
    }

    template<class T>
    inline void construct(T* _p){
        new reinterpret_cast<void*>(_p)T1();
    }

    // destroy()
    template<class T>
    inline void destroy(T* _p){
        _p->~T();
    }

    template<class FORWARDITERATOR,class T>
    inline void __destroy(FORWARDITERATOR first, FORWARDITERATOR last){
        for (; first < last; ++first){
            destroy(&*first);
        }
    }

    template<class FORWARDITERATOR>
    inline void destroy(FORWARDITERATOR first, FORWARDITERATOR last){
        __destroy(first, last);
    }

    inline void destroy(char*, char*) {}
    inline void destroy(int*, int*) {}
    inline void destroy(long*, long*) {}
    inline void destroy(float*, float*) {}
    inline void destroy(double*, double*) {}

#ifdef UNICODE
    inline void destroy(wchar_t*,wchar_t*){}
#endif
   
}//namespace zkj_stl

//mode: c++

#endif
