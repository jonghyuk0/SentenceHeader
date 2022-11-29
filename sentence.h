#ifndef REVI_SENTENCE_H
#define REVI_SENTENCE_H
#include <iostream>

class sentence {
private:
    char *sentence_contents = nullptr;
    int sentence_length;
    int memory_capacity;

public:
    ///생성자들
    //기본 생성자
    explicit sentence() : sentence_contents(nullptr), sentence_length(0), memory_capacity(0) {}

    //문자로 부터 생성
    explicit sentence(const char chr) : sentence_length(1), memory_capacity(1) {
        this->sentence_contents = new char[1];
        this->sentence_contents[0] = chr;
    }

    //문자열로부터 생성
    explicit sentence(const char *sen) : sentence_length(senlen(sen)), memory_capacity(senlen(sen)) {
        int slen = senlen(sen);
        this->sentence_length = slen;
        this->sentence_contents = new char[sentence_length];
        for (int i = 0; i < sentence_length; i++) {
            sentence_contents[i] = sen[i];
        }
    }

    //복사 생성자
    explicit sentence(const sentence &sen) {
        sentence_length = sen.length();
        sentence_contents = new char[sentence_length];
        memory_capacity = sentence_length;
        for (int i = 0; i < sentence_length; i++) {
            sentence_contents[i] = sen[i];
        }
    }

    //이동 생성자
    sentence(sentence &&sen) {
        this->sentence_length = sen.sentence_length;
        this->sentence_contents = sen.sentence_contents;
        this->memory_capacity = sen.memory_capacity;

        sen.sentence_contents = nullptr;
    }
    ///생성자들

    ///소멸자
    ~sentence() {
        if (this->sentence_contents != nullptr) delete[] this->sentence_contents;
    }
    ///소멸자

    /// 함수들
    //char* 길이 구하는 함수
    static int senlen(const char *sen) {
        int senlen = 0;
        for (; sen[senlen] != '\0'; senlen++) {}
        return senlen;
    }

    //길이
    int length() const {
        return this->sentence_length;
    }


    //메모리 할당
    void reserve(const int size, bool remember = true) {
        if (size > this->memory_capacity) {
            char *prev_sentence_content = this->sentence_contents;

            this->sentence_contents = new char[size];
            this->memory_capacity = size;

            for (int i = 0; i < this->sentence_length; i++) {
                this->sentence_contents[i] = prev_sentence_content[i];
            }

            if (prev_sentence_content != nullptr) delete[] prev_sentence_content;
        }
    }

    int capacity() {
        return this->memory_capacity;
    }

    void print() const {
        for (int i = 0; i < this->sentence_length; i++) {
            std::cout << this->sentence_contents[i];
        }
    }

    sentence sub_sen(int begin, int end = -1) {
        if (end == -1) end = this->sentence_length;
        sentence sen;
        for (int i = begin; i < end; i++) {
            sen += this->sentence_contents[i];
        }
        return sen;
    }
    ///함수들

    ///연산자들
    //접근자
    char &operator[](const int idx) const {
        return this->sentence_contents[idx];
    }

    //문자 복사 대입
    sentence &operator=(const char chr) {
        if (this->memory_capacity == 0) {
            this->sentence_contents = new char[1];
            this->memory_capacity = 1;
        }

        this->sentence_contents[0] = chr;
        this->sentence_length = 1;
        return *this;
    }

    //문자열 복사 대입
    sentence &operator=(const char *s) {
        int sen_len = senlen(s);
        if (this->memory_capacity < sen_len) {
            delete[] this->sentence_contents;
            this->sentence_contents = new char[sen_len];
            this->memory_capacity = sen_len;
        }
        this->sentence_length = sen_len;
        for (int i = 0; i < this->sentence_length; i++) {
            this->sentence_contents[i] = s[i];
        }
        return *this;
    }

    //복사 대입
    sentence &operator=(const sentence &sen) {
        if (this->memory_capacity < sen.length()) {
            delete[] this->sentence_contents;
            this->sentence_contents = new char[sen.length()];
            this->memory_capacity = sen.length();
        }
        this->sentence_length = sen.length();
        for (int i = 0; i < this->sentence_length; i++)
            this->sentence_contents[i] = sen[i];

        return *this;
    }

    //우측값 이동 대입
    sentence &operator=(sentence &&sen) {
        this->sentence_length = sen.sentence_length;
        this->sentence_contents = sen.sentence_contents;
        this->memory_capacity = sen.memory_capacity;

        sen.sentence_contents = nullptr;
        return *this;
    }

    //문자 추가
    sentence &operator+=(const char chr) {
        if (this->sentence_length + 1 > this->memory_capacity)
            this->reserve(this->sentence_length * 2);
        this->sentence_contents[sentence_length] = chr;
        this->sentence_length++;
        return *this;
    }

    //문자열 추가
    sentence &operator+=(const char *s) {
        int sen_len = senlen(s);
        if (this->sentence_length + sen_len > this->memory_capacity) {
            int mem = memory_capacity;
            while (this->sentence_length + sen_len > mem)
                mem *= 2;
            this->reserve(mem);
        }
        for (int i = 0; i < sen_len; i++)
            this->sentence_contents[this->sentence_length + i] = s[i];
        this->sentence_length += sen_len;
        return *this;
    }


    sentence &operator+=(const sentence &s) {
        if (this->sentence_length + s.length() > this->memory_capacity) {
            int mem = memory_capacity;
            while (this->sentence_length + s.length() > mem)
                mem *= 2;
            this->reserve(mem);
        }
        for (int i = 0; i < s.length(); i++)
            this->sentence_contents[this->sentence_length + i] = s[i];
        this->sentence_length += s.length();
        return *this;
    }


    sentence &operator+=(const sentence &&s) {
        if (this->sentence_length + s.length() > this->memory_capacity) {
            int mem = memory_capacity;
            while (this->sentence_length + s.length() > mem)
                mem *= 2;
            this->reserve(mem);
        }
        for (int i = 0; i < s.length(); i++)
            sentence_contents[sentence_length + i] = s[i];
        sentence_length += s.length();
        return *this;
    }
    ///연산자들
};

///출력
std::ostream& operator<<(std::ostream& OutputStream, const sentence& sen){
    sen.print();
    return OutputStream;
}

std::ostream& operator<<(std::ostream& OutputStream, const sentence&& sen){
    sen.print();
    return OutputStream;
}
    ///출력

    ///덧셈
    sentence operator+(const sentence& sentence1, const char chr){
        sentence sen(sentence1);
        sen += chr;
        return sen;
    }

    sentence operator+(const sentence& sentence1, const char* str){
        sentence sen(sentence1);
        sen += str;
        return sen;
    }

    sentence operator+(const sentence& sentence1, const sentence& sentence2){
        sentence sen(sentence1);
        sen += sentence2;
        return sen;
    }

    sentence operator+(const sentence&& sentence1, const char chr){
        sentence sen(sentence1);
        sen += chr;
        return sen;
    }

    sentence operator+(const sentence&& sentence1, const char* str){
        sentence sen(sentence1);
        sen += str;
        return sen;
    }

    sentence operator+(const sentence&& sentence1, const sentence& sentence2){
        sentence sen(sentence1);
        sen += sentence2;
        return sen;
    }
    ///덧셈

#endif //REVI_SENTENCE_H
