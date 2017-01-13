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

int n,m;
string ans;

struct node
{
	int key;
	int d[50];
	bool operator <(node a)const
	{
		for (int i=0;i<n;i++)
		{
			if (d[i]<a.d[i]) return 1;
			if (d[i]>a.d[i]) return 0;
		}
		return 0;
	}
};

node a[10010],c;
int b[10];

struct EllysBulls 
{
    string getNumber(vector <string> guesses, vector <int> bulls)
    {
    	n=guesses.size();m=guesses[0].size();
    	int l=min(m,4),t=1;
    	for (int i=0;i<l;i++) t*=10;
    	for (int i=0;i<t;i++)
    	{
    		int tt=i;a[i].key=i;
    		for (int j=0;j<l;j++) {b[j]=tt%10;tt/=10;}
    		for (int j=0;j<n;j++)
    		{
    			a[i].d[j]=0;
    			for (int k=0;k<l;k++) if (b[k]==guesses[j][k]-'0') a[i].d[j]++;
    		}
    	}
    	sort(a,a+t);
    	int l2=m-l,t2=1;
    	for (int i=0;i<l2;i++) t2*=10;
    	int cnt=0;
    	for (int i=0;i<t2;i++)
    	{
    		int tt=i;
    		for (int j=0;j<l2;j++) {b[j]=tt%10;tt/=10;}
    		bool ok=1;
    		for (int j=0;j<n;j++)
    		{
    			c.d[j]=bulls[j];
    			for (int k=0;k<l2;k++) if (b[k]==guesses[j][k+l]-'0') c.d[j]--;
    			if (c.d[j]<0) {ok=0;break;}
    		}
    		if (!ok) continue;
    		int l0=lower_bound(a,a+t,c)-a,r0=upper_bound(a,a+t,c)-a;
    		cnt+=r0-l0;
    		if (cnt>=2) return "Ambiguity";
    		if (r0-l0)
    		{
    			int tt=a[l0].key;ans="";
    			for (int j=0;j<l;j++) {ans+=char(tt%10+48);tt/=10;}
    			tt=i;
    			for (int j=0;j<l2;j++) {ans+=char(tt%10+48);tt/=10;}
    		}
    	}
    	if (cnt) return ans; else return "Liar";
    }
};
