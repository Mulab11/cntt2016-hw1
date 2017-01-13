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
const int MAXN = 2525;
pair<int, int> a[MAXN];//<s[i], t[i]>
int t2[MAXN];
bool cmp(int i, int j)
{
	return t2[i] == t2[j] ? a[i].first > a[j].first : t2[i] > t2[j];
}
class ShoutterDiv1
{
private:
	string concatenate(const vector<string> &vec)
	{
		string ret;
		for(int i = 0; i < vec.size(); i++)
			ret += vec[i];
		return ret;
	}
	int n;
	int mnt;//rabbit mnt has minimal t[]
	int f[MAXN];//f[i]: minimal number of posts(not reposts) necessary for rabbit i to be able to read the self-introduction of rabbit mnt
	int g[MAXN];//g[i]: maximal t[j] where rabbit j is able to read the self-introduction of rabbit mnt with i posts(not reposts)
	int h[MAXN];//h[i]: minimal s[j] where rabbit j is able to read the self-introduction of rabbit n-1 with i posts(not reposts)
	//rabbit n-1 has maximal s[]
	int seq[MAXN];
public:
	int count(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1)
	{
		string S1000 = concatenate(s1000), S100 = concatenate(s100), S10 = concatenate(s10), S1 = concatenate(s1), T1000 = concatenate(t1000), T100 = concatenate(t100), T10 = concatenate(t10), T1 = concatenate(t1);
		n = S1.size();
		for(int i = 0; i < n; i++)
			a[i] = make_pair((S1000[i] - '0') * 1000 + (S100[i] - '0') * 100 + (S10[i] - '0') * 10 + (S1[i] - '0'), (T1000[i] - '0') * 1000 + (T100[i] - '0') * 100 + (T10[i] - '0') * 10 + (T1[i] - '0'));
		sort(a, a + n);//s[i] ascend, then t[i] ascend
		mnt = 0;
		for(int i = 1; i < n; i++)
			if(a[i].second < a[mnt].second)//get min t[i]
				mnt = i;
		memset(g, 0, sizeof(g));
		f[mnt] = 0;
		g[0] = a[mnt].second;
		int ptr = 0;//min ptr where g[ptr] >= s[i]
		int mxf = 0;//max f[i]
		for(int i = 0; i < n; i++)
		{
			if(i == mnt)
				continue;
			while(ptr <= mxf && g[ptr] < a[i].first)
				ptr++;
			if(ptr > mxf)
				return -1;//the graph is not connected
			f[i] = ptr + 1;//just one more post will do the job
			if(f[i] > mxf)//update them
				mxf = f[i];
			if(a[i].second > g[f[i]])
				g[f[i]] = a[i].second;
			//printf("%d: [%d,%d] f = %d\n", i, a[i].first, a[i].second, f[i]);
		}
		//for(int i = 0; i <= 10; i++)
		//	printf("g[%d] = %d\n", i, g[i]);
		for(int i = 0; i < n - 1; i++)
			t2[i] = max(a[i].second, f[i] ? g[f[i] - 1] : 0);//definition of t2[i]
		memset(h, 63, sizeof(h));
		h[0] = a[n - 1].first;
		ptr = 0;//min ptr where h[ptr] <= t2[seq[i]]
		int ans = f[n - 1];
		for(int i = 0; i < n - 1; i++)
			seq[i] = i;
		sort(seq, seq + n - 1, cmp);//t2[i] descend, then s[i] descend
		for(int i = 0; i < n - 1; i++)
		{
			while(h[ptr] > t2[seq[i]])
				ptr++;
			ans += ptr + f[seq[i]];
			if(a[seq[i]].first < h[ptr + 1])
				h[ptr + 1] = a[seq[i]].first;
			//printf("%d: [%d,%d] p = %d\n", seq[i], a[seq[i]].first, a[seq[i]].second, ptr);
		}
		//for(int i = 0; i <= 10; i++)
		//	printf("h[%d] = %d\n", i, h[i]);
		return ans - n + 1;//change posts to reposts; "+1": 'ptr' should +1 when (seq[i] == mnt) because it represents the number of reposts
	}
};

