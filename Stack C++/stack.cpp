#include <iostream>
#include "stack.h"

using namespace std;

bool tStackTest();

int main()
{
    bool stack_testing = tStackTest();
    cout << "Testing summary: " << (stack_testing ? "OK\n" : "FAIL\n");
    return 0;
}

bool tStackTest()
{
    tStack<double> s;
    cout << "Test started.\n";
    bool empty_test_1 = true;
    empty_test_1 &= s.isEmpty();
    s.push(1);
    empty_test_1 &= !(s.isEmpty());
    bool push_test_1 = (s.pop() == 1);
    empty_test_1 &= s.isEmpty();
    cout << "Push-pop test #1: " << (push_test_1 ? "OK\n" : "Fail\n");
    cout << "Empty test #1: " << (empty_test_1 ? "OK\n" : "Fail\n");

    bool push_test_2 = true;
    bool empty_test_2 = true;
    for(int i = 0; i < 10; i++)
    {
        s.push(i*i + 5);
        empty_test_2 &= !s.isEmpty();
    }
    for(int i = 9; i >= 0; i--)
    {
        empty_test_2 &= !s.isEmpty();
        if (s.isEmpty() || s.pop() != i*i + 5)
        {
            push_test_2 = false;
            break;
        }
    }
    empty_test_2 &= s.isEmpty();
    cout << "Push-pop test #2: " << (push_test_2 ? "OK\n" : "Fail\n");
    cout << "Empty test #2: " << (empty_test_2 ? "OK\n" : "Fail\n");

    return empty_test_1 && empty_test_2 && push_test_1 && push_test_2;
}
