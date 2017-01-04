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

string ans;
int a[26],b[26],c[55][26],d[55][26],f[26];

struct FoxAndHandle 
{
    string lexSmallestName(string S)
    {
    	int n=S.size();
    	for (int i=0;i<26;i++) b[i]=n;
    	for (int i=n-1;i>=0;i--)
    	{
    		int x=S[i]-97;
    		a[x]++;b[x]=i;
    		for (int j=0;j<26;j++) {c[i][j]=a[j];d[i][j]=b[j];}
    	}
    	ans="";int k=0;
    	for (int i=0;i<n/2;i++) //the string's length is at most n/2
    		for (int j=0;j<26;j++)
    			if (f[j]<a[j]/2)
    			{
    				int p=d[k][j];bool ok=1;
    				for (int q=0;q<26;q++) if ((f[q]+c[p][q])*2<a[q]) ok=0;
    				if (ok) {k=p+1;ans+=char(j+97);f[j]++;break;}
    			}
    	return ans;
    }
};
