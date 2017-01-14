#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int maxn=2000005;
const int M=1000000007;
class WolfDelaymasterHard
{
	public:
	int N;
	char s[maxn];
	int prew[maxn],preo[maxn],nexw[maxn],nexo[maxn];
	int ps2[maxn];
	int f[maxn];
	
	int sum(int l,int r)
	{
		if(l<0)exit(1);
		if(l>0)return (ps2[r]-ps2[l-2]+M)%M;
		return ps2[r];
	}
	
	void check(int a,int b)
	{
		int n=b-a;
		for(int i=1;i<=n/2;i++)
			if(s[a+i]=='o'||s[a+n/2+i]=='w')
			{
				cout<<a<<' '<<b<<endl;
				return;
			}
	}
	
	int work()
	{
		//It is simple to get a brute-force DP.
		//Let f[i] be the ways to fill out '?'s in first i positions and make it a valid word.
		//To transfer, we can enumerate j<i,
		//and check whether the interval [j+1,i] can be filled out as a word like ww...woo...o
		//If so we can transfer from f[j] to f[i]
		prew[0]=preo[0]=0;
		for(int i=1;i<=N+1;i++)
		{
			prew[i]=s[i]=='w'?i:prew[i-1];
			preo[i]=s[i]=='o'?i:preo[i-1];
		}
		nexw[N+1]=nexo[N+1]=N+1;
		for(int i=N;i>=0;i--)
		{
			nexw[i]=s[i]=='w'?i:nexw[i+1];
			nexo[i]=s[i]=='o'?i:nexo[i+1];
		}
		f[0]=1;
		ps2[0]=1;
		//We use some tricks to make the time complexity of transform under O(log n)
		for(int i=2;i<=N;i+=2)
		{
			int mx=i-prew[i];
			mx=min(mx,(i-preo[prew[i]])/2);//...o(...w...s[i])
			//mx means the most number of 'o's that end at i
			int j=1,k;
			while(j<=mx)
			{
				k=(i-preo[i-j])/2;//...o(...s[j]...i)
				//Let t be the position of last 'o' before i-j
				//we want the last ww...woo...o on the right of t,
				//and we can get k as the most number of the last consecutive 'o's
				k=min(k,mx);
				//We can choose the number of the last consecutive 'o's in interval [j,k]
				if(k>=j)
				{
					//We should add \sum_{p=j}^k f[i-2p] to f[i], we can do it O(1) with prefix-sum array.
					(f[i]+=sum(i-k-k,i-j-j))%=M;
					//for(int p=j;p<=k;p++)
					//	check(i-p-p,i);
					j=i-preo[i-j]+1;
					//The interval [i-j-j+1,i-j] must only contain '?', so j must become twice of itself. 
				}
				else
				{
					j=nexo[i-j-j];
					j=i-j+1;
					//Any two consecutive operations will make j multiply.
				}
				//We can prove that this loop must be runned no more than O(log n) times.
			}
			//Maintain the prefix-sum array
			ps2[i]=(f[i]+ps2[i-2])%M;
		}
		return f[N];
	}
	
	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
	{
		for(int i=1;i<=N;i++)
			s[i]='?';
		LL x = w0;
		for(int i=0;i<wlen;i++){
			s[x+1] = 'w';				// Rewrite the x-th (0-based) character of s
			x = (x * wmul + wadd) % N;
		}
		x = o0;
		for(int i=0;i<olen;i++){
			s[x+1] = 'o';				// Rewrite the x-th (0-based) character of s
			x = (x * omul + oadd) % N;
		}
		//Above is getting the string
		this->N=N; 
		return work();
	}
	
	int countWords_(string ss)
	{
		N=ss.size();
		for(int i=1;i<=N;i++)
			s[i]=ss[i-1];
		return work();
	}
	
};

