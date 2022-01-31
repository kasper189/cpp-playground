#ifndef arrays_string_h
#define arrays_string_h

void run_arrays_string();

//Exercises
bool is_unique(const std::string& iString);
bool is_permutation(const std::string& iFirst, const std::string& iSecond);
void urlify(std::string& iString, const uint32_t& realLength);
bool is_palindrome_permutation(const std::string& iString);
bool is_one_edit_away(const std::string& iFirst, const std::string& iSecond);
std::string compress(const std::string& iString);

#endif /* arrays_string_h */
