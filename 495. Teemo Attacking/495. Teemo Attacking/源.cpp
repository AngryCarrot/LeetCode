#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int findPoisonedDuration(vector<int>& timeSeries, int duration) 
	{
		if (timeSeries.empty())
		{
			return 0;
		}
		int result = 0;
		int length = timeSeries.size();

		for (int i = 0; i != length; ++i)
		{
			if (i == length - 1)
			{
				result += duration;
			}
			else
			{
				if (timeSeries[i] + duration >= timeSeries[i + 1])
				{
					result += timeSeries[i + 1] - timeSeries[i];
				}
				else
				{
					result += duration;
				}
			}
		}
		return result;
	}	
};

int main()
{
	Solution s;
	vector<int> v = {1, 2, 4, 7};
	int duration = 2;
	int result = s.findPoisonedDuration(v, duration);
	cout << result << endl;
	return 0;
}