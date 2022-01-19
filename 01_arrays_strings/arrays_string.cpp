#include <iostream>
#include <array>
#include <sstream>

#include "arrays_string.h"

std::string bool_as_text(bool b)
{
    std::stringstream converter;
    converter << std::boolalpha << b;
    return converter.str();
}

void run_arrays_string() {
    std::cout << "Hello, Arrays and Strings!\n";
    
    // 1.1
    std::string a("abcdef");
    std::string b("abcdeff");
    std::cout << "is unique" << std::endl;
    std::cout << "is unique: true is " + bool_as_text(is_unique(a)) << std::endl;
    std::cout << "is unique: false is " + bool_as_text(is_unique(b)) << std::endl;
    
    // 1.2
    std::cout << "is permutation" << std::endl;
    std::cout << "is permutation: false is " + bool_as_text(is_permutation(a, b)) << std::endl;
    std::cout << "is permutation: true is " + bool_as_text(is_permutation(a, a)) << std::endl;
    
    std::string c("fedcba");
    std::cout << "is permutation: true is " + bool_as_text(is_permutation(a, c)) << std::endl;
    
    std::string d("");
    std::cout << "is permutation: false is " + bool_as_text(is_permutation(a, d)) << std::endl;
    
    std::string e("");
    std::cout << "is permutation: true is " + bool_as_text(is_permutation(e, e)) << std::endl;
    
    // 1.3
    std::string f("Mr John Smith    ");
    urlify(f, 13);
    std::cout << "urlify: Mr%20John%20Smith is " + f << std::endl;

}

/*1.1*/
bool is_unique(const std::string& iString){
    if(iString.size() == 0) return true;
    if(iString.size() > 128) return false;
    
    std::array<bool, 128> chars = {false};
    
    for(const char& c : iString){
        if(chars[c - 'a'] == true){
            return false;
        }
        chars[c - 'a'] = true;
    }
    return true;
}

void loop_and_count(const std::string& iTarget, std::array<uint32_t, 128>& counter){
    for(const char& c : iTarget) {
        counter[c - 'a']++;
    }
    return;
}

/*1.2*/
bool is_permutation(const std::string& iFirst, const std::string& iSecond){
    // not case sensitive | no whitespaces
    // Alternative could be to sort the strings and compare (nlogn)
    // Could be solved using only one counter: incremente for first and decrement for second
    if(iFirst.size() != iSecond.size()) return false;
    
    std::array<uint32_t, 128> firstCounter = {0};
    std::array<uint32_t, 128> secondCounter = {0};
    
    loop_and_count(iFirst, firstCounter);
    loop_and_count(iSecond, secondCounter);
    
    for(int i = 0; i < 128; ++i){
        if(firstCounter[i] != secondCounter[i]){
            return false;
        }
    }
    
    return true;
}

/*1.3*/
void urlify(std::string& iString, const uint32_t& realLength) {
    uint32_t spaces(0);
    //counting the spaces
    for(uint32_t i = 0; i < realLength; ++i) {
        if(iString[i] == ' ') {
            spaces++;
        }
    }
    
    uint32_t counter(realLength + spaces * 2);
    counter--; //end of the string
    
    for(int32_t i = realLength - 1; i >= 0; --i){
        if(iString[i] == ' '){
            iString[counter] = '0';
            iString[counter - 1] = '2';
            iString[counter - 2] = '%';
            counter -= 3;
        } else {
            iString[counter] = iString[i];
            counter--;
        }
    }
}
