//   Author:Arturia
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<ctime>
#include<cstdlib>
#include<string>
#include<queue>
#include<cmath>
#include<set>
#include<map>
#include<bitset>
#include<vector>
#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>
using namespace std;
vector<string>ans;
string tmp;

/*
直接暴力生成即可
*/

void add(int now){
	if (now<10) tmp+='0'+now;
	else add(now/10),tmp+='0'+now%10;
}
struct FoxAndMp3{
	vector<string>playList(int n){
		int now=1;
		rep(i,1,min(n,50)){
			tmp.clear();add(now);tmp+=".mp3";
			ans.pb(tmp);
			if (now*10<=n) now*=10;
			else if (now<n){
				now++;
				while (now%10==0) now/=10;
			}
			else now=now/10+1;
		}
		return ans;
	}
};
