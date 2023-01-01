#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iomanip>


#define DEBUG 0

#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

using namespace std;

const int UNKNOWN = -1;

vector<string> types =
{
	"BRUTE FORCE",
	"BACKTRACKING",
	"MEMOIZATION",
	"TABULATION"
};

void GetAllSubsets(vector<int> set, vector<int> subset,
	int index, vector<vector<vector<int>>>& allSubsets)
{
	// ���� set�� ���� ������ ���
	if (index == set.size())
	{
			// �κ����� ũ�⸦ �ε����� ����Ͽ� �κ������� allSubsets�� �߰�
			allSubsets[subset.size()].push_back(subset);
			return;
	} 

	// ���Ҹ� �߰����� �ʰ� ��� ȣ��
	GetAllSubsets(set, subset, index + 1, allSubsets);

	//���Ҹ� �߰��ϰ� ��� ȣ��
	subset.push_back(set[index]);
	GetAllSubsets(set, subset, index + 1, allSubsets);
}

bool SubsetSum_BruteForce(vector<int> set, int target)
{
	vector<vector<vector<int>>> allSubsets(set.size() + 1);

	GetAllSubsets(set, {}, 0, allSubsets);

	for (int size = 0; size < set.size(); size++)
	{
		PRINT("�κ������� ���� ����: " << size << endl);

		for (auto subset : allSubsets[size])
		{
			PRINT("\t{ ");

			int sum = 0;
			for (auto number : subset)
			{
				sum += number;
				PRINT(number << " ");
			}

			PRINT("} = " << sum << endl);

			if (sum == target)
				return true;
		}
	}

	return false;
}

bool SubsetSum_Backtracking(vector<int> set, int sum, int i)
{
	// ���� ���� �κ������� ���� target�� ���ٸ�
	if (sum == 0)
	{
		return true;
	}

	// ���� ���� �κ������� ���� target���� ũ�ų�, ������ ���� �����ߴٸ�
	if (i == set.size() || set[i] > sum)
	{
		return false;
	}

	//Case 1: sum���� set[i]�� ���� ��� ȣ��(i��° ���Ҹ� �κ����տ� �߰�)
	//Case 2: sum�� �״�� �����Ͽ� ��� ȣ��(i��° ���Ҹ� �κ����տ� �߰����� ����)

	return SubsetSum_Backtracking(set, sum - set[i], i + 1)
		|| SubsetSum_Backtracking(set, sum, i + 1);
}

bool SubsetSum_Memoization(vector<int>& set, int sum, int i,
	vector<vector<int>>& memo)
{
	// ���� ���� �κ������� ���� target�� ���ٸ�
	if (sum == 0)
	{
		return true;
	}
	if (i == set.size() || set[i] > sum)
	{
		return false;
	}

	// ���� ���°� ĳ�ÿ� �ִ��� Ȯ��
	if (memo[i][sum] == UNKNOWN)
	{
		// ���� ���¿� ���� �ַ���� ���Ͽ� ĳ�ÿ� ����
		bool append = SubsetSum_Memoization(set, sum - set[i], i + 1, memo);
		bool ignore = SubsetSum_Memoization(set, sum, i + 1, memo);

		memo[i][sum] = append || ignore;
	}
	// ĳ�ÿ� ����� ���� ��ȯ
	return memo[i][sum];
}

vector<vector<bool>> SubsetSum_Tabulation(vector<int>& set)
{
	int maxSum = 0;

	for (int i = 0; i < set.size(); i++)
	{
		maxSum += set[i];
	}

	vector<vector<bool>> DP(set.size() + 1, vector<bool>(maxSum + 1, 0));

	for (int i = 0; i < set.size(); i++)
	{
		DP[i][0] = true;
	}

	for (int i = 1; i <= set.size(); i++)
	{
		for (int sum = 1; sum <= maxSum; sum++)
		{
			if (sum < set[i - 1])
			{
				DP[i][sum] = DP[i - 1][sum];
			}
			else
			{
				DP[i][sum] = DP[i - 1][sum] || DP[i - 1][sum - set[i - 1]];
			}
		}
	}

	return DP;
}

void GetTime(clock_t& timer, string type)
{
	// ���� �ð����� timer�� ���� ��� �ð��� ���
	timer = clock() - timer;

	// ȭ�鿡 ��� �ð� ���
	cout << type << " ��� ��� �ð�: ";
	cout << fixed << setprecision(5) << (float)timer / CLOCKS_PER_SEC << endl;

	timer = clock(); // timer�� ���� �ð����� �ʱ�ȭ
}

int main()
{
	vector<int> set = { 16, 1058, 22, 13, 46, 55, 3, 92, 47, 7,
					   98, 367, 807, 106, 333, 85, 577, 9, 3059 };
	int target = 6076;
	int tests = 4;

	sort(set.begin(), set.end());

	for (int i = 0; i < tests; i++)
	{
		bool found = false;

		clock_t timer = clock();

		switch (i)
		{
		case 0:
			found = SubsetSum_BruteForce(set, target);
			break;
		case 1:
			found = SubsetSum_Backtracking(set, target, 0);
			break;
		case 2:
		{
			// �޸������̼� ���̺� �ʱ�ȭ
			vector<vector<int>> memo(set.size(), vector<int>(7000, UNKNOWN));

			found = SubsetSum_Memoization(set, target, 0, memo);
			break;
		}
		case 3:
		{
			int total = 0;
			for (auto number : set)
				total += number;

			vector<vector<bool>> DP = SubsetSum_Tabulation(set);
			found = DP[set.size()][target];

			vector<int> subsetSums;
			for (int sum = 1; sum <= total; sum++)
			{
				if (DP[set.size()][sum])
				{
					subsetSums.push_back(sum);
				}
			}

			cout << "������ ���� " << subsetSums.size() << "������ �κ������� ���� �����մϴ�:" << endl;

			for (auto sum : subsetSums)
				cout << sum << " ";
			cout << endl;

			break;
		}
		}

		if (found)
		{
			cout << "���� ���� " << target << "�� �κ������� �ֽ��ϴ�." << endl;
		}
		else
		{
			cout << "���� ���� " << target << "�� �κ������� �����ϴ�." << endl;
		}

		GetTime(timer, types[i]);
		cout << endl;
	}
}