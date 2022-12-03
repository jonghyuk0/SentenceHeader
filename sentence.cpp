#include "sentence.h"
#include <iostream>


sentence::sentence() : contents(nullptr), sen_length(0), memory_capacity(0) {}
sentence::sentence(const char chr) : sen_length(1), memory_capacity(1) {
    this->contents = new char[1];
    this->contents[0] = chr;
}
sentence::sentence(const char *str) {
    int str_len = get_len(str);
    this->sen_length = str_len;
    this->contents = new char[this->sen_length];
    memory_capacity = this->sen_length;
    for (int i = 0; i < this->sen_length; i++) {
        this->contents[i] = str[i];
    }
}
sentence::sentence(const sentence &sen) {
    this->sen_length = sen.length();
    this->contents = new char[this->sen_length];
    this->memory_capacity = this->sen_length;
    for (int i = 0; i < this->sen_length; i++) {
        this->contents[i] = sen[i];
    }
}
sentence::sentence(sentence &&sen) noexcept {
    delete[] this->contents;
    this->sen_length = sen.length();
    this->contents = sen.contents;
    this->memory_capacity = sen.memory_capacity;

    sen.contents = nullptr;
}

sentence::~sentence() {delete[] this->contents;}


int sentence::get_len(const char *str) {
    int str_len = 0;
    for (; str[str_len] != '\0'; str_len++) {}
    return str_len;
}


[[nodiscard]] unsigned int sentence::length() const {
    return this->sen_length;
}

[[nodiscard]] unsigned int sentence::get_capacity() const {
    return this->memory_capacity;
}

void sentence::reserve(const int size, bool remember = true) {
    if (this->memory_capacity < size) {
        char *prev_sentence_content = this->contents;

        this->contents = new char[size];
        this->memory_capacity = size;

        for (int i = 0; i < this->sen_length; i++) {
            this->contents[i] = prev_sentence_content[i];
        }

        delete[] prev_sentence_content;
    }
}

sentence sentence::sub_sen(int begin, int end) {
    if (end == -1) end = this->sen_length;
    if(begin < 0 || this->sen_length <= end)
        throw std::out_of_range("Out of Range");
    if(end < begin)
        throw std::out_of_range("begin cannot be bigger than end");
    sentence sen;
    for (int i = begin; i < end; i++) {
        sen += this->contents[i];
    }
    return sen;
}

char &sentence::operator[](const int idx) const noexcept(false) {
    if(idx < 0 || this->sen_length <= idx)
        throw std::out_of_range("index " + std::to_string(idx) + " is OutOfRange");
    return this->contents[idx];
}

sentence &sentence::operator=(const char chr) {
    if (this->memory_capacity == 0) {
        this->contents = new char[1];
        this->memory_capacity = 1;
    }

    this->contents[0] = chr;
    this->sen_length = 1;
    return *this;
}
sentence &sentence::operator=(const char *s) {
    int sen_len = get_len(s);
    if (this->memory_capacity < sen_len) {
        delete[] this->contents;
        this->contents = new char[sen_len];
        this->memory_capacity = sen_len;
    }
    this->sen_length = sen_len;
    for (int i = 0; i < this->sen_length; i++) {
        this->contents[i] = s[i];
    }
    return *this;
}
sentence &sentence::operator=(const sentence &sen) {
    if (this->memory_capacity < sen.length()) {
        delete[] this->contents;
        this->contents = new char[sen.length()];
        this->memory_capacity = sen.length();
    }
    this->sen_length = sen.length();
    for (int i = 0; i < this->sen_length; i++)
        this->contents[i] = sen[i];

    return *this;
}
sentence &sentence::operator=(sentence &&sen) noexcept {
    delete[] this->contents;
    this->sen_length = sen.length();
    this->contents = sen.contents;
    this->memory_capacity = sen.memory_capacity;

    sen.contents = nullptr;
    return *this;
}

sentence &sentence::operator+=(const char chr) {
    if (this->memory_capacity < this->sen_length + 1)
        this->reserve(this->sen_length * 2);
    this->contents[sen_length] = chr;
    this->sen_length++;
    return *this;
}
sentence &sentence::operator+=(const char *str) {
    int str_len = get_len(str);
    if (this->memory_capacity < this->sen_length + str_len) {
        int mem = memory_capacity;
        while (this->sen_length + str_len > mem)
            mem *= 2;
        this->reserve(mem);
    }
    for (int i = 0; i < str_len; i++)
        this->contents[this->sen_length + i] = str[i];
    this->sen_length += str_len;
    return *this;
}
sentence &sentence::operator+=(const sentence &sen) {
    if (this->memory_capacity < this->sen_length + sen.length()) {
        int mem = memory_capacity;
        while (this->sen_length + sen.length() > mem)
            mem *= 2;
        this->reserve(mem);
    }
    for (int i = 0; i < sen.length(); i++)
        this->contents[this->sen_length + i] = sen[i];
    this->sen_length += sen.length();
    return *this;
}
sentence &sentence::operator+=(const sentence &&sen) {
    if (this->memory_capacity < this->sen_length + sen.length()) {
        int mem = memory_capacity;
        while (this->sen_length + sen.length() > mem)
            mem *= 2;
        this->reserve(mem);
    }
    for (int i = 0; i < sen.length(); i++)
        contents[this->sen_length + i] = sen[i];
    this->sen_length += sen.length();
    return *this;
}

sentence sentence::operator+(const char chr){
    sentence sen(*this);
    sen += chr;
    return sen;
}
sentence sentence::operator+(const char *str) {
    sentence sen(*this);
    sen += str;
    return sen;
}
sentence sentence::operator+(const sentence &sen1) {
    sentence sen(*this);
    sen += sen1;
    return sen;
}

std::ostream &operator<<(std::ostream &OutputStream, const sentence &sen) {
    for(int i = 0; i < sen.length(); i++)
        std::cout << sen.contents[i];
    return OutputStream;
}
std::ostream &operator<<(std::ostream &OutputStream, const sentence &&sen) {
    for(int i = 0; i < sen.length(); i++)
        std::cout << sen.contents[i];
    return OutputStream;
}