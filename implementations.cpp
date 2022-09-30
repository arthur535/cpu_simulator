#include "class.hpp"

CPU_AliExpress::CPU_AliExpress() {
    make();
}
int my_atoi(std::string& str) {
    int i = 0;
    int result = 0;
    while( str[i] != '\0') {
        result *= 10;
        result += str[i] - 48;
        ++i;
    }
    return result;
}
void CPU_AliExpress::get(std::string name) {
    std::string line;
    get_labels(name);
    this->file.open(name);
    if (file.is_open()) {
        while (std::getline(file, line)) {
            this->split(line);
        }
    } else {
        perror("File is not open !!!");
        exit(1);
    }
    file.close();
}

void CPU_AliExpress::get_labels(std::string& name) {
    std::string line;
    this->file.open(name);
    if (this->file.is_open()) {
        while (!(this->file.eof())) {
            std::getline(this->file, line);
            if (line.find(':') != -1) {
                line.erase(line.begin() + line.find(':'));
                this->label[line] = this->file.tellg();
            }
        }
    }
    this->file.close();
}

void CPU_AliExpress::split(std::string rhs) {
    std::string oper = "";
    std::string reg = "";
    std::string src = "";
    if (rhs.find(':') != -1) {
        return;
    }
    if (rhs.find(',') != -1) {
        rhs.erase(rhs.begin() + rhs.find(','));
    }
    int space = 0;
    for (int i = 0; i < rhs.size(); ++i) {
        if (rhs[i] == ' ') {
            ++space;
        }
    }
    if (space == 1) {
        for (int i = 0; i < rhs.size(); ++i) {
            if (rhs[i] == ' ') {
                oper += rhs.substr(0, i);
                rhs.erase(rhs.begin(), rhs.begin() + i + 1);
            }
        }
        reg += rhs;
    }
    if (2 == space) {
        for (int i = 0; i < rhs.size(); ++i) {
            if (rhs[i] == ' ') {
                oper += rhs.substr(0, i);
                rhs.erase(rhs.begin(), rhs.begin() + i + 1);
                reg += rhs.substr(0, rhs.find(' '));
                rhs.erase(rhs.begin(), rhs.begin() + rhs.find(' ') + 1);
            }
        }
        src += rhs;
    }
    (this->*func[oper])(reg, src);
}

void CPU_AliExpress::make() {
    regs["r1"] = &r1;
    regs["r2"] = &r2;
    regs["r3"] = &r3;
    regs["r4"] = &r4;
    regs["r5"] = &r5;
    regs["r6"] = &r6;
    regs["r7"] = &r7;
    regs["r8"] = &r8;
    regs["r9"] = &r9;
    regs["r10"] = &r10;
    
    jumps["je"] = false;
    jumps["jne"] = false;
    jumps["jl"] = false;
    jumps["jle"] = false;
    jumps["jg"] = false;
    jumps["jge"] = false;
    jumps["jz"] = false;
    jumps["jnz"] = false;

    func["mov"] = &CPU_AliExpress::mov;
    func["add"] = &CPU_AliExpress::add;
    func["cmp"] = &CPU_AliExpress::cmp;
    func["sub"] = &CPU_AliExpress::sub;
    func["div"] = &CPU_AliExpress::div;
    func["mul"] = &CPU_AliExpress::mul;
    func["and"] = &CPU_AliExpress::_and;
    func["or" ] = &CPU_AliExpress::_or;
    func["xor"] = &CPU_AliExpress::_xor;
    func["not"] = &CPU_AliExpress::_not;
    func["jmp"] = &CPU_AliExpress::jmp;
    func["jz" ] = &CPU_AliExpress::jz;
    func["jg" ] = &CPU_AliExpress::jg;
    func["jge"] = &CPU_AliExpress::jge;
    func["jl" ] = &CPU_AliExpress::jl;
    func["jle"] = &CPU_AliExpress::jle;
    func["jne"] = &CPU_AliExpress::jne;
}

bool CPU_AliExpress::check_reg(std::string& src) {
    for (int i = 0; i < regs.size(); ++i) {
        if ((regs.find(src)) == (regs.end())) {
            return false;
        }
    }
    return true;
}

bool CPU_AliExpress::is_number(std::string& src) {
    bool flag = true;
    for (int i = 0; i < src.length(); ++i) {
        if (src[i] >= '0' && src[i] <= '9') {
            flag = true;
        } else {
            flag = false;
            break;
        }
    }
    return flag;
}

void CPU_AliExpress::mov(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) = my_atoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) = *(regs[src]);
        }
    } else {
        perror("register is not found");
        exit(1);
    }
    // std::cout << "r1" << " " << r1 << std::endl;
    //std::cout << "r2" << " " << r2 << std::endl;
}

void CPU_AliExpress::add(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) += my_atoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) += *(regs[src]);
        }
    } else {
        perror("register is not found");
        exit(1);
    }
    // std::cout << "r1" << " " << r1 << std::endl;
    //std::cout << "r2" << " " << r2 << std::endl;

}

void CPU_AliExpress::sub(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) -= my_atoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) -= *(regs[src]);
        }
    } else {
        perror("register is not found");
        exit(1);
    }
    // std::cout << "r1" << " " << r1 << std::endl;
    // std::cout << "r2" << " " << r2 << std::endl;
}

