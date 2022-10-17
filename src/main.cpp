
#include<iostream>
#include<my_temp.h>
#include<utility>

using namespace std;

int main () {
    print();
    std::pair<int, int> p {1,2};
    auto [r1, r2] = p;
    cout<<r1<<","<<r2<<endl;
    return 0;
}
