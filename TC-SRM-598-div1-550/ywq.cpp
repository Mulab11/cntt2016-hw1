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

struct FoxAndFencing 
{
    string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d)
    {
    	if (mov1+rng1>=d)
    		return "Ciel";
    	else
    		if (mov2-mov1+rng2>=d)
    			return "Liss";
    		else
    			if (mov1>mov2&&rng1+mov1>mov2*2+rng2)
    				return "Ciel";
    			else
    				if (mov2>mov1&&rng2+mov2>mov1*2+rng1)
    					return "Liss";
    				else
    					return "Draw";
    }
};
