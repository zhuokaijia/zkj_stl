#ifndef _ZKJ_STL_PAIR_H_
#define _ZKJ_STL_PAIR_H_

namespace zkj_stl{
    
    template<class T1,class T2>
    class pair{

        typedef T1 first_type;
        typedef T2 second_type;

        T1  first;
        T2  second;

        //constructor
        pair() :first(T1()), second(T2()){};
        pair(const T1& _a, const T2& _b) :first(_a), second(_b){};


    };

    template <class T1, class T2>
    inline bool operator==(const pair<T1, T2>& _x, const pair<T1, T2>& _y)
    {
        return _x.first == _y.first && _x.second == _y.second;
    }


    template <class T1, class T2>
    inline bool operator<(const pair<T1, T2>& _x, const pair<T1, T2>& _y)
    {
        return _x.first < _y.first ||
            (!(_y.first < _x.first) && _x.second < _y.second);
    }

    template <class T1, class T2>
    inline bool operator!=(const pair<T1, _2>& _x, const pair<T1, T2>& _y) {
        return !(_x == _y);
    }

    template <class T1, class T2>
    inline bool operator>(const pair<T1, T2>& _x, const pair<T1, T2>& _y) {
        return _y < _x;
    }

    template <class T1, class T2>
    inline bool operator<=(const pair<T1, T2>& _x, const pair<T1, T2>& _y) {
        return !(_y < _x);
    }

    template <class T1, class T2>
    inline bool operator>=(const pair<T1, T2>& _x, const pair<T1, T2>& _y) {
        return !(_x < _y);
    }


    template <class T1, class T2>
    inline pair<T1, T2> make_pair(const T1& _x, const T2& _y)
    {
        return pair<T1, T2>(_x, _y);
    }

}//namespace zkj_stl;

//mode:c++

#endif