void CPU_AliExpress::div(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) /= my_atoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) /= *(regs[src]);
        }
    } else {
        perror("register is not found");
        exit(1);
    }
}

void CPU_AliExpress::mul(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) *= my_atoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) *= *(regs[src]);
        }
    } else {
        perror("register is not found");
        exit(1);
    }
}

void CPU_AliExpress::_and(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) &= my_atoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) &= *(regs[src]);
        }
    } else {
        perror("register is not found");
        exit(1);
    }
    // std::cout << "r1" << " " << r1 << std::endl;
    // std::cout << "r2" << " " << r2 << std::endl;
}

void CPU_AliExpress::_or(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) |= my_atoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) |= *(regs[src]);
        }
    } else {
        perror("register is not found");
        exit(1);
    }
    // std::cout << "r1" << " " << r1 << std::endl;
    // std::cout << "r2" << " " << r2 << std::endl;
}

void CPU_AliExpress::_xor(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src)) {
            *(regs[dest]) ^= my_atoi(src);
        }
        if (check_reg(src)) {
            *(regs[dest]) ^= *(regs[src]);
        }
    } else {
        perror("register is not found");
        exit(1);
    }
    // std::cout << "r1" << " " << r1 << std::endl;
    // std::cout << "r2" << " " << r2 << std::endl;
}

void CPU_AliExpress::_not(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
            *(regs[dest]) = ~(my_atoi(dest));
    } else {
        perror("register is not found");
        exit(1);
    }
}

void CPU_AliExpress::cmp(std::string& dest, std::string& src) {
    if (check_reg(dest)) {
        if (is_number(src) && src != "0") {
            if (*(regs[dest]) == (my_atoi(src))) {
                jumps["je"] = true;
                jumps["jne"] = false;
                jumps["jl"] = false;
                jumps["jle"] = true;
                jumps["jg"] = false;
                jumps["jge"] = true;
                jumps["jz"] = false;
                return;
            }
            else if (*(regs[dest]) < (my_atoi(src))) {
                jumps["je"] = false;
                jumps["jne"] = true;
                jumps["jl"] = true;
                jumps["jle"] = true;
                jumps["jg"] = false;
                jumps["jge"] = false;
                jumps["jz"] = false;
                return;
            }
            else if (*(regs[dest]) > (my_atoi(src))) {
                jumps["je"] = false;
                jumps["jne"] = true;
                jumps["jl"] = false;
                jumps["jle"] = false;
                jumps["jg"] = true;
                jumps["jge"] = true;
                jumps["jz"] = false;
                return;
            }
        }
        else if (src == "0") {
            jumps["jz"] = true;
            return;
        }
        if (check_reg(src) && src != "0") {
            if (*(regs[dest]) == *(regs[src])) {
                jumps["je"] = true;
                jumps["jne"] = false;
                jumps["jl"] = false;
                jumps["jle"] = true;
                jumps["jg"] = false;
                jumps["jge"] = true;
                jumps["jz"] = false;
                return;
            }
            else if (*(regs[dest]) < *(regs[src])) {
                jumps["je"] = false;
                jumps["jne"] = true;
                jumps["jl"] = true;
                jumps["jle"] = true;
                jumps["jg"] = false;
                jumps["jge"] = false;
                jumps["jz"] = false;
                return;
            }
            else if (*(regs[dest]) > *(regs[src])) {
                jumps["je"] = false;
                jumps["jne"] = true;
                jumps["jl"] = false;
                jumps["jle"] = false;
                jumps["jg"] = true;
                jumps["jge"] = true;
                jumps["jz"] = false;
                return;
            }
        }
        else if (*(regs[src]) == 0) {
            jumps["jz"] = true;
            return;
        }
    } else {
        perror("register is not found");
    }
}

void CPU_AliExpress::jmp(std::string& dest, std::string& src) {
    //std::cout << "R1 " << this->r1 << std::endl << "R2 " << this->r2 << std::endl;
    this->file.seekg(this->label[dest]);
}

void CPU_AliExpress::je(std::string& dest, std::string& src) {
    if (jumps["je"]) {
        this->file.seekg(this->label[dest]);
    }
}

void CPU_AliExpress::jl(std::string& dest, std::string& src) {
    if(jumps["jl"]) {
        this->file.seekg(this->label[dest]);
    }
}

void CPU_AliExpress::jle(std::string& dest, std::string& src) {
    if (jumps["jle"]) {
        this->file.seekg(this->label[dest]);
    }
}

void CPU_AliExpress::jg(std::string& dest, std::string& src) {
    if (jumps["jg"]) {
        this->file.seekg(this->label[dest]);
    }
}

void CPU_AliExpress::jge(std::string& dest, std::string& src) {
    if (jumps["jge"]) {
        this->file.seekg(this->label[dest]);
    }
}

void CPU_AliExpress::jz(std::string& dest, std::string& src) {
    if (jumps["jz"]) {
        this->file.seekg(this->label[dest]);
    }
}

void CPU_AliExpress::jne(std::string& dest, std::string& src) {
    if (jumps["jne"]) {
        this->file.seekg(this->label[dest]);
    }
}

void CPU_AliExpress::print() {
    for (auto it : regs) {
        std::cout << it.first << " " << *it.second << std::endl;
    }
}
