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

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,goal[N],fir,sec,f;
map<vector<int>,pair<int,string> >mp;
string now,w[N];
void setin(string s) //找到了一个前半的字符串并塞入map 
{
		int i,j;
		vector<int>ans; ans.clear();
		for (i=0;i<n;++i)
		{
				int now=0;
				for (j=0;j<fir;++j) if (s[j]==w[i][j]) ++now;
				ans.pb(now);
		}
				if (mp.find(ans)==mp.end())
						mp[ans]=mk(1,s);
				else mp[ans].fi++;
}
void dfs(int x,string s)
{
		if (x>fir) setin(s);
		else 
		{
				int i;
				for (i=0;i<10;++i) dfs(x+1,s+(char)('0'+i));
		}
}
void findans(string s) //枚举一个后半字符串然后在map里记录答案 
{
		int i,j;
		vector<int>ans; ans.clear();
		for (i=0;i<n;++i)
		{
				int now=0;
				for (j=fir;j<fir+sec;++j) if (s[j-fir]==w[i][j]) ++now;
				ans.pb(goal[i]-now);
		}
		if (mp.find(ans)!=mp.end()) f+=mp[ans].fi,now=mp[ans].se+s;
}
void work(int x,string s)
{
		if (x>sec) findans(s);
		else 
		{
				int i;
				for (i=0;i<10;++i) work(x+1,s+(char)('0'+i));
		}
}
class EllysBulls{
	public:
		string getNumber(vector <string> guesses, vector <int> bulls)
		{
				n=guesses.size();
				m=guesses[0].length();
				for (i=0;i<n;++i) goal[i]=bulls[i],w[i]=guesses[i];
				fir=min(5,m); sec=m-fir; //考虑采用折半搜索的方法, 用一个vector记录下前半段确定后每个位置还差多少个确定位置,然后搜索后半进行询问 
				dfs(1,""); 
				work(1,"");
				if (f>1) return "Ambiguity";
				if (!f) return "Liar";
				return now;
		}
}MRT;

int main()
{
	 cout<<MRT.getNumber({"0000", "1111", "2222"},{2, 2, 2});
}

