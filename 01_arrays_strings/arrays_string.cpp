#include <iostream>
#include <array>
#include <vector>
#include <sstream>

#include "arrays_string.h"

std::string bool_as_text(bool b)
{
    std::stringstream converter;
    converter << std::boolalpha << b;
    return converter.str();
}

void print_matrix(const std::vector< std::vector<int> >& iMatrix, const int& rows, const int& cols){
    
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c) {
            std::cout << iMatrix[r][c] << "-";
        }
        std::cout << "|";
    }
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
    
    // 1.6
    std::string m("aabcccccaaa");
    std::cout << "is one edit away: a2b1c5a3 is " + compress(m) << std::endl;
    
    std::cout << "is one edit away: bale is " + compress(k) << std::endl;
    
    // 1.7
//    char n[4][4] = {
//        {'A', 'B', 'C', 'D'},
//        {'E', 'F', 'G', 'H'},
//        {'I', 'J', 'K', 'L'},
//        {'M', 'N', 'O', 'P'}
//    };
//    print_matrix(n);
//    rotate_matrix(*n[]);
//    std::cout << "rotated matrix is: M-I-E-A|N-J-F-B|O-K-G-C|P-L-H-D is " + print_matrix(n) << std::endl;
    
    // 1.8
    std::vector< std::vector<int> > o;
    std::vector<int> p = {1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1};
    int cnt(0);
    o.resize(5);
    for(int i = 0 ; i < 5 ; ++i)
    {
        o[i].resize(4);
    }
    for(int r = 0; r < 5; ++r){
        for(int c = 0; c < 4; ++c){
            o[r][c] = p[cnt];
            cnt++;
        }
    }
    
    zerofy_rows_columns(o, 5, 4);
    std::cout << "zerofied matrix is: 0-0-0-0|0-1-0-0|0-0-0-0|0-0-0-0|0-1-0-0| is ";
    print_matrix(o, 5, 4);
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

/*1.6*/
bool has_duplicate(const std::string& iString) {
    std::string::const_iterator it;
    for (it = iString.begin(); it != iString.end(); ++it){
        if((it+1) != iString.end() && *it == *(it+1)) {
            return true;
        }
    }
    return false;
}

uint32_t count_duplicates(const std::string& iString, const uint32_t pos){
    uint32_t duplicates(1);
    
    for(uint32_t i = pos; pos < iString.length(); ++i) {
        if(i + 1 < iString.length() && iString[i] == iString[i + 1]) {
            duplicates++;
        } else {
            break;
        }
    }
    return duplicates;
}

std::string compress(const std::string& iString) {
    if(iString.empty() || !has_duplicate(iString)) {
        return iString;
    }
    
    std::string compressed;
    
    uint32_t cnt(0);
    
    while(cnt < iString.length()) {
        uint32_t duplicates = count_duplicates(iString, cnt);
        compressed += iString.at(cnt);
        compressed += std::to_string(duplicates);
        cnt += duplicates;
    }
    return compressed;
}

///*1.7*/
//void rotate_matrix(char **matrix) {
//    // Number of columns
//    int columns(0);
//    for(char *p = *matrix; *p; ++p) {
//        columns++;
//    }
//
//    for(int c = 0; c < columns / 2; ++columns){
//        for(int i = c; i < columns - c - 1; ++i){
//            int top(matrix[c][i]);
//            matrix[c][i] = matrix[columns - 1 - c - (i - c)][c];
//            matrix[columns - 1 - c - (i - c)][c] = matrix[columns - 1 - c][columns - 1 - c - (i - c)];
//            matrix[columns - 1 - c][columns - 1 - c - (i - c)] = matrix[i][columns - 1 - c];
//            matrix[i][columns - 1 - c] = top;
//        }
//    }
//}

/*1.8*/
void zerofy_rows_columns(std::vector< std::vector<int> >& iMatrix, const int& rows, const int& cols) {
    std::vector<int> row_zeros;
    std::vector<int> col_zeros;
    
    //Finds rows and cols that have a zero
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c) {
            if(iMatrix[r][c] == 0) {
                row_zeros.push_back(r);
                col_zeros.push_back(c);
            }
        }
    }
    
    //Reset rows
    for(const int& rz : row_zeros) {
        for(int c = 0; c < cols; ++c){
            iMatrix[rz][c] = 0;
        }
    }
    
    //Reset cols
    for(const int& cz : col_zeros) {
        for(int r = 0; r < rows; ++r){
            iMatrix[r][cz] = 0;
        }
    }
}
