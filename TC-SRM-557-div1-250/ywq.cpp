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

struct FoxAndMountainEasy 
{
    string possible(int n, int h0, int hn, string history)
    {
    	int m=history.size();
    	int s=0;for (int i=0;i<m;i++) if (history[i]=='U') s++; else s--;
    	int t=hn-h0-s+n-m;
    	if (t%2==1) return "NO"; //parity check
    	t/=2;
    	if (t<0||t>n-m) return "NO";
    	int x=h0+t; //put all 'U' in front of history
    	for (int i=0;i<m;i++)
    	{
    		if (history[i]=='U') x++; else x--;
    		if (x<0) return "NO";
    	}
    	return "YES";
    }
};
