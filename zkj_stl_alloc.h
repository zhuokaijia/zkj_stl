/*  NOTE:This is an internal header file,included by other header file.
 *  you should not attempt to use it directly
 */

#ifndef _ZKJ_STL_ALLOC_H_
#define _ZKJ_STL_ALLOC_H_

#include  <cassert>
#include  <cstdlib>
#include  <cstdio>         
#include  <cstring>                 //for memcpy

namespace zkj_stl{

    template<class T,class Alloc=fl_malloc>
    class simple_alloc{
        static T* allocate(size_t _n){
            return (0 == _n) ? 0 : static_cast<T*>(Alloc::allocate(n*sizeof(T));
        }
        static T* allocate(){
            return (0 == _n) ? 0 : static_cast<T*>(Alloc::allocate(sizeof(T));
        }
        static void deallocate(T* _p, size_t _n){
            if (0 != _n){
                Alloc::deallocate(_p, _n*sizeof(T));
            }
        }
        static void deallocate(T*_p){
            Alloc::deallocate(_p, sizeof(T));
        }
    };

    const int ALIGN = 8;
    const int MAX_BYTES = 128;
    const int NFLISTS = MAX_BYTES / ALIGN;

    // if the client request an object of size > MAX_BYTES
    // the object will be obtained directly by malloc
    class general_alloc{
    public:
        static void* allocate(size_t _n){
            void* res = malloc(_n);
            assert(res != nullptr);
            return res;
        }

        static void* deallocate(void* _p, size_t){
            free(_p);
            _p = nullptr;
        }

        static void* reallocate(void* _p, size_t,size_t _n){
            void* res = realloc(_p, _n);
            assert(res != nullptr);
            return res;
        }
    };

    // if the client request an object of size <= MAX_BYTES
    // the object will be obtained by fl_malloc
    class fl_malloc{            //free-list-malloc
    private:
        static inline size_t round_up(size_t _n){
            return (_n + ALIGN - 1)& (~(ALIGN - 1));
        }

        union obj{
            union obj* fl_link;
            char data[1];
        };

        // free-lists
        static obj* free_list[NFLISTS];
        // from 0 to NFLISTS - 1
        static size_t fl_index(size_t _n){
            return (_n + ALIGN - 1) / ALIGN - 1;
        }

        static void* refill(size_t _n);
        // _nobjs pass by reference
        static char* chunk_alloc(size_t _n, size_t& _nobjs);

        //change in chunk_alloc function
        static char* head_free;
        static char* end_free;

    public:
        static void* allocate(size_t _n);
        static void  deallocate(void* _p, size_t _n);
        static void* reallocate(void* _P, size_t _o,size_t _n);
    };

    

}//namespace zkj_stl

//mode:c++

#endif