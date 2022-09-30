#include <iostream>
#include "/Users/arthur/Desktop/CPU/class.hpp"
int main() {
    std::string ptr = "/Users/arthur/Desktop/yyy.txt";
    CPU_AliExpress obj;
    obj.get(ptr);
    obj.print();
    return 0;
}

