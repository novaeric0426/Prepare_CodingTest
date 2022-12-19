// std::string �� ���ǵ� getline ���
#include <iostream>
#include <sstream>
#include <string>

double to_number(std::string s) {
	std::istringstream ss(s);
	double x;

	ss >> x;
	return x;
}

int main() {
	std::cout << "��ȯ:: 1+2 = " << to_number("1") + to_number("2") << endl;
	return 0;
}