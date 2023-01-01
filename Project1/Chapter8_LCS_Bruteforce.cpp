#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <time.h>
#include <iomanip>
#include <iostream>

#define DEBUG 1

#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

using namespace std;

vector<vector<pair<int, int>>> found;

int LCS_BruteForce(string A, string B, int i, int j,
	vector<pair<int, int>> subsequence)
{
	// ���� i�� A�� ���̺��� Ŀ���ų� �Ǵ� j�� B�� ���̺��� Ŀ����:
	if (i >= A.size() || j >= B.size())
	{
		found.push_back(subsequence);

		// ��͸� �����ϰ� �κ� �������� ���̸� ��ȯ�մϴ�.
		return subsequence.size();
	}

	// ���� A[i] = B[j] �̸�:
	if (A[i] == B[j])
	{
		// �κ� ������ ���̸� 1��ŭ �����մϴ�.
		subsequence.push_back({ i,j });

		//i�� j�� ���� 1�� �����մϴ�.
		return LCS_BruteForce(A, B, i + 1, j + 1, subsequence);
	}
	/* �׷��� ������:

	   �ɼ� 1) (i + 1)��°�� j��° ���ڿ� ���� �˻縦 �����մϴ�.
	   �ɼ� 2) i��°�� (j + 1)��° ���ڿ� ���� �˻縦 �����մϴ�.
	   �� ������ LCS�� �ɼ� 1 �� �ɼ� 2�� �ִ񰪰� �����ϴ�.
	 */

	return max(LCS_BruteForce(A, B, i + 1, j, subsequence),
		LCS_BruteForce(A, B, i, j + 1, subsequence));
}

void PrintSubsequences(string A, string B)
{
	// ���� �Լ��� �̿��� ����
	sort(found.begin(), found.end(), [](auto a, auto b)
		{
			// �κ� ������ ���̸� �������� ����
			if (a.size() != b.size())
			{
				return a.size() < b.size();
			}

			// �� �κ� ������ ���̰� ���ٸ� �ε����� ���� ������ ����
			return a < b;
		});

	// �ߺ� ����
	found.erase(unique(found.begin(), found.end()), found.end());

	int previousSize = 0;

	for (auto subsequence : found)
	{
		if (subsequence.size() != previousSize)
		{
			previousSize = subsequence.size();
			PRINT("SIZE = " << previousSize << endl);
		}

		// ������ �̿��Ͽ� ������ �ڸ��� ǥ��
		string a_seq(A.size(), '_');
		string b_seq(B.size(), '_');

		for (auto pair : subsequence)
		{
			// ��ĭ�� �κ� ���ڿ� ���ڷ� ä���
			a_seq[pair.first] = A[pair.first];
			b_seq[pair.second] = B[pair.second];
		}

		PRINT("\t" << a_seq << " " << b_seq << endl);
	}
}

const int UNKNOWN = -1;

int LCS_Memoization(string A, string B, int i, int j, vector<vector<int>>& memo)
{
	// ���� ���� - �� ���ڿ��� ���ؼ��� 0�� ��ȯ
	if (i == 0 || j == 0)
	{
		return 0;
	}

	// �� ���ڿ��� �κ� ���ڿ��� ���� ����� ����Ǿ� ������ ��ȯ
	if (memo[i - 1][j - 1] != UNKNOWN)
		return memo[i - 1][j - 1];

	//A�� B�� �� �κ� ���ڿ����� �� ������ ���ڰ� ������ Ȯ��
	if (A[i - 1] == B[j - 1])
	{
		// �� ��� A�� B�� �κ� ���ڿ����� ���� LCS ���̴� �� �κ� ���ڿ�����
		// ������ �� ���ڸ� ������ ���ڿ��κ��� ���� LCS ���̿� 1�� ���� �Ͱ� ����

		memo[i - 1][j - 1] = 1 + LCS_Memoization(A, B, i - 1, j - 1, memo);

		// ���̺� ����� ����� ��ȯ
		return memo[i - 1][j - 1];
	}

	// A�� B�� �� �κ� ���ڿ����� �� ������ ���ڰ� ���� �ʴٸ�
	// A�� �κ� ���ڿ����� ������ ���ڸ� ������ �Ͱ� B�� �κ� ���ڿ����� ���� LCS ����,
	// B�� �κ� ���ڿ����� ������ ���ڸ� ������ �Ͱ� A�� �κ� ���ڿ����� ���� LCS ���� ��
	// �ִ��� �����Ͽ� ����

	memo[i - 1][j - 1] = max(LCS_Memoization(A, B, i - 1, j, memo),
		LCS_Memoization(A, B, i, j - 1, memo));

	return memo[i - 1][j - 1];
}

vector<string> types =
{
	"BRUTE FORCE",
	"MEMOIZATION",
	"TABULATION"
};

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
	string A, B;
	cin >> A >> B;

	int tests = 2;


	for (int i = 0; i < tests; i++)
	{
		int LCS;

		clock_t timer = clock();

		switch (i)
		{
		case 0:
		{
			LCS = LCS_BruteForce(A, B, 0, 0, {});

#if DEBUG
			PrintSubsequences(A, B);
#endif
			break;
		}
		case 1:
		{
			vector<vector<int>> memo(A.size(), vector<int>(B.size(), UNKNOWN));
			LCS = LCS_Memoization(A, B, A.size(), B.size(), memo);
			break;
		}
		}

		cout << A << "�� " << B << "�� ���� ���� �κ� ������ ����: " << LCS << endl;

		GetTime(timer, types[i]);
		cout << endl;
	}
}

/*
123456 QWERTY
= 0
ACBEBC ABCBC
= 4
AZYBYXCXW ZZAYYBXXXCWW
= 6
ABCABDBEFBA ABCBEFBEAB
= 8
ABZCYDABAZADAEA YABAZADBBEAAECYACAZ
= 10
*/