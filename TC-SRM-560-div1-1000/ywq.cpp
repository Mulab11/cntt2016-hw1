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

const double eps=1e-7;

bool a[15][15];
int b[15],c[15];
double val[15];
string s;

struct BoundedOptimization 
{
    double maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum)
    {
    	s="";
    	for (int i=0;i<expr.size();i++) s+=expr[i];
    	int l=s.size();
    	for (int i=0;i<l;i+=3)
    		a[s[i]-'a'][s[i+1]-'a']=a[s[i+1]-'a'][s[i]-'a']=1;
    	int n=lowerBound.size();double ans=0;
    	for (int i=0;i<(1<<n);i++)
    	{
    		int m1=0,m2=0;
    		for (int j=0;j<n;j++) if (i&(1<<j)) b[m1++]=j; else c[m2++]=j;
    		bool ok=1;
    		for (int j=0;j<m1;j++)
    			for (int k=j+1;k<m1;k++)
    				if (!a[b[j]][b[k]]) ok=0;
    		if (!ok) continue;
    		for (int j=0;j<(1<<m2);j++)
    		{
    			double res=maxSum;
    			for (int k=0;k<m2;k++)
    			{
    				if (j&(1<<k)) val[c[k]]=upperBound[c[k]]; else val[c[k]]=lowerBound[c[k]];
    				res-=val[c[k]];
    			}
    			if (res<-eps) continue; //the sum of vals can not exceed maxSum
    			double sum=0;
    			for (int k=0;k<m1;k++)
    			{
    				double adj=0;
    				for (int p=0;p<m2;p++) if (a[b[k]][c[p]]) adj+=val[c[p]];
    				val[b[k]]=adj+res/2;sum+=val[b[k]];
    			}
    			double delta=(res-sum)/m1;
    			bool ok=1;
    			for (int k=0;k<m1;k++)
    			{
    				val[b[k]]+=delta;
    				if (val[b[k]]<lowerBound[b[k]]-eps||val[b[k]]>upperBound[b[k]]+eps) ok=0;
    			}
    			if (!ok) continue; //illegal
    			double t=0;
    			for (int k=0;k<n;k++)
    				for (int p=k+1;p<n;p++)
    					if (a[k][p]) t+=val[k]*val[p];
    			ans=max(ans,t);
    		}
    	}
    	return ans;
    }
};
