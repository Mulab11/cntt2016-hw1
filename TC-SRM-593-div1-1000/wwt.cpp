#include <bits/stdc++.h>

using namespace std;

const int maxn = 2000005,mo = int(1e9) + 7;

int final[maxn],nex[maxn];
int a[2][maxn];
int righ[maxn],f[maxn],n;
char s[maxn];

class WolfDelaymasterHard
{
public:	
	void add(int p,int v)
	{
		int *b = a[p & 1];
		if (!p) b[p] = (b[p] + v) % mo; else //p=0时树状数组会有bug
			for(;p;p -= p & -p) b[p] = (b[p] + v) % mo;
	}

	int query(int *b,int p)
	{
		p = max(p,0);
		int tmp = 0;
		if (!p) tmp = b[0],++ p;
		for(;p <= n;p += p & -p) tmp = (tmp + b[p]) % mo;
		return tmp;
	}

	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
	{
		n = N;
		long long x = w0;
		for(int i = 0;i < wlen;i ++)
		{
			s[x] = 'w';
			x = (x * wmul + wadd) % n;
		}
		x = o0;
		for(int i = 0;i < olen;i ++)
		{
			s[x] = 'o';
			x = (x * omul + oadd) % n;
		}
		//显然一个合法的s相当于一些((((()))))拼在一起
		//令f[i]表示以i为某个(((())))的结尾的方案数，那么答案就是f[n]
		//f[i]=\sum_{j,(i,j]可以是一段合法的((()))} f_j
		//考虑怎么的j是合法的
		//那么必有(i-j) mod 2 = 0,j<i，令right[j]表示距离j最近（且>j）的右括号，不存在则标记为n+1,left[i]表示距离i最近的左括号，不存在标记为0
		//那么有right[j]>(i+j)/2,left[i]<=(i+j)/2，可得：2left[i]-i<=j,2right[j]>i
		//因此，我们可以在求出f[j]后，在j位置+f[j]，当i移动到2right[j]时，再在2right[j]在j位置-f[j]
		//然后对于f[i]，相当于对2left[i]-i求后缀和，用树状数组即可。
		//事实上，由于right[j]是递增的，因此，对于每个i，合法的j都是一段连续的区间，求f[j]时维护前缀和就可以不用树状数组了。
		for(int i = n;i;i --) s[i] = s[i - 1];//make the string starts at 1
		for(int i = n,po = n + 1;i >= 0;i --)//求出right[j]
		{
			righ[i] = po;
			if (s[i] == 'o') po = i;
			righ[i] = min(n + 1,2 * righ[i] - i);
			nex[i + 1] = final[righ[i]],final[righ[i]] = i + 1;
		}
		f[0] = 1;
		add(0,1);
		for(int i = 1,lst = 0;i <= n;i ++) //lst表示left[i]
		{
			for(int j = final[i];j;j = nex[j]) add(j - 1,-f[j - 1]);
			if (s[i] == 'w') lst = i;
			f[i] = query(a[i & 1],2 * lst - i); //i和j奇偶性要相同
			add(i,f[i]);
		}
		return (f[n] + mo) % mo;
	}
};
