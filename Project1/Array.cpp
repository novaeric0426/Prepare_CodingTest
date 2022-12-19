#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include <random>

using namespace std;

typedef enum {RED,WHITE,BLUE} Color;

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
	vector<Color>& A = *A_ptr;
	Color pivot = A[pivot_index];
	//First pass : group elements smaller than pivot
	int smaller = 0;
	for (int i = 0; i < A.size(); ++i) {
		if (A[i] < pivot)
			swap(A[i], A[smaller++]);
	}
	//Second pass : group elements greater than pivot
	int larger = A.size() - 1;
	for (int j = A.size() - 1; j >= 0 && A[j]>= pivot; --j) {
		if (A[j] > pivot)
			swap(A[j], A[larger--]);
	}
}

void BetterDFP(int pivot_index, vector<Color>* A_ptr) {
	vector<Color>& A = *A_ptr;
	Color pivot = A[pivot_index];
	/**
	* Keep the following invariants during partitioning:
	* bottom group : A[0 : smaller-1],
	* middle group : A[smaller : equal-1],
	* unclassified group : A[equal : larger-1],
	* top group : A[larger : A.size()-1],
	*/

	int smaller = 0, equal = 0, larger = A.size();
	while (equal < larger) {
		if (A[equal] < pivot) {
			swap(A[smaller++], A[equal++]);
		}
		else if (A[equal] == pivot) {
			++equal;
		}
		else {
			swap(A[equal], A[--larger]);
		}
	}
}

vector<int> PlusOne(vector<int> A) {
	++A.back();
	for (int i = A.size() - 1; i > 0 && A[i] == 10; --i) {
		A[i] = 0; A[i - 1]++;
	}
	if (A[0] == 10) {
		A[0] = 0;
		A.insert(A.begin(), 1);
	}
	return A;
}

bool CanReachEnd(const vector<int>& max_advance_steps) {
	int reach = 0; int last_index = max_advance_steps.size() - 1;
	for (int i = 0; i <= reach && reach < last_index; i++) {
		reach = max(reach, max_advance_steps[i] + i);
	}
	return reach >= last_index;
}

int DeleteDuplicates(vector<int>* A_ptr) {
	vector<int>& A = *A_ptr;
	if (A.empty())
		return 0;
	int write_index = 1;
	for (int i = 1; i < A.size(); i++) {
		if (A[i] != A[write_index-1]) {
			A[write_index++] = A[i];
		}
	}
	return write_index;
}

double BuyAndSellStock(vector<int>& prices) {
	double min_price_so_far = 10000000, max_profit = 0;
	for (const double& price : prices) {
		double max_profit_sell_today = price - min_price_so_far;
		max_profit = max(max_profit_sell_today, max_profit);
		min_price_so_far = min(price, min_price_so_far);
	}
	return max_profit;
}

double BuyAndSellStockTwice(const vector<double>& prices) {
	double max_total_profit = 0;
	vector<double> first_buy_sell_profits(prices.size(), 0);
	double min_price_so_far = numeric_limits<double>::max();

	for (int i = 0; i < prices.size(); ++i) {
		min_price_so_far = min(min_price_so_far, prices[i]);
		max_total_profit = max(max_total_profit, prices[i] - min_price_so_far);
		first_buy_sell_profits[i] = max_total_profit;
	}

	double max_prices_so_far = numeric_limits<double>::min();
	for (int i = prices.size()-1; i > 0; --i) {
		max_prices_so_far = max(max_prices_so_far, prices[i]);
		max_total_profit = max(max_total_profit, max_prices_so_far - prices[i] + first_buy_sell_profits[i - 1]);
	}
	return max_total_profit;
}

vector<int> GeneratePrimes(int n) {
	vector<int> primes;

	deque<bool> is_prime(n + 1, true);
	is_prime[0] = is_prime[1] = false;
	for (int p = 2; p < n; p++) {
		if (is_prime[p]) {
			primes.emplace_back(p);
			for (int j = p; j <= n; j += p) {
				is_prime[j] = false;
			}
		}
		
	}
	return primes;
}

void permute(int A[], int P[], int n)
{
	// For each element of P
	for (int i = 0; i < n; i++) {
		int next = i;

		// Check if it is already
		// considered in cycle
		while (P[next] >= 0) {

			// Swap the current element according
			// to the permutation in P
			swap(A[i], A[P[next]]);
			int temp = P[next];

			// Subtract n from an entry in P
			// to make it negative which indicates
			// the corresponding move
			// has been performed
			P[next] -= n;
			next = temp;
			
		}
		for (int j = 0; j < 5; j++) {
			cout << A[j];
		}
		cout << endl;
		
	}
}

vector<int> NextPermutation(vector<int> perm)
{
	int k = perm.size() - 2;
	while (k >= 0 && perm[k] >= perm[k + 1]) {
		--k;
	}
	if (k == -1) { return {}; }

	swap(*find_if(perm.rbegin(), perm.rend(),
		[&](int a) {return a > perm[k]; }),
		perm[k]);

	reverse(perm.begin() + k + 1, perm.end());
	return perm;
}

vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) 
{
	vector<int> spiral_ordering;
	for (int offset = 0; offset < ceil(0.5 * square_matrix.size()); ++offset) {
		MatrixLayerInClockwise(square_matrix, offset, &spiral_ordering);
	}
	return spiral_ordering;
}

void MatrixLayerInClockwise(const vector<vector<int>>& square_matrix,
	int offset, vector<int>* spiral_ordering) {
	if (offset == square_matrix.size() - offset - 1) {
		spiral_ordering->emplace_back(square_matrix[offset][offset]);
		return;
	}
	for (int j = offset; j < square_matrix.size() - offset - 1; ++j) { //맨 위에줄
		spiral_ordering->emplace_back(square_matrix[offset][j]);
	}
	for (int i = offset; i < square_matrix.size() - offset - 1; ++i) {
		spiral_ordering->emplace_back(square_matrix[i][square_matrix.size() - offset - 1]);
	}
	for (int j = square_matrix.size() - offset - 1; j > offset; --j) {
		spiral_ordering->emplace_back(square_matrix[square_matrix.size() - offset - 1][j]);
	}
	for (int i = square_matrix.size() - offset - 1; i > offset; --i) {
		spiral_ordering->emplace_back(square_matrix[i][offset]);
	}
}

void RotateMatrix(vector<vector<int>>* square_matrix_ptr) {
	vector<vector<int>>& square_matrix = *square_matrix_ptr;
	const int matrix_size = square_matrix.size() - 1;
	for (int i = 0; i < (square_matrix.size() / 2); ++i) {
		for (int j = i; j < matrix_size - i; ++j) {
			int temp1 = square_matrix[matrix_size - j][i];
			int temp2 = square_matrix[matrix_size - i][matrix_size - j];
			int temp3 = square_matrix[j][matrix_size - i];
			int temp4 = square_matrix[i][j];
			square_matrix[i][j] = temp1;
			square_matrix[matrix_size - j][i] = temp2;
			square_matrix[matrix_size - i][matrix_size - j] = temp3;
			square_matrix[j][matrix_size - i] = temp4;
		}
	}
}

	vector<Color> ABC{ RED,WHITE,BLUE ,RED,WHITE,BLUE ,RED,WHITE,BLUE,RED,WHITE,BLUE };



int main() {
	int A[] = { 9,8,7,6,5 };
	int P[] = { 4,3,1,0,2 };
	int n = sizeof(A) / sizeof(int);

	permute(A, P, n);

	// Print the new array after
	// applying the permutation
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";

	return 0;
}