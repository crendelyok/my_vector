#include <iostream>
#include "vector.hpp"
using namespace std;
int main(int argc, char*argv[]) {
    cout << argv[0] << endl;
    Vector a(2);
    Vector b;
    a.push_back(1);
    a.push_back(2);
    a.push_back(2);
    a.push_back(2);
    a.push_back(2);
    a.push_back(2);
    cout << a[3] << endl;
    cout << a.at(3) << endl;

    b = a;
    Vector c;
    c = a + b;
    c.dump();
    b.dump();
    int x = a.pop();
    a.dump();
    return 0;
}
