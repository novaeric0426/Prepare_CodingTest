#include<iostream>
#include<vector>

template <typename T>
auto partition(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator end)
{
	auto pivot_val = *begin;
	auto left_iter = begin + 1;
	auto right_iter = end;

	while (true)
	{
		while (*left_iter <= pivot_val && left_iter != right_iter)
			left_iter++;
		while (*right_iter >= pivot_val && left_iter != right_iter)
			right_iter--;


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
	if (std::distance(begin, last) >= 1)
	{
		auto partition_iter = partition<T>(begin, last);

		quick_sort<T>(begin, partition_iter - 1);
		quick_sort<T>(partition_iter, last);
	}
}

template<typename T>
auto find_median(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last)
{
	quick_sort<T>(begin, last);

	return begin + (std::distance(begin, last) / 2);
}

template<typename T>
auto partition_using_given_pivot(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator end,
	typename std::vector<T>::iterator pivot)
{
	auto left_iter = begin;
	auto right_iter = end;

	while (true)
	{
		while (*left_iter < *pivot && left_iter != right_iter)
			left_iter++;
		
		while (*right_iter >= *pivot && left_iter != right_iter)
			right_iter--;

		if (left_iter == right_iter)
			break;
		else
			std::iter_swap(left_iter, right_iter);
	}

	if (*pivot > * right_iter)
		std::iter_swap(pivot, right_iter);
	return right_iter;
}

template<typename T>
typename std::vector<T>::iterator linear_time_select(
	typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last,
	size_t i)
{
	auto size = std::distance(begin, last);
	
	if (size > 0 && i < size)
	{
		auto num_Vi = (size + 4) / 5;
		size_t j = 0;

		std::vector<T> M;
		for (; j < size / 5; j++)
		{
			auto b = begin + (j * 5);
			auto l = begin + (j * 5) + 5;

			M.push_back(*find_median(b, l));
		}
		if (j * 5 < size)
		{
			auto b = begin + (j * 5);
			auto l = begin + (j * 5) + (size % 5);

			M.push_back(*find_median(b, l));
		}

		auto median_of_medians = (M.size() == 1) ? M.begin() :
			linear_time_select<T>(M.begin(), M.end() - 1, M.size() / 2);

		auto partition_iter = partition_using_given_pivot<T>(begin, last, median of medians);
		auto k = std::distance(begin, partition_iter) + 1;

		if (i == k)
			return partition_iter;
		else if (i < k)
			return linear_time_select<T>(begin, partition_iter - 1, i);
		else if (i > k)
			return linear_time_select<T>(partition_iter + 1, last, i - k);
	}
	else
	{
		return begin;
	}
}