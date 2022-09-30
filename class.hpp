#ifndef ALIEXPRESS_H
#define ALIEXPRESS_H
#include <iostream>
#include <string>
#include <map>
#include <fstream>

class CPU_AliExpress {
public:
    CPU_AliExpress();
    ~CPU_AliExpress() = default;
    void get(std::string);
    void print();

private:
    std::map<std::string, int*> regs;
    std::map<std::string, void(CPU_AliExpress::*)(std::string&, std::string&)> func;
    std::map<std::string, int> label;
    std::map<std::string, bool> jumps;
    std::ifstream file;
    int r1 = 0;
    int r2 = 0;
    int r3 = 0;
    int r4 = 0;
    int r5 = 0;
    int r6 = 0;
    int r7 = 0;
    int r8 = 0;
    int r9 = 0;
    int r10 = 0;

private:
    void make();
    void get_labels(std::string&);
    bool is_number(std::string&);
    bool check_reg(std::string&);
    void split(std::string);
    void mov(std::string&, std::string&);
    void add(std::string&, std::string&);
    void jmp(std::string&, std::string&);
    void cmp(std::string&, std::string&);
    void sub(std::string&, std::string&);
    void div(std::string&, std::string&);
    void mul(std::string&, std::string&);
    void _and(std::string&, std::string&);
    void _or(std::string&, std::string&);
    void _xor(std::string&, std::string&);
    void _not(std::string&, std::string&);
    void jl(std::string&, std::string&);
    void je(std::string&, std::string&);
    void jle(std::string&, std::string&);
    void jg(std::string&, std::string&);
    void jge(std::string&, std::string&);
    void jne(std::string&, std::string&);
    void jz(std::string&, std::string&);
};

#endif // ALIEXPRESSU_H
