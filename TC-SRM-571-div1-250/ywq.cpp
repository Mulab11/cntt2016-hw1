#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

vector<string> ans;
int cnt,a[15];

bool dfs(int l,int n)
{
	ll d=0;
	for (int i=1;i<=l;i++) d=d*10+a[i];
	if (d>n) return 0;
	cnt++;string s="";
	for (int i=1;i<=l;i++) s+=char(a[i]+48);
	s+=".mp3";
	ans.pb(s);
	if (cnt==50) return 1;
	for (int i=0;i<10;i++)
	{
		a[l+1]=i;if (dfs(l+1,n)) return 1;
	}
	return 0;
}

struct FoxAndMp3 
{
    vector <string> playList(int n)
    {
    	cnt=0;
    	for (int i=1;i<=9;i++)
    	{
    		a[1]=i;
    		if (dfs(1,n)) break;
    	}
    	return ans;
    }
};
