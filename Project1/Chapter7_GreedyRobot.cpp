#include<vector>
#include<iostream>
#include<climits>
#include<fstream>

using namespace std;

struct Edge
{
	int src;
	int dst;
	int weight;
};

const int UNKNOWN = INT_MAX;

bool ReadTestCase(string filename, int& N, vector<Edge>& edges)
{
	ifstream infile(filename);

	if (!infile.is_open())
	{
		cout << "테스트 케이스 파일을 열 수 없습니다!" << endl;
		return false;
	}

	infile >> N;

	for (int i = 0; i < N * N - 1; i++)
	{
		string directions;
		int power;

		infile >> directions >> power;

		int next = i;

		for (auto d : directions)
		{
			switch (d)
			{
			case 'N':next = i - N; break;
			case 'E':next = i + 1; break;
			case 'S':next = i + N; break;
			case 'W':next = i - 1; break;
			}

			// power 값의 부호를 바꿔서 에지 가중치로 사용
			edges.push_back(Edge{ i,next,-power });
		}
	}
	return true;
}

vector<int> BellmanFord(vector<Edge> edges, int V, int start)
{
	vector<int> distance(V, UNKNOWN);
	distance[start] = 0;

	for (int i = 0; i < V - 1; i++)
	{
		for (auto& e : edges)
		{
			if (distance[e.src] == UNKNOWN)
				continue;

			if (distance[e.dst] > distance[e.src] + e.weight)
			{
				distance[e.dst] = distance[e.src] + e.weight;
			}
		}
	}

	for (auto& e : edges)
	{
		if (distance[e.src] == UNKNOWN)
			continue;
		if (distance[e.dst] > distance[e.src] + e.weight)
		{
			return{};
		}
	}

	return distance;
}

int main()
{
	int N;
	vector<Edge> edges;     // 에지 리스트

	// testcase1~5.txt 파일로부터 테스트 입력을 받아 결과 확인
	if (ReadTestCase("testcase1.txt", N, edges))
	{
		vector<int> distance = BellmanFord(edges, N * N, 0);

		if (distance.empty() || distance[N * N - 1] == UNKNOWN)
			cout << "탐색 중단" << endl;
		else
			cout << -1 * distance[N * N - 1] << endl;
	}
}