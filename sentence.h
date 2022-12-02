#ifndef JONGHYUK_SENTENCE_H
#define JONGHYUK_SENTENCE_H

class sentence {
private:
    char *contents = nullptr;
    unsigned int sen_length;
    unsigned int memory_capacity;

    //char* 길이 구하는 함수
    static int get_len(const char*);

public:

    ///기본 생성자
    sentence();

    ///문자로 생성
    sentence(const char);

    ///문자열로 생성
    sentence(const char*);

    ///복사 생성자
    sentence(const sentence&);

    ///이동 생성자
    sentence(sentence&&) noexcept;

    ///소멸자
    ~sentence();


    //길이
    [[nodiscard]] unsigned int length() const;
    //메모리 크기 반환
    [[nodiscard]] unsigned int get_capacity() const;

    //메모리 할당
    void reserve(const int, bool);

    //문자열 자르기
    sentence sub_sen(int, int);


    //접근자
    char &operator[](int) const noexcept(false);

    //문자 복사 대입
    sentence &operator=(char);

    //문자열 복사 대입
    sentence &operator=(const char*);

    //복사 대입
    sentence &operator=(const sentence&);

    //우측값 이동 대입
    sentence &operator=(sentence&&) noexcept;

    sentence &operator+=(const char);
    sentence &operator+=(const char*);
    sentence &operator+=(const sentence&);
    sentence &operator+=(const sentence&&);

    friend std::ostream &operator<<(std::ostream&, const sentence&);
    friend std::ostream &operator<<(std::ostream&, const sentence&&);

    sentence operator+(const char);
    sentence operator+(const char*);
    sentence operator+(const sentence&);
};

#endif //JONGHYUK_SENTENCE_H
