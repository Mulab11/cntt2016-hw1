#include <algorithm>
using namespace std;
class TeamContest
{
public:
	int worstRank(vector<int> w)
	{
		int m = min(w[0], min(w[1], w[2])) + max(w[0], max(w[1], w[2]));
		w.erase(w.begin(), w.begin() + 3);
		int n = w.size();
		sort(w.begin(), w.end(), [] (int a, int b)
		{
			return a > b;
		});
		int ans = 1;
		for(int i = 0, j = n - 1, k = n / 3; k; i++, j--, ans++)
		{
			while(i < j && w[i] + w[j] <= m)
				j--;
			if(i + 1 >= j)
				break;
			k = min(k - 1, (j - i - 2) / 3); //中间最多还能选几组 
		}
		return ans;
	}
};