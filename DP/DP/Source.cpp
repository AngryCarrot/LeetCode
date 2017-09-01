#include "Solution.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main()
{
	vector<int> ma = { 2, 4, 7, 4, 2, 1, 6, 7, 8, 5 };
	int x = lower_bound(begin(ma), end(ma), 5) - begin(ma);
	cout << x << endl;
	vector<int> a(11);
	for (int i = 1; i <= 10; ++i)
	{
		a[i] = i;
	}
	int ans = 0;
	do {
		if (a[3] == 10 && a[5] == 1)
		{
			++ans;
		}
	} while (next_permutation(begin(a) + 1, end(a)));
	cout << ans << endl;
	Solution sln;

	int m = 15;
	int n = 1;
	vector<vector<int>> matrix(m, vector<int>(n, 0));
	int i = 0;
	int j = 0;
	int count = 1;
	int left = 0;
	int right = n;
	int top = 0;
	int bottom = m;
	while (count <= m * n)
	{
		for (int j = left; j < right; ++j)
		{
			matrix[top][j] = count++;
		}
		++top;
		if (top == bottom) break;
		for (int i = top; i < bottom; ++i)
		{
			matrix[i][right - 1] = count++;
		}
		--right;
		if (right == left) break;
		for (int j = right - 1; j >= left; --j)
		{
			matrix[bottom - 1][j] = count++;
		}
		--bottom;
		for (int i = bottom - 1; i >= top; --i)
		{
			matrix[i][left] = count++;
		}
		++left;
	}
	for (auto row : matrix)
	{
		for (auto item : row)
		{
			cout << setw(7) << item << ", ";
		}
		cout << endl;
	}

	return 0;
}