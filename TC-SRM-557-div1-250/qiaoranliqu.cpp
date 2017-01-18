#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 205
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,A[N];
class FoxAndMountainEasy{
		public:
			string possible(int n, int h0, int hn, string s)
			{
				 int len=s.size(),up=hn-h0,goal=0,rest=n-len,UP=0,DOWN=0;
				 for (i=0;i<len;++i) 
				 	  if (s[i]=='U') goal++;
				 	  else goal--;
				 up-=goal; goal=up;
				 if (rest-abs(goal)<0||((rest-abs(goal))&1)) return "NO";
				 if (goal>0) UP+=goal; else DOWN-=goal;
				 UP+=(rest-abs(goal))/2;
				 DOWN+=(rest-abs(goal))/2;
				 //计算出需要的u和d的数量 
				 for (i=1;i<=UP;++i) A[++A[0]]=1; //u放在前面 
				 for (i=0;i<len;++i) if (s[i]=='U') A[++A[0]]=1; 
				 else A[++A[0]]=-1;
				 for (i=1;i<=DOWN;++i) A[++A[0]]=-1; //d放在后面 
				 int now=h0;
				 for (i=1;i<=n;++i)  //判断是否为合法序列 
				 {
				 	now+=A[i];
				 	if (now<0) return "NO";
				 }
				 return "YES";
			}
}FFT;

int main()
{
	  cout<<FFT.possible(4,100000,100000,"DDU");
}

