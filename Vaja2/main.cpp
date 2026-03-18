#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool Branje_Stevil(vector<unsigned char>& vec, const char s[]) {
    ifstream input(s);
    int st;

    if (!input.is_open()) {
        return false;
    }

    while (!input.eof()) {
        input >> st;
        vec.push_back(st);
        while (isspace(input.peek())) input.get();
    }
    input.close();
    return true;
}


int main(int argc, const char* argv[]) {
{
    vector<unsigned char> A;

    if (argc < 2) return 0;
    if (!Branje_Stevil(A, argv[1])) return 0;


    return 0;
}