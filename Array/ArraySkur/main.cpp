#include <iostream>

using namespace std;

template<typename T>
class Array{
    int _size;
    T *_A;

    Array(const Array<T> &noname) {} //forbidden to call!
public:
    Array(int fixedSize):_size(fixedSize)
    {
        _A = new T[fixedSize];
    }
    ~Array()
    {
        delete[] _A;
    }
    T& operator [](int i)
    {
        return _A[i];
    }
    const T& operator [](int i) const
    {
        return _A[i];
    }
    int size() const
    {
        return _size;
    }
    Array<T> operator+(const Array<T> &other)
    {
        Array<T> result(_size + other._size);
        for(int i = 0; i < _size; i++)
        {
            result._A[i] = _A[i];
        }
        int i = _size;
        for(int j = 0; j < other._size; j++, i++)
        {
            result._A[i] = other._A[j];
        }
        return result;
    }
    const Array<T>& operator=(const Array<T> &other)
    {
        delete[] _A;
        _size = other._size;
        _A = new T[_size];
        for(int i = 0; i < _size; i++)
        {
            _A[i] = other._A[i];
        }
        return *this;
    }
};

template<typename T>
ostream & operator << (ostream &out, const Array<T> &M)
{
    for(int i = 0; i < M.size(); i++)
    {
        out << M[i] << '\t';
    }
    return out;
}

int main()
{
    cout << "Hello Array!" << endl;
    Array<double> M(5), H(5), U(1);

    for(int i = 0; i < M.size(); i++)
    {
        M[i] = i + 1;
    }
    for(int i = 0; i < M.size(); i++)
    {
        H[i] = M[M.size() - i - 1];
    }

    U = M + H;
    cout << M << endl;
    cout << H << endl;
    cout << U << endl;


    return 0;
}
