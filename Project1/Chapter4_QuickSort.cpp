#include <iostream>
#include <vector>

template <typename T>
auto partition(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator end)
{
	// �� ���� �ݺ��ڸ� �����մϴ�.
	// �ϳ��� �ǹ��� ����Ű��, ������ ���� ������ ���۰� ������ ���Ҹ� ����ŵ�ϴ�.
	auto pivot_val = *begin;
	auto left_iter = begin + 1;
	auto right_iter = end;

	while (true)
	{
		// ������ ù ��° ���Һ��� �����Ͽ� �ǹ����� ū ���Ҹ� ã���ϴ�.
		while (*left_iter <= pivot_val && std::distance(left_iter,right_iter) > 0)
			left_iter++;

		//������ ������ ���Һ��� �����Ͽ� �ǹ����� ���� ���Ҹ� ã���ϴ�.
		while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
			right_iter--;

		//���� left_iter�� right_iter�� ���ٸ� ��ȯ�� ���Ұ� ������ �ǹ��մϴ�.
		//�׷��� ������ left_iter�� right_iter�� ����Ű�� ���Ҹ� ���� ��ȯ.
		if (left_iter == right_iter)
			break;
		else
			std::iter_swap(left_iter, right_iter);
	}

	if (pivot_val > * right_iter)
		std::iter_swap(begin, right_iter);

	return right_iter;
}

template <typename T>
void quick_sort(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last)
{
	// ���� ���Ϳ� �ϳ� �̻��� ���Ұ� �ִٸ�
	if (std::distance(begin, last) >= 1)
	{
		//���� �۾��� ����
		auto partition_iter = partition<T>(begin, last);

		//���� �۾��� ���� ������ ���͸� ��������� ����
		quick_sort<T>(begin, partition_iter - 1);
		quick_sort<T>(partition_iter, last);
	}
}