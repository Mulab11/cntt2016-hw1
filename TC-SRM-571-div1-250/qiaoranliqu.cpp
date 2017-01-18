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
#include<stdlib.h>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k;
vector<string>ans;
void dfs(long long x) //直接按照字典序最小值搜出前50优的解即可. 
{
	int i;
	if (x>n||(int)ans.size()>=50) return;
	string s;
	for (i=x;i;i/=10) s+='0'+i%10;
	reverse(s.begin(),s.end());
	ans.pb(s+".mp3");
	for (i=0;i<10;++i) dfs(x*10+i);
}
class FoxAndMp3{
	public:
		vector <string> playList(int n)
		{
				::n=n;
				for (i=1;i<10;++i)
				dfs(i);
				return ans;
		}
};
