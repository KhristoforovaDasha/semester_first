#include "tests.h"
#include <string>
bool push_back(char c, String& str){
    size_t len = str.length();
     str.push_back(c);
     return  str[len] == c && len + 1 == str.length();

}
bool find(const String& str,const String& other,const std::string& tmp,const std::string other_tmp){
    size_t pos1 = str.find(other);
    size_t pos2 = tmp.find(other_tmp);
    return pos1 == pos2;
}

bool rfind(const String& str,const String& other,const std::string& tmp,const std::string other_tmp){
    size_t pos1 = str.rfind(other);
    size_t pos2 = tmp.rfind(other_tmp);
    return pos1 == pos2;
}
bool pop_back(String& str){
      size_t len = str.length();
      str.pop_back();
      return len - 1 == str.length();
}
bool add(String& str,const String& other){
    size_t len = str.length();
    str += other;
    for(size_t i = len; i < str.length(); ++i) 
        if(str[i] != other[i - len]) return 0;
    return len + other.length() == str.length();
}
bool runAllTests(){
    String str = "abacaba";
    String other = "aba";
    std:: string tmp(' ',str.length());
    std:: string other_tmp(' ',other.length());
    for(size_t i = 0; i < str.length(); ++i) tmp[i] = str[i];
    for(size_t i = 0; i < other.length(); ++i) other_tmp[i] = other[i];
    if(!push_back('a',str)) return 0;
    if(!find(str,other,tmp,other_tmp)) return 0;
    if(!rfind(str,other,tmp,other_tmp)) return 0;
    if(!pop_back(str)) return 0;
    if(!add(str,other)) return 0;
    return 1;

}
