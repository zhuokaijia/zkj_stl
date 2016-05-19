/*  NOTE:This is an internal header file,included by other header file.
 *  you should not attempt to use it directly
 */

#ifndef _ZKJ_STL_ITER_H_
#define _ZKJ_STL_ITER_H_

#include  <cstddef>         //for ptrdiff_t
#include  <cassert>

namespace zkj_stl{

    //basic iterator
    template<class Category,class T,class Distance=ptrdiff_t,
             class Pointer = T*,class Reference = T&>
    struct iterator{
        typedef Category    Iter_type;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
    };

    //for argument deducation
    struct IIter_tag {};
    struct OIter_tag {};
    struct FIter_tag :public IIter_tag {};
    struct BIter_tag :public FIter_tag {};
    struct RIter_tag :public BIter_tag {};

    template<class T,class Distance>
    struct IIter{
        typedef IIter_tag   Iter_type;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef T*          pointer;
        typedef T&          reference;
    };

    struct OIter{
        typedef OIter_tag   Iter_type;
        typedef void        value_type;
        typedef void        difference_type;
        typedef void        pointer;
        typedef void        reference;
    };

    template<class T, class Distance>
    struct FIter{
        typedef FIter_tag   Iter_type;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef T*          pointer;
        typedef T&          reference;
    };

    template<class T, class Distance>
    struct BIter{
        typedef BIter_tag   Iter_type;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef T*          pointer;
        typedef T&          reference;
    };

    template<class T, class Distance>
    struct RIter{
        typedef RIter_tag   Iter_type;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef T*          pointer;
        typedef T&          reference;
    };

    template<class Iter>
    struct Iter_traits{
        typedef typename Iter::Iter_type            Iter_type;
        typedef typename Iter::value_type           value_type;
        typedef typename Iter::difference_type      difference_type;
        typedef typename Iter::pointer              pointer;
        typedef typename Iter::reference            reference;
    };

    //partial specialization for pointer
    template<class T>
    struct Iter_traits < T* > {
        typedef typename RIter_tag      Iter_type;
        typedef typename T              value_type;
        typedef typename ptrdiff_t      difference_type;
        typedef typename T*             pointer;
        typedef typename T&             reference;
    };

    //partial specialization for const pointer
    template<class T>
    struct Iter_traits < const T* > {
        typedef typename RIter_tag      Iter_type;
        typedef typename T              value_type;
        typedef typename ptrdiff_t      difference_type;
        typedef typename const T*       pointer;
        typedef typename const T&       reference;
    };

    //return the category of iterator
    template<class Iter>
    inline typename Iter_traits<Iter>::Iter_type
    Iter_type(const Iter&){
        typedef typename Iter_traits<Iter>::Iter_type  iter_type;

        // return the default constructor of struct iter_type
        return iter_type();                 
    }

    //return the value_type of iterator
    template<class Iter>
    inline typename Iter_traits<Iter>::value_type*
    value_type(const Iter&){
        return static_cast<typename Iter_traits<Iter>::value_type*>(0);
    }

    //return the difference_type of iterator
    template<class Iter>
    inline typename Iter_traits<Iter>::difference_type*
    difference_type(const Iter&){
        return static_cast<typename Iter_traits<Iter>::difference_type*>(0);
    }

    template<class IIter,class Distance>
    inline void _distance(IIter _first, IIter _last, Distance& _n, IIter_tag){
        while (_first != _last){
            ++_n;
            ++_first;
        }
    }

    template<class RIter,class Distance>
    inline void _distance(RIter _first, RIter _last, Distance& _n, RIter_tag){
        _n += _last - _first;
    }

    template<class IIter,class Distance>
    inline void distance(IIter _first, IIter _last, Distance& _n){
        typedef typename Iter_traits<IIter>::Iter_type type;
        _distance(_first, _last, _n, type());
    }

    template<class IIter,class Distance>
    inline void _advance(IIter& _first, Distance _n, IIter_tag){
        assert(_n >= 0);
        while (_n--){
            ++_first;
        }
    }

    template<class BIter,class Distance>
    inline void _advance(BIter& _first, Distance _n, BIter_tag){
        if (_n > 0){
            while (_n--) ++_first;
        }
        else{
            while (_n++) --_first;
        }
    }

    template<class RIter,class Distance>
    inline void _advance(RIter& _first, Distance _n, RIter_tag){
        _first += _n;
    }

    template<class IIter,class Distance>
    inline void advance(IIter& _first, Distance _n){
        _advance(_first, _n, Iter_type(IIter));
    }

}//namespace zkj_stl

//mode:c++

#endif