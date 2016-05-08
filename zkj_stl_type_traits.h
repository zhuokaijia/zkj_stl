/*  NOTE:This is an internal header file,included by other header file.
 *  you should not attempt to use it directly
 */

#ifndef ZKJ_STL_TYPE_TRAITS_H_
#define ZKJ_STL_TYPE_TRAITS_H_

namespace zkj_stl{

    //for argument deducation
    struct true_type{};
    struct false_type{};

    template<class T>
    struct type_traits{
        typedef true_type   has_default_constructor;
        typedef true_type   has_copy_constructor;
        typedef true_type   has_assignment_constructor;
        typedef true_type   has_destructor;
        typedef false_type  is_POD;
    };

    // partial specialization for bool
    struct type_traits<bool>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for char
    struct type_traits<char>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for signed char
    struct type_traits<signed char>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for unsigned char
    struct type_traits<unsigned char>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };
#ifdef UNICODE

    // partial specialization for wchar_t
    struct type_traits<wchar_t>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

#endif

    // partial specialization for short
    struct type_traits<short>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for unsigned short
    struct type_traits<unsigned short>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for int
    struct type_traits<int>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for unsigned int
    struct type_traits<unsigned int>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for long
    struct type_traits<long>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for unsigned long
    struct type_traits<unsigned long>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for long long
    struct type_traits<long long>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for unsigned long long
    struct type_traits<unsigned long long>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for float
    struct type_traits<float>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for double
    struct type_traits<double>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for long double
    struct type_traits<long double>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for pointer
    template<class T>
    struct type_traits<T*>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

    // partial specialization for const pointer
    template<class T>
    struct type_traits<const T*>{
        typedef false_type   has_default_constructor;
        typedef false_type   has_copy_constructor;
        typedef false_type   has_assignment_constructor;
        typedef false_type   has_destructor;
        typedef true_type    is_POD;
    };

}//namespace zkj_stl

//mode: c++

#endif