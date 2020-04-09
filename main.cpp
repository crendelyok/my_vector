#include <iostream>
#include "vector.h"
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
    b = a;
    b.dump();
    a.dump();
    return 0;
}