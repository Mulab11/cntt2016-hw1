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

const int N=100000;

int ma[2*N+10],mi[2*N+10],b[2*N+10][2];
int x[55],y[55];

struct ConvexPolygonGame 
{
    string winner(vector <int> X, vector <int> Y)
    {
    	int n=X.size();
    	for (int i=0;i<n;i++) {x[i]=X[i];y[i]=Y[i];}
    	x[n]=x[0];y[n]=y[0];
    	for (int i=0;i<=2*N;i++) {mi[i]=N+1;ma[i]=-N-1;}
    	for (int i=0;i<n;i++)
    		if (x[i]==x[i+1]) //与y轴平行
    		{
   				mi[x[i]+N]=min(mi[x[i]+N],min(y[i],y[i+1])+1);
   				ma[x[i]+N]=max(ma[x[i]+N],max(y[i],y[i+1])-1);
    		}
    		else
    		{
    			bool ok=1;
    			if (x[i]>x[i+1]) {ok=0;swap(x[i],x[i+1]);swap(y[i],y[i+1]);}
    			for (int j=x[i];j<=x[i+1];j++)
    			{
    				ll t=ll(j-x[i])*(y[i+1]-y[i])+ll(x[i+1]-x[i])*y[i];
    				if (t>0)
    				{
    					ma[j+N]=max(ll(ma[j+N]),(j==x[i]||j==x[i+1] ? t-1 : t)/(x[i+1]-x[i]));
    					mi[j+N]=min(ll(mi[j+N]),(j==x[i]||j==x[i+1] ? t : t-1)/(x[i+1]-x[i])+1);
    				}
    				else
    					if (t<0)
    					{
    						ma[j+N]=max(ll(ma[j+N]),(j==x[i]||j==x[i+1] ? t : t+1)/(x[i+1]-x[i])-1);
    						mi[j+N]=min(ll(mi[j+N]),(j==x[i]||j==x[i+1] ? t+1 : t)/(x[i+1]-x[i]));
    					}
    					else
    					{
    						ma[j+N]=max(ma[j+N],(j==x[i]||j==x[i+1] ? -1 : 0));
    						mi[j+N]=min(mi[j+N],(j==x[i]||j==x[i+1] ? 1 : 0));
    					}
    			}
    			if (!ok) {swap(x[i],x[i+1]);swap(y[i],y[i+1]);}
    		}

    	int m=0;
    	for (int i=0;i<=2*N;i++)
    		for (int j=mi[i];j<=ma[i];j++)
    		{
    			b[++m][0]=i;b[m][1]=j;
    			if (m>2*N+1) return "Masha";//点数超过200001，必然不共线
    		}
    	for (int i=3;i<=m;i++)
    		if (ll(b[2][0]-b[1][0])*(b[i][1]-b[1][1])!=ll(b[2][1]-b[1][1])*(b[i][0]-b[1][0])) return "Masha";
    	return "Petya";
    }
};
