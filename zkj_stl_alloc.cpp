#include  "zkj_stl_alloc.h"

namespace zkj_stl{

    void* fl_malloc::allocate(size_t _n){
        assert(_n > 0);
        if (_n > MAX_BYTES){
            return general_alloc::allocate(_n);
        }
        obj** cur_free_list;
        obj* res;

        cur_free_list = free_list + fl_index(_n);
        res = *cur_free_list;
        if (res == nullptr){
            void* temp = refill(round_up(_n));
            return temp;
        }
        *cur_free_list = res->fl_link;
        return res;
    }

    void fl_malloc::deallocate(void* _p, size_t _n){
        obj* temp = reinterpret_cast<obj*>(_p);
        obj** cur_free_list = free_list + fl_index(_n);
        if (_n > MAX_BYTES){
            general_alloc::deallocate(_p, _n);
        }
        temp->fl_link = *cur_free_list;
        *cur_free_list = temp;
    }

    void* fl_malloc::reallocate(void* _p,size_t _ord, size_t _new){
        void* res;
        if (_ord<_new && _new>MAX_BYTES){
            return general_alloc::reallocate(_p, _ord, _new);
        }

        size_t copy_size = _ord < _new ? _ord : _new;
        memcpy(res, _p, copy_size);
        deallocate(_p, _ord);
        return res;
    }

    void* fl_malloc::refill(size_t _n){
        size_t nobjs = 20;
        char* chunk = chunk_alloc(_n, nobjs);
        obj** cur_free_list;
        cur_free_list = free_list + fl_index(_n);

        if (1 == nobjs){
            return chunk;
        }
        obj* cur_obj, *next_obj,* res;
        res = reinterpret_cast<obj*>(chunk);
        *cur_free_list = next_obj = reinterpret_cast<obj*>(chunk + _n);

        for (int i = 1; i < nobjs; i++){
            cur_obj = next_obj;
            next_obj = reinterpret_cast<obj*>(reinterpret_cast<char*>(next_obj) + _n);
            if (i == nobjs - 1){
                cur_obj->fl_link = nullptr;
            }
            else{
                cur_obj->fl_link = next_obj;
            }
        }

        return reinterpret_cast<void*>(res);
    }

    char* fl_malloc::chunk_alloc(size_t _n, size_t& _nobjs){
        char* res;
        size_t total_size = _n * _nobjs;
        size_t left_bytes = end_free - head_free;
        if (left_bytes >= total_size){
            res = head_free;
            head_free = head_free + total_size;
            return res;
        }
        else if (left_bytes >= _n){
            res = head_free;
            _nobjs = left_bytes / _n;
            head_free += _n * _nobjs;
            return res;
        }
        else{
            head_free = static_cast<char*>(malloc(2 * total_size));
            end_free = head_free + 2 * total_size;
            return chunk_alloc(_n, _nobjs);
        }
            
        
    }

    char* fl_malloc::head_free = 0 ;
    char* fl_malloc::end_free = 0;
}//namespace zkj_stl

//mode:c++