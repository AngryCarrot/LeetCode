#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
	{
		int i = m - 1, j = n - 1, position = m + n - 1;
		while (j >= 0) 
		{
			nums1[position--] = i >= 0 && nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
		}
		/*int position = m + n - 1;
		for (int i = n - 1; i < 0; --i)
		{
			for (int j = m - 1; j < 0; --j)
			{
				if (nums1[j] > nums2[i])
				{
					nums1[position--] = nums1[j];
				}
				else
				{
					nums1[position--] = nums2[i];
				}
			}
		}
		for (int i = 0; i != n; ++i)
		{
			for (int j = 0; j != m; ++j)
			{
				if (nums1[j] > nums2[i])
				{

				}
			}
		}*/
	}
};

int main()
{
	char str1[] = "hello world";
	cout << strlen(str1) << endl;
	cout << sizeof(str1) << endl;
	char *str2 = "hello world";
	cout << strlen(str1) << endl;
	cout << sizeof(str1) << endl;
	return 0;
}