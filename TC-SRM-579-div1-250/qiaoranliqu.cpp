#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,lcp[N][N],ans;
int get(string a,string b)
{
		int len=min(a.length(),b.length()),i;
		for (i=0;i<len;++i)
			if (a[i]!=b[i]) break;
		return i;
}
class UndoHistory{
	public:
		int minPresses(vector <string> lines)
		{
				n=lines.size();
				ans=n;
				for (i=0;i<n;++i) 
					for (j=0;j<n;++j) lcp[i][j]=get(lines[i],lines[j]);
				for (i=0;i<n;++i) //对于每次操作,假设前一个串是这个串的前缀,那么可以直接转移;否则一定是找一个最长前缀然后转移过来 
				{
						int now=2000000;
						if (i&&lcp[i-1][i]==lines[i-1].length()) now=lines[i].length()-lines[i-1].length();
						{
							int gg=0;
							for (j=0;j<i;++j) gg=max(gg,lcp[j][i]);
							now=min(now,(int)lines[i].length()-gg+2);
						}
						ans+=now;
				}
				return ans-2;
		}
}MRT;

int main()
{
	 cout<<MRT.minPresses({"absolutely", "abs", "absolute"});
}

