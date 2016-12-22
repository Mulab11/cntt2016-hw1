#include <algorithm>
#include <vector>
using namespace std;

class EelAndRabbit
{
private:
	int n;
	pair<int, int> a[105];//<time, pos>
public:
	int getmax(vector<int> l, vector<int> t)
	{
		n = l.size();
		for(int i = 0; i < n; i++)
			a[i << 1] = make_pair(t[i], i << 1), a[(i << 1) | 1] = make_pair(t[i] + l[i] + 1, (i << 1) | 1);//appear at time t[i], disappear at time t[i] + l[i] + 1
		sort(a, a + (n << 1));
		a[n << 1].first = a[(n << 1) - 1].first + 1;//for convenience
		int ans = 0;
		for(int i = 0; i < n; i++)//enumerate the eel which is caught as soon as it arrives (the first catch will be at time t[i])
		{
			int cnt1 = 0, cnt2 = 0, now = 0;
			for(int j = 0; j < (n << 1); j++)
			{
				if(t[a[j].second >> 1] <= t[i] && t[i] <= t[a[j].second >> 1] + l[a[j].second >> 1])//caught in the first catch
					cnt1 += (a[j].second & 1);//it will appear in array 'a' twice (appear/disappear), we should count only once
				else
					now += (a[j].second & 1) ? -1 : 1;//odd: disappear; even: appear
				if(a[j].first != a[j + 1].first && now > cnt2)
					cnt2 = now;//the second catch at time a[j].first
			}
			if(cnt1 + cnt2 > ans)
				ans = cnt1 + cnt2;
		}
		return ans;
	}
};

