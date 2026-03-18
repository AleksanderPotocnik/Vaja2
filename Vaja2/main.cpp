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
void setUpArray(vector<unsigned char>& A, vector<int>& C, int arraySize, int k) {
	for (int i = 0; i < arraySize; i++) {
		C[(A[i] >> k) & 1]++;
	}
	C[1] += C[0];
}
void counting_sort(vector<unsigned char>& A, int k) {
	int arraySize = A.size();

	vector<unsigned char> B(arraySize);
	vector<int> C(2, 0);

	setUpArray(A, C, arraySize, k);

	for (int i = arraySize - 1; i >= 0; i--) {
		B[--C[(A[i] >> k) & 1]] = A[i];
	}
	swap(A, B);
}

void radix_sort(vector<unsigned char>& A) {
	for (int k = 0; k < 8; k++) {
		counting_sort(A, k);
	}
}
void Izpis_Stevil(unsigned char* polje, unsigned int velikost) {
	ofstream output("out.txt");

	for (int i = 0; i < velikost; i++)
		output << (int)polje[i] << ' ';
}
int main(int argc, const char* argv[]) {
	vector<unsigned char> A;

	if (argc < 2) return 0;
	if (!Branje_Stevil(A, argv[1])) return 0;

	radix_sort(A);
	Izpis_Stevil(A.data(), A.size());
	return 0;
}