//
// Created by Admin on 09.11.2021.
//

#ifndef UNTITLED5_STRING_H
#define UNTITLED5_STRING_H

#include <iostream>
#include <cstring>


char *myRealloc(char *ptr, size_t count) {
    char *newPtr = new char[count];
    memcpy(newPtr, ptr, std::min(strlen(ptr), count) );
    delete[] ptr;
    return newPtr;
}

class String {
public:
    String(const char *str) {
        size_t len = strlen(str);
        if (len == 0) {
            string = new char[1]();
        } else {
            string = new char[len + 1];
            memcpy(string, str, len + 1);
            size = len;
            capacity = len + 1;
        }
    }

    String(size_t num, char ch) {
        if (num == 0) {
            string = new char[1]();
        } else {
            string = new char[num + 1];
            memset(string, ch, num);
            string[num] = '\0';
            size = num;
            capacity = num + 1;
        }
    }

    String() {
        string = new char[1]();
    }

    String(const String &copy) {
        size_t len = copy.size;
        string = new char[len + 1];
        memcpy(string, copy.string, len + 1);
        size = len;
        capacity = len + 1;
    }

    String &operator=(const String& other) {
        if(this != &other) {
            size_t len = other.size;
            delete[] string;
            string = new char[len + 1];
            memcpy(string, other.string, len + 1);
            size = len;
            capacity = len + 1;
        }
        return *this;
    }

    char &operator[](size_t index) { return string[index]; }

    const char &operator[](size_t index) const { return string[index]; }

    size_t length() const {
        return size;
    }

    void push_back(char ch) {
        if (size + 1 == capacity) {
            capacity *= 2;
            string = myRealloc(string, capacity);
        }
        string[size++] = ch;
        string[size] = '\0';
    }

    void pop_back() {
        if (size * 4 + 1 <= capacity) {
            capacity /= 2;
            if(capacity == 0) capacity = 1;
            string = myRealloc(string, capacity);
        }
        string[--size] = '\0';
    }

    char &front() { return string[0]; }

    const char &front() const { return string[0]; }

    char &back() { return string[size - 1]; }

    const char &back() const { return string[size - 1]; }

    String& operator+=(const String &other) {
        size_t len = size + other.size;
        capacity = len + 1;
        string = myRealloc(string, capacity);
        memcpy(string + size * sizeof(char), other.string, other.size + 1);
        size = len;
        string[size] = '\0';
        return *this;
    }

    String &operator+=(char ch) {
        push_back(ch);
        return *this;
    }

    String operator+(char ch) {
        String result(string);
        result.push_back(ch);
        return result;
    }

    size_t find(const String &substring) const {
        char *cur = strstr(string, substring.string);
        if (cur == nullptr) return size;
        return size - strlen(cur);
    }

    size_t rfind(const String &substring) const {
        size_t result = size;
        for (size_t i = 0; i <= size; ++i) {
            char *cur = strstr(string + i * sizeof(char), substring.string);
            if (cur != nullptr) result = size - strlen(cur);
        }
        return result;
    }

    String substr(size_t start, size_t count) const {
        size_t len = std::min(count, size - start);
        char *tmp = new char[len + 1];
        memcpy(tmp, string + start * sizeof(char), len);
        tmp[len] = '\0';
        String str(tmp);
        delete[] tmp;
        return str;
    }

    bool empty() { return !size; }

    void clear() {
        delete[] string;
        size = 0;
        capacity = 1;
        string = new char[1]();
    }

    ~String() { delete[] string; }

    friend std::ostream &operator<<(std::ostream &out, const String &str);

    friend std::istream &operator>>(std::istream &in, String &str);
    friend bool operator==(const String &first,const String &second);

private:
    size_t size = 0;
    size_t capacity = 1;
    char *string = nullptr;
};

std::ostream &operator<<(std::ostream &out, const String &str) {
    out << str.string;
    return out;
}

std::istream &operator>>(std::istream &in, String &str) {
    str.clear();
    char ch;
    while (in.get(ch) && !isspace(ch) && ch != '\0') {
        str.push_back(ch);
    }
    return in;
}

String operator+(const String &first, const String &second) {
    String result;
    result += first;
    result += second;
    return result;
}

String operator+(char ch, const String &other) {
    String result(1, ch);
    result += other;
    return result;
}
bool operator==(const String &first,const String &second) {
    if (first.size != second.size) return false;
    return !(memcmp(first.string, second.string, std::min(first.size,second.size)));
}
#endif //UNTITLED5_STRING_H
