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

struct TheBrickTowerEasyDivOne 
{
    int find(int redCount, int redHeight, int blueCount, int blueHeight)
    {
    	int ans=min(redCount,blueCount);
    	if (redHeight==blueHeight) 
    		ans+=min(min(redCount,blueCount)+1,max(redCount,blueCount));
    	else
    		ans+=min(redCount,blueCount+1)+min(blueCount,redCount+1);
    	return ans;
    }
};
