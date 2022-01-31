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
    
    // 1.4
    std::string g("tact coa");
    std::cout << "is palindrome permutation: true is " + bool_as_text(is_palindrome_permutation(g)) << std::endl;
    
    std::string h("act coa");
    std::cout << "is palindrome permutation: false is " + bool_as_text(is_palindrome_permutation(h)) << std::endl;
    
    // 1.5
    std::string i("pale");
    std::string j("ple");
    std::cout << "is one edit away: true is " + bool_as_text(is_one_edit_away(i, j)) << std::endl;
    
    std::string k("bale");
    std::cout << "is one edit away: true is " + bool_as_text(is_one_edit_away(i, k)) << std::endl;
    
    std::string l("bae");
    std::cout << "is one edit away: false is " + bool_as_text(is_one_edit_away(i, l)) << std::endl;

}

/*1.1*/
bool is_unique(const std::string& iString){
    if(iString.size() == 0) return true;
    if(iString.size() > 128) return false;
    
    std::array<bool, 128> chars = {false}; //ASCII
    
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
    // Could be solved using only one counter: increment for first and decrement for second
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

/*1.4*/
bool is_palindrome_permutation(const std::string& iString){
    //Assumption: all lower case | only spaces as non-letter char
    
    if(iString.empty()) return false;
    
    std::array<bool, 128> counters = {false};
    uint32_t size(0);
    
    for(const char& c : iString){
        if(c != ' '){
            size++;
            counters[c - 'a'] = !counters[c - 'a'];
        }
    }
    
    uint32_t checks(0);
    for(int i = 0; i < counters.size(); ++i){
        if(counters[i]) {
            checks++;
        }
    }
    
    if(checks == 1 && size % 2 == 1) {
        return true;
    }
    if(checks == 0 && size % 2 == 0) {
        return true;
    }
    
    return false;
}

/*1.5*/
bool is_one_edit_replace(const std::string& iFirst, const std::string& iSecond) {
    bool differenceFound(false);
    
    for(int i = 0; i < iFirst.length(); ++i) {
        if(iFirst[i] != iSecond[i]) {
            if(differenceFound) {
                return false;
            } else {
                differenceFound = true;
            }
        }
    }
    return true;
}

bool is_one_edit_insert(const std::string& iFirst, const std::string& iSecond) {
    uint32_t idxA(0), idxB(0);
    
    while(idxA < iFirst.length() && idxB < iSecond.length()) {
        if(iFirst[idxA] != iSecond[idxB]) {
            if(idxA != idxB) {
                return false;
            }
            idxB++;
        } else {
            idxA++;
            idxB++;
        }
    }
    return true;
}

bool is_one_edit_away(const std::string& iFirst, const std::string& iSecond) {
    if(iFirst.length() == iSecond.length()) {
        return is_one_edit_replace(iFirst, iSecond);
    }
    if(iFirst.length() + 1 == iSecond.length()) {
        return is_one_edit_insert(iFirst, iSecond);
    }
    if(iFirst.length() == iSecond.length() + 1) {
        return is_one_edit_insert(iSecond, iFirst);
    }
    return false;
}


