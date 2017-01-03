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

int a[310],b[310],c[310];
string s1,s2,s3;

struct Ear 
{
    long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY)
    {

        // turn strings to arrays

    	s1="";s2="";s3="";
    	for (int i=0;i<redX.size();i++) s1+=redX[i];
    	for (int i=0;i<blueX.size();i++) s2+=blueX[i];
    	for (int i=0;i<blueY.size();i++) s3+=blueY[i];
    	int d=0;
    	n=0;int l1=s1.size();
    	for (int i=0;i<=l1;i++)
    		if (i==l1||s1[i]==' ')
    		{
    			a[n++]=d;d=0;
    		}
    		else
    			d=d*10+s1[i]-'0';
    	m=0;int l2=s2.size();
    	for (int i=0;i<=l2;i++)
    		if (i==l2||s2[i]==' ')
    		{
    			b[m++]=d;d=0;
    		}
    		else
    			d=d*10+s2[i]-'0';
    	m=0;int l3=s3.size();
    	for (int i=0;i<=l3;i++)
    		if (i==l3||s3[i]==' ')
    		{
    			c[m++]=d;d=0;
    		}
    		else
    			d=d*10+s3[i]-'0';

    	sort(a,a+n);
    	ll ans=0;
    	for (int i=0;i<m;i++) //P
    		for (int j=0;j<m;j++) //Q
    			if (c[i]>c[j])
    			{
    				int r1=lower_bound(a,a+n,min(b[i],b[i]-(b[i]-b[j])*c[i]/(c[i]-c[j])))-a; //A
    				int r2=lower_bound(a,a+n,b[j])-a; //B
    				int t=(r2*2-r1-1)*r1/2;
    				int l1=a+n-upper_bound(a,a+n,max(b[i],b[i]+(b[j]-b[i])*c[i]/(c[i]-c[j]))); //D
    				int l2=a+n-upper_bound(a,a+n,b[j]); //C
    				t=t*((l2*2-l1-1)*l1/2);
    				ans+=t;
    			}
    	return ans;
    }
};
