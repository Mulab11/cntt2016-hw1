#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int MaxN = 2000010;
char str[MaxN];
int lef[MaxN], rig[MaxN];
int *ans, *sum;
struct Data
{
	int r, p;
	bool operator < (const Data& D) const {return r > D.r;}
};

int range_sum(int l, int r)
{
	return l > 0 ? (sum[r] - sum[l - 1]) % mod : sum[r];
}

struct Range{int l, r; bool operator < (const Range& R) const {return l < R.l;}};
set<Range> helper;
set<Range>::iterator iter;
void insert(const int i)
{
	iter = helper.lower_bound((Range) {i, i});
	int l = i, r = i;
	if(iter != helper.end() 	&& iter->l == i + 1) 		r = iter->r;
	if(iter != helper.begin() 	&& (--iter)->r == i - 1)	l = iter->l;
	if(l != i) helper.erase(iter++); else if(iter != helper.end() && iter->l < i) ++iter;
	if(r != i) helper.erase(iter);
	helper.insert((Range) {l, r});
}

class WolfDelaymasterHard
{
public:
	int countWords(int N, int n0, int x0, int k0, int b0, int n1, int x1, int k1, int b1)
	{
		for( ; n0--; x0 = ((long long) k0 * x0 + b0) % N) str[x0 + 1] = '0';
		for( ; n1--; x1 = ((long long) k1 * x1 + b1) % N) str[x1 + 1] = '1';
		
		for(int i = 1; i <= N; ++i) lef[i] = (str[i] != '1' ? lef[i - 1] + 1 : 0);
		for(int i = N; i >= 1; --i) rig[i] = (str[i] != '0' ? rig[i + 1] + 1 : 0);
		
		ans = lef;
		sum = rig;
		ans[0] = sum[0] = 1;
		helper.insert((Range) {0, 0});
		priority_queue<Data> heap;
		
		int R;
		for(int i = 1; i <= N; ++i)
		{
#define dmin(a, b) ((a) < (b) ? (a) : (b))
			R = dmin(lef[i], rig[i + 1]);
			while(!heap.empty() && heap.top().r < i) insert(heap.top().p), heap.pop();
			ans[i] = 0;
			if((~i & 1))
			{
				iter = helper.begin();
				for(int l = iter->r + 1, r; l < i; l = iter->r + 1)
				{
					r = ((++iter == helper.end()) ? i : iter->l) - 1;
					(ans[i] += range_sum((l << 1) - i, (r << 1) - i)) %= mod;
					if(iter == helper.end()) break;
				}
			}
			heap.push((Data) {i + R, i});
			sum[i] = (ans[i] + sum[i - 1]) % mod;
		}
		return (ans[N] + mod) % mod;
	}
}	user;
