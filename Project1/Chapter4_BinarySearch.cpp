#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

bool linear_search(int N, vector<int>& S)
{
	for (auto i : S)
	{
		if (i == N)
			return true;
	}
	return false;
}
bool binary_search(int N, std::vector<int>& S)
{
	auto first = S.begin();
	auto last = S.end();

	while (true)
	{
		auto range_length = std::distance(first, last);
		auto mid_element_index = std::floor(range_length / 2);
		auto mid_element = *(first + mid_element_index);

		if (mid_element == N)
		{
			return true;
		}
		else if (mid_element > N)
		{
			std::advance(last, -mid_element_index);
		}
		else
		{
			std::advance(first, mid_element_index);
		}

		// ���� �˻� ������ �ϳ��� ���Ҹ� ���� �ִٸ� false�� ��ȯ
		if (range_length == 1)
			return false;
	}
}
