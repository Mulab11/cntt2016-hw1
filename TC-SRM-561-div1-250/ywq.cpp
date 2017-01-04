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

const int inf=1000000000;

int n1,n2,a[55],b[55];

int solve()
{
	int s=0;
	for (int i=1;i<=n1;i++) s+=a[i];
	for (int i=1;i<=n2;i++) s-=b[i];
	if (s<0) return inf;
	sort(a+1,a+n1+1);sort(b+1,b+n2+1);
	int ans=0;
	for (int i=n2;i;i--)
	{
		int k=n1-(n2-i);
		if (k>0) ans+=max(b[i]-a[k],0); else ans+=b[i];
	}
	return ans;
}

struct ICPCBalloons 
{
    int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted)
    {
    	int n=balloonSize.size(),m=maxAccepted.size(),ans=inf;
    	for (int i=0;i<(1<<m);i++) //enumerate the size of each problem's balloon
    	{
    		n1=0;n2=0;
    		for (int j=0;j<n;j++) if (balloonSize[j]=='M') a[++n1]=balloonCount[j];
    		for (int j=0;j<m;j++) if (!(i&(1<<j))) b[++n2]=maxAccepted[j];
    		int tmp=solve();
    		n1=0;n2=0;
    		for (int j=0;j<n;j++) if (balloonSize[j]=='L') a[++n1]=balloonCount[j];
    		for (int j=0;j<m;j++) if ((i&(1<<j))) b[++n2]=maxAccepted[j];
    		tmp+=solve();
    		ans=min(ans,tmp);
    	}
    	if (ans==inf) return -1; else return ans;
    }
};
