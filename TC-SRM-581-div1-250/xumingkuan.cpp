#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <queue>
#include <map>
#include <set>
using namespace std;

class SurveillanceSystem
{
private:
	int n, a[55];//a[i]: number of containers in interval [i, i + L)
	int cnt[55];//cnt[i]: number of j which reports[j] == i
	int tot[55];//tot[i]: number of j which a[j] == i
	int type[55];//1: probably monitored; 2: probably not monitored
	bool visit[55];//if there is probably a camera at interval [i, i + L)
	int num[55];//num[i]: number of j which a[j] == i and the camera at interval [i, i + L) shouldn't exist when some place is not monitored
public:
	string getContainerInfo(string containers, vector<int> reports, int L)
	{
		n = containers.size();
		a[0] = 0;
		for(int i = 0; i < L; i++)
			a[0] += (containers[i] == 'X');
		for(int i = 1; i <= n - L; i++)
			a[i] = a[i - 1] + (containers[i + L - 1] == 'X') - (containers[i - 1] == 'X');
		memset(cnt, 0, sizeof(cnt));
		for(int i = 0; i < reports.size(); i++)
			cnt[reports[i]]++;
		memset(type, 0, sizeof(type));
		memset(visit, false, sizeof(visit));
		memset(tot, 0, sizeof(tot));
		for(int i = 0; i <= n - L; i++)
			visit[i] = (bool)cnt[a[i]], tot[a[i]]++;
		int tmp = 0;//number of probable cameras
		for(int i = 0; i < n; i++)
			if((tmp += (i <= n - L ? visit[i] : 0) - (i >= L ? visit[i - L] : 0)))
				type[i] |= 1;
		memset(num, 0, sizeof(num));
		tmp = 0;//number of paradoxes
		for(int i = 0; i < n; i++)
		{
			tmp += (i <= n - L && num[a[i]]++ == tot[a[i]] - cnt[a[i]]);
			tmp -= (i >= L && --num[a[i - L]] == tot[a[i - L]] - cnt[a[i - L]]);
			if(!tmp)
				type[i] |= 2;
		}
		string ans;
		for(int i = 0; i < n; i++)
			ans += type[i] == 3 ? '?' : type[i] == 2 ? '-' : type[i] == 1 ? '+' : '*';//'*' means error
		return ans;
	}
};

