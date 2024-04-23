#include <iostream>

//This text centering function was found on StackOverflow.com
template<typename charT, typename traits = std::char_traits<charT> >
class center_helper {
    std::basic_string<charT, traits> str_;
public:
    center_helper(std::basic_string<charT, traits> str) : str_(str) {}
    template<typename a, typename b>
    friend std::basic_ostream<a, b>& operator<<(std::basic_ostream<a, b>& s, const center_helper<a, b>& c);
};

void help();
void logo();
int isWin(int num1, int num2, int num3, int win1, int win2, int win3, int fbWin);
int earningsCalculator(int winType);
int readFile (std::string fileName, int in1, int in2, int in3, bool brute, int* cost, int* roi);
bool fileTest(std::string fileName);
void autoScan(std::string fileName, bool brute, int* cost, int* roi);