/*
设状态st[0..2]表示相对最终状态还差i步的位置，那么事实上st[2]=n-st[0]-st[1]，所以不同的st只有n^2=121个。
我们可以很轻易的搞出st的转移（相当于选一个位置转能转到什么状态），转的最大个数也是确定的（因为转到目标状态后必然都是转一圈），
那么矩阵乘法就好了。
*/
#include <bits/stdc++.h>

using namespace std;
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 12,Mo = int(1e9) + 7;
const int MAXM = 225;
typedef int Matrix[MAXM][MAXM];

Matrix A,Tmp,B;
char S[MAXM],T[MAXM];
int c0,c1,c2,mc,n;

int Trans(char a,char b) //转移需要的费用
{
	if (a == 'a')
	{
		if (b == 'a') return 0;
		if (b == 'b') return c0;
		if (b == 'c') return c0 + c1;
	}
	if (a == 'b')
	{
		if (b == 'b') return 0;
		if (b == 'c') return c1;
		if (b == 'a') return c1 + c2;
	}
	if (a == 'c')
	{
		if (b == 'c') return 0;
		if (b == 'a') return c2;
		if (b == 'b') return c2 + c0;
	}
}

int Tr(char a,char b) //转移需要的步数
{
	if (a == 'a')
	{
		if (b == 'a') return 0;
		if (b == 'b') return 1;
		if (b == 'c') return 2;
	}
	if (a == 'b')
	{
		if (b == 'b') return 0;
		if (b == 'c') return 1;
		if (b == 'a') return 2;
	}
	if (a == 'c')
	{
		if (b == 'c') return 0;
		if (b == 'a') return 1;
		if (b == 'b') return 2;
	}
}

int Ord(int x,int y) {return x * (n + 1) + y;}

void Mul(Matrix &a,Matrix &b,Matrix &c) //矩阵乘法
{
	memset(Tmp,0,sizeof Tmp);
	int al = Ord(n,n);
	for(int i = 0;i <= al;i ++)
		for(int k = 0;k <= al;k ++)
			for(int j = 0;j <= al;j ++)
				Tmp[i][j] = (a[i][k] * 1ll * b[k][j] + Tmp[i][j]) % Mo;
	memcpy(c,Tmp,sizeof c);
}

int Cnt[3];

class ConversionMachine
{
public:
	int countAll(string S, string T, vector <int> costs, int mc)
	{
		int K,tim = 0;
		long long Min = 0;
		c0 = costs[0],c1 = costs[1],c2 = costs[2];
		n = S.length();
		for(int i = 0;i < n;i ++) Min += Trans(S[i],T[i]),tim += Tr(S[i],T[i]),Cnt[Tr(S[i],T[i])] ++;
		if (mc < Min) return 0;
		K = (mc - Min) / (c0 + c1 + c2) * 3 + tim; //总共要走k步
		for(int a = 0;a <= n;a ++)
			for(int b = 0;b <= n - a;b ++)
			{
				int u = Ord(a,b),c = n - a - b;
				if (a) A[u][Ord(a - 1,b)] = a;
				if (b) A[u][Ord(a + 1,b - 1)] = b;
				if (c) A[u][Ord(a,b + 1)] = c;
			}
		A[Ord(n,0)][Ord(n,n)] = 1;
		A[Ord(n,n)][Ord(n,n)] ++;
		for(int i = 0;i <= Ord(n,n);i ++) B[i][i] = 1;
		for(++ K;K;K >>= 1)
		{
			if (K & 1) Mul(B,A,B);
			Mul(A,A,A);
		}
		return B[Ord(Cnt[0],Cnt[1])][Ord(n,n)];
	}
};
