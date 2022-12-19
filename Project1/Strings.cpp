#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<cstring>
using namespace std;

/*bool IsPalindromic(const string& s) {
	for (int i = 0, j = s.size() - 1; i < j; i++, --j) {
		if (s[i] != s[j])
			return false;
	}
	return true;
}
string IntToString(int x) {
	bool is_negative = false;
	if (x < 0) {
		is_negative = true;
	}
	string s;
	do {
		s += '0' + abs(x % 10);
		x /= 10;
	} while (x);
	if (is_negative) {
		s += '-';
	}
	return { s.rbegin(),s.rend() };
}

int StringToInt(const string& s) {
	int result = 0;
	for (int i = s[0] == '-' ? 1 : 0; i < s.size(); i++) {
		const int digit = s[i] - '0';
		result = result * 10 + digit;
	}
	return s[0] == '-' ? -result : result;
}
string ConstructFromBase(int NumAsInt, int base) {
	return NumAsInt == 0
		? ""
		: ConstructFromBase(NumAsInt / base, base) +
		(char)(NumAsInt % base >= 10 ? 'A' + NumAsInt % base - 10 : '0' + NumAsInt % base);
}
string ConvertBase(const string& NumAsString, int b1, int b2) {
	bool is_negative = NumAsString.front() == '-';
	int NumAsInt = 0;
	for (size_t i = (is_negative == true ? 1 : 0); i < NumAsString.size(); ++i) {
		NumAsInt *= b1;
		NumAsInt += isdigit(NumAsString[i]) ? NumAsString[i] - '0' //숫자인경우
			: NumAsString[i] - 'A' + 10; //9를 넘어가서 알파벳인경우
	}
	return (is_negative ? "-" : "") + (NumAsInt == 0 ? "0" : ConstructFromBase(NumAsInt, b2));
}


int ReplaceAndRemove(int size, char s[]) {
	int write_idx = 0, a_count = 0;
	for (int i = 0; i < size; ++i) {
		if (s[i] != 'b') {
			s[write_idx++] = s[i];
		}
		if (s[i] == 'a') {
			++a_count;
		}
	}
	int cur_idx = write_idx - 1;
	write_idx = write_idx + a_count - 1;
	const int final_size = write_idx + 1;

	while(cur_idx >= 0) {
		if (s[cur_idx] == 'a') {
			s[write_idx--] = 'd';
			s[write_idx--] = 'd';
		}
		else {
			s[write_idx--] = s[cur_idx];
		}
		--cur_idx;
	}
	return final_size;
}

bool IsPalindrome(const string& s) {
	int i = 0; int j = s.size() - 1;
	while (i < j) {
		while(!isalnum(s[i]) && i < j) {
			++i;
		}
		while (!isalnum(s[j]) && i < j) {
			--j;
		}
		if (tolower(s[i++]) != tolower(s[j--])) {
			return false;
		}
	}
	return true;
}

void ReverseWords(string* s) {
	reverse(s->begin() , s->end());

	size_t start = 0, end;
	while ((end = s->find(" ", start)) != string::npos) {
		//Reverse each word in the string.
		reverse(s->begin() + start, s->begin() + end);
		start = end + 1;
	}
	//Reverse the last word.
	reverse(s->begin() + start, s->end());
}



int RomanToInteger(const string& s) {
	unordered_map<char, int> T = { {'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000} };

	int sum = T[s.back()];
	for (int i = s.size() - 2; i >= 0; --i) {
		if (T[s[i]] > T[s[i + 1]]) {
			sum += T[s[i]];
		}
		else {
			sum -= T[s[i]];
		}
	}
	return sum;
}

bool IsValidPart(const string& s) {
	if (s.size() > 3) {
		return false;
	}
	// 00,000,01 등은 not valid 하지만 0은 가능.
	if (s.front() == '0' && s.size() > 1) {
		return false;
	}
	int val = stoi(s);
	return val <= 255 && val >= 0;
}

vector<string> GetValidIPAddress(const string& s) {
	vector<string> result;
	for (size_t i = 1; i < 4; ++i) {
		const string first = s.substr(0, i);
		if (IsValidPart(first)) {
			for (size_t j = 1; i + j < s.size() && j < 4; ++j) {
				const string second = s.substr(i, j);
				if (IsValidPart(second)) {
					for (size_t k = 1; i + j + k < s.size() && k < 4; ++k) {
						const string third = s.substr(i + j, k);
						const string fourth = s.substr(i + j + k);
						if (IsValidPart(third) && IsValidPart(fourth)) {
							result.emplace_back(first + "." + second + "." + third + "." + fourth);
						}
					}
				}
			}
		}
	}
}*/

