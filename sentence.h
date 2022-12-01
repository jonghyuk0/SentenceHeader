#ifndef REVI_SENTENCE_H
#define REVI_SENTENCE_H
#include <iostream>

class sentence {
private:
    char *contents = nullptr;
    unsigned int sen_length;
    unsigned int memory_capacity;

    //char* 길이 구하는 함수
    static int get_len(const char *str) {
        int str_len = 0;
        for (; str[str_len] != '\0'; str_len++) {}
        return str_len;
    }

public:

    ///기본 생성자
    sentence() : contents(nullptr), sen_length(0), memory_capacity(0) {}

    ///문자로 생성
    sentence(const char chr) : sen_length(1), memory_capacity(1) {
        this->contents = new char[1];
        this->contents[0] = chr;
    }

    ///문자열로 생성
    sentence(const char *str) {
        int str_len = get_len(str);
        this->sen_length = str_len;
        this->contents = new char[this->sen_length];
        memory_capacity = this->sen_length;
        for (int i = 0; i < this->sen_length; i++) {
            this->contents[i] = str[i];
        }
    }

    ///복사 생성자
    sentence(const sentence &sen) {
        this->sen_length = sen.length();
        this->contents = new char[this->sen_length];
        this->memory_capacity = this->sen_length;
        for (int i = 0; i < this->sen_length; i++) {
            this->contents[i] = sen[i];
        }
    }

    ///이동 생성자
    sentence(sentence &&sen) noexcept {
        delete[] this->contents;
        this->sen_length = sen.length();
        this->contents = sen.contents;
        this->memory_capacity = sen.memory_capacity;

        sen.contents = nullptr;
    }

    ///소멸자
    ~sentence() {
        delete[] this->contents;
    }

    //길이
    [[nodiscard]] int length() const {
        return this->sen_length;
    }


    //메모리 할당
    void reserve(const int size, bool remember = true) {
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

    //메모리 크기 반환
    [[nodiscard]] int get_capacity() const {
        return this->memory_capacity;
    }

    //문자열 자르기
    sentence sub_sen(int begin, int end = -1) {
        if (end == -1) end = this->sen_length;
        sentence sen;
        for (int i = begin; i < end; i++) {
            sen += this->contents[i];
        }
        return sen;
    }

    //접근자
    char &operator[](const int idx) const {
        return this->contents[idx];
    }

    //문자 복사 대입
    sentence &operator=(const char chr) {
        if (this->memory_capacity == 0) {
            this->contents = new char[1];
            this->memory_capacity = 1;
        }

        this->contents[0] = chr;
        this->sen_length = 1;
        return *this;
    }

    //문자열 복사 대입
    sentence &operator=(const char *s) {
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

    //복사 대입
    sentence &operator=(const sentence &sen) {
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

    //우측값 이동 대입
    sentence &operator=(sentence &&sen) noexcept {
        delete[] this->contents;
        this->sen_length = sen.length();
        this->contents = sen.contents;
        this->memory_capacity = sen.memory_capacity;

        sen.contents = nullptr;
        return *this;
    }

    //문자 추가
    sentence &operator+=(const char chr) {
        if (this->memory_capacity < this->sen_length + 1)
            this->reserve(this->sen_length * 2);
        this->contents[sen_length] = chr;
        this->sen_length++;
        return *this;
    }

    //문자열 추가
    sentence &operator+=(const char *str) {
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


    sentence &operator+=(const sentence &sen) {
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


    sentence &operator+=(const sentence &&sen) {
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
    ///연산자

    friend std::ostream &operator<<(std::ostream&, const sentence&);
    friend std::ostream &operator<<(std::ostream&, const sentence&&);
};


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


sentence operator+(const sentence &sentence1, const char chr) {
    sentence sen(sentence1);
    sen += chr;
    return sen;
}

sentence operator+(const sentence &sentence1, const char *str) {
    sentence sen(sentence1);
    sen += str;
    return sen;
}

sentence operator+(const sentence &sen1, const sentence &sen2) {
    sentence sen(sen1);
    sen += sen2;
    return sen;
}

sentence operator+(const sentence &&sen1, const char chr) {
    sentence sen(sen1);
    sen += chr;
    return sen;
}

sentence operator+(const sentence &&sen1, const char *str) {
    sentence sen(sen1);
    sen += str;
    return sen;
}

sentence operator+(const sentence &&sen1, const sentence &sen2) {
    sentence sen(sen1);
    sen += sen2;
    return sen;
}

#endif //REVI_SENTENCE_H
