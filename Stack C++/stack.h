#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#ifdef _DEBUG
#include <iostream>
#endif

typedef unsigned int t_size;

class Error {};
class Overflow:Error {};
class Empty:Error {};

template <typename T>
class tStack
{
    t_size _allocated;
    t_size _top;
    T *_data;
    public:
        tStack (t_size size = 1000)
        {
            _data = new T[size];
            if (!_data)
                throw Overflow();
            _allocated = size;
            _top = 0;
        }

        ~tStack ()
        {
            delete[] _data;
        }

        void push (T value)
        {
            if (_top == _allocated)
                throw Overflow();
            _data[_top] = value;
            _top++;
        }

        T pop ()
        {
            if (isEmpty())
                throw Empty();
            _top--;
            return _data[_top];
        }
        bool isEmpty ()
        {
            return _top == 0;
        }
#ifdef _DEBUG
        void debugPrint()
        {
            for(int i = 0; i < _top; i++)
                std::cerr << _data[i] << '\t';
            std::cerr << '\n';
        }
#endif
};

#endif // STACK_H_INCLUDED
