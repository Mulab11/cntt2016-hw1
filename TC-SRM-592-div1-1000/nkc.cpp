#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#define N 51
using namespace std;
struct E
{long double s,x;};
E operator-(const E&x,const E&y)
{return (E)
{x.s-y.s,x.x-y.x};}
E operator+(const E&x,const E&y)
{return (E)
{x.s+y.s,x.x+y.x};}
E operator*(const E&x,const E&y)
{return (E)
{x.s*y.s-x.x*y.x,x.s*y.x+x.x*y.s};}
E operator-(const E&x)
{return (E)
{-x.s,-x.x};}
E omg[N];
E A[N],B[N],C[N];
int D[N],F[N];
int ans[N];
int n;
long double pi=acos(-1);
E kpf(E x)
{
	long double alpha=atan2(x.x,x.s)/2;
	long double l=sqrt(x.x*x.x+x.s*x.s);
	l=sqrt(l);
	return (E)
	{cos(alpha)*l,sin(alpha)*l};
}
void dfs(int x)
{
	if(2*x>n)
	{
		int i,j;
		for(i=0;i<n;i++)
		{
			C[i].s=C[i].x=0;
			E tmp=(E)
			{1,0};
			for(j=0;j<n;j++)
			{
				C[i]=C[i]+tmp*B[j];
				tmp=tmp*omg[i];
			}
			D[i]=(int)(C[i].s/n+0.4);
		}//求出当前方案下的原数列 
		for(i=1;i<n;i++)
		if(D[i]!=D[n-i]||D[i]<0) return;//检验是否满足题目要求 
		for(i=0;i<n;i++)
		{
			if(ans[i]<D[i]) return;//不比上一个解优就返回 
			if(ans[i]>D[i]) break;
		}
		for(i=0;i<n;i++)
		F[i]=0;
		for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		F[(i+j)%n]+=D[i]*D[j];
		for(i=0;i<n;i++)
		if(abs(A[i].s-F[i])>1e-6) return;//检验这个解是否正确 
		for(i=0;i<n;i++)
		ans[i]=D[i];//更新答案 
		return;
	}
	dfs(x+1);
	if(2*x==n||x==0)
	{
		B[x]=-B[x];
		dfs(x+1);
		B[x]=-B[x];
	}
	else
	{
		B[x]=-B[x];
		B[n-x]=-B[n-x];
		dfs(x+1);
		B[x]=-B[x];
		B[n-x]=-B[n-x];
	}
} 
struct SplittingFoxes2
{
	vector <int> getPattern(vector <int> amount)
	{
		vector<int>ret;
		int i,j;
		n=amount.size();
		for(i=0;i<n;i++)
		A[i].s=amount[i],A[i].x=0;
		for(i=0;i<n;i++)
		{
			omg[i].s=cos(2*pi*i/n);
			omg[i].x=sin(2*pi*i/n);
		}
		for(i=0;i<n;i++)
		{
			B[i].s=B[i].x=0;
			E tmp=(E)
			{1,0};
			for(j=0;j<n;j++)
			{
				B[i]=B[i]+tmp*A[j];
				tmp=tmp*omg[i];
			}
			B[i]=kpf(B[i]);
		}//先求出原数列的点值表达式 
		for(i=0;i<n;i++)
		{
			omg[i].s=cos(-2*pi*i/n);
			omg[i].x=sin(-2*pi*i/n);
		}
		for(i=0;i<n;i++)
		ans[i]=707185547;
		dfs(0);//暴力枚举所有可能方案 
		if(ans[0]==707185547) ret.push_back(-1);
		else
		{
			for(i=0;i<n;i++)
			ret.push_back(ans[i]);
		}
		return ret;
	}
};
/*SplittingFoxes2 P;
int main()
{
	vector<int>a,b;
	a.push_back(35198);
	a.push_back(27644);
	a.push_back(22185);
	a.push_back(26896);
	a.push_back(34136);
	a.push_back(26896);
	a.push_back(22185);
	a.push_back(27644);
	b=P.getPattern(a);
	for(int i=0;i<8;i++)
	cout<<b[i]<<' ';
}*/