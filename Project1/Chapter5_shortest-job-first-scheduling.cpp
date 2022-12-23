#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

template<typename T>
auto compute_waiting_times(std::vector<T>& service_times)
{
	std::vector<T> W(service_times.size());
	W[0] = 0;
	for (auto i = 1; i < W.size(); i++) {
		W[i] = services_times[i - 1] + W[i - 1];
	}
	return W;
}

template<typename T>
void print_vector(std::vector<T>& V)
{
	for (auto& i : V)
	{
		std::cout << width(2);
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

template<typename T>
void compute_and_print_waiting_times(std::vector<T>& service_times)
{
	auto waiting_times = compute_waiting_times<int>(service_times);

	std::cout << "- 처리 시간: ";
	print_vector<T>(service_times);
	std::cout << "- 대기 시간: ";
	print_vector<T>(waiting_times);

	auto ave_waiting_times = std::accumulate(waiting_times.begin(), waiting_times.end(), 0.0) / waiting_times.size();
	std::cout << "-평균 대기 시간: " << ave_waiting_times;
	std::cout << std::endl;/
}