class Complex {
private:
	double real, img;

	double get_number(const char* str, int from, int to) const;

public:
	Complex(double real, double img) : real(real),img(img){}
	Complex(const Complex& c) { real = c.real, img = c.img; }
	Complex(const char* str);

	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;

	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);
	Complex& operator*=(const Complex& c);
	Complex& operator/=(const Complex& c);

	Complex& operator=(const Complex& c);

	void println() {
		std::cout << "( " << real << " , " << img << " ) " << std::endl;
	}
};

Complex::Complex(const char* str) {
	int begin = 0, end = strlen(str);
	img = 0.0;
	real = 0.0;
	
	int pos_i = -1;
	for (int i = begin; i != end; ++i) {
		if (str[i] == 'i') {
			pos_i = i;
			break;
		}
	}

	if (pos_i == -1) {
		real = get_number(str, begin, end - 1);
		return;
	}

	real = get_number(str, begin, pos_i - 1);
	img = get_number(str, pos_i + 1, end - 1);

	if (pos_i >= 1 && str[pos_i - 1] == '-') img *= -1.0;
}

double Complex::get_number(const char* str, int from, int to) const {
	bool minus = false;
	if (from > to) return 0;

	if (str[from] == '-') minus = true;
	if (str[from] == '-' || str[from] == '+') from++;

	double num = 0.0;
	double decimal = 1.0;

	bool integer_part = true;
	for (int i = from; i <= to; i++) {
		if (isdigit(str[i]) && integer_part) {
			num *= 10.0;
			num += (str[i] - '0');
		}
		else if (str[i] == '.') {
			integer_part = false;
		}
		else if (isdigit(str[i]) && !integer_part) {
			decimal /= 10.0;
			decimal += ((str[i] - '0') * decimal);
		}
		else
			break;
	}
	if (minus) num *= -1.0;
	return num;
}
Complex Complex::operator+(const Complex& c) const {
	Complex temp(real + c.real, img + c.img);
	return temp;
}
Complex Complex::operator-(const Complex& c) const {
	Complex temp(real - c.real, img - c.img);
	return temp;
}
Complex Complex::operator*(const Complex& c) const {
	Complex temp(real * c.real - img * c.img, real * c.img + img * c.real);
	return temp;
}
Complex Complex::operator/(const Complex& c) const {
	Complex temp(
		(real * c.real + img * c.img) / (c.real * c.real + c.img * c.img),
		(img * c.real - real * c.img) / (c.real * c.real + c.img * c.img));
	return temp;
}

Complex& Complex::operator+=(const Complex& c) {
	(*this) = (*this) + c;
	return *this;
}
Complex& Complex::operator-=(const Complex& c) {
	(*this) = (*this) - c;
	return *this;
}
Complex& Complex::operator*=(const Complex& c) {
	(*this) = (*this) * c;
	return *this;
}
Complex& Complex::operator/=(const Complex& c) {
	(*this) = (*this) / c;
	return *this;
}
Complex& Complex::operator=(const Complex& c) {
	real = c.real;
	img = c.img;
	return *this;
}

