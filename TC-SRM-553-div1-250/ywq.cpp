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

ll a[55];
bool b[55];

struct Suminator 
{
    int findMissing(vector <int> program, int wantedResult)
    {
    	int n=program.size(),top=0;
        //program[i]=0
    	for (int i=0;i<n;i++)
    		if (program[i]<=0)
    		{
    			if (top>=2) {top--;a[top]+=a[top+1];}
    		}
    		else
    			a[++top]=program[i];
    	if (a[top]==wantedResult) return 0;
        //program[i]=x(x>0)
    	top=0;
    	for (int i=0;i<n;i++)
    		if (program[i]==0)
    		{
    			if (top>=2)
    			{
    				top--;a[top]+=a[top+1];b[top]|=b[top+1];
    			}
    		}
    		else
    			if (program[i]==-1)
    			{
    				a[++top]=0;b[top]=1;
    			}
    			else
    			{
    				a[++top]=program[i];b[top]=0;
    			}
    	if (!b[top])
    	{
    		if (a[top]==wantedResult) return 1; else return -1;
    	}
    	if (a[top]<wantedResult) return wantedResult-a[top]; else return -1;
    }
};
