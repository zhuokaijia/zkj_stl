#ifndef _ZKJ_STL_STACK_H_
#define _ZKJ_STL_STACK_H_



namespace zkj_stl{

 
    //forward-declared
    template<class T, class Alloc, size_t buffer_size>
    class deque;

    //forward-declared
    template<class T, class Alloc>
    class list;

    //by default,sequence = deque<T>
    //sequeence = list<T> is also available
    template<class T,class sequence=deque<T> >
    class stack{
    protected:
        typedef typename sequence::value_type       value_type;
        typedef typename sequence::reference        reference;
        typedef typename sequence::const_reference  connst_reference;

        sequence c;

    public:
        bool empty()const{ return c.empty(); }
        size_t size()const{ return c.size(); }
        reference top(){ return c.back(); }
        const_reference top()const{ return c.back(); }
        void pop(){ c.pop_back(); }
        void push(const_reference _value){ c.push_back(_value); }
    };

}//namespace zkj_stl

//mode:c++

#endif