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

const int di[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

bool ok[2510][2510];

struct RotatingBot 
{
    int minArea(vector <int> moves)
    {
    	int n=moves.size(),x=1251,y=1251;
    	ok[x][y]=1;
    	int x0=-10000,x1=10000;
    	int y0=-10000,y1=10000;
    	for (int i=0;i<n;i++)
    	{
    		for (int j=0;j<moves[i];j++)
    		{
    			x+=di[i%4][0];y+=di[i%4][1];
    			if (ok[x][y]) return -1;//the robot visits the same cell twice
    			ok[x][y]=1;
    		}
    		if (x<x0||x>x1||y<y0||y>y1) return -1;//the robot oversteps the boundary
    		if (i==n-1) break;
    		if (!ok[x+di[i%4][0]][y+di[i%4][1]]) //update the boundary
    		{
    			if (i%4==0) {if (x1!=10000&&x!=x1||x<1251) return -1;x1=x;}
    			if (i%4==1) {if (y1!=10000&&y!=y1||y<1251) return -1;y1=y;}
    			if (i%4==2) {if (x0!=-10000&&x!=x0||x>1251) return -1;x0=x;}
    			if (i%4==3) {if (y0!=-10000&&y!=y0||y>1251) return -1;y0=y;}
    		}
    	}
        //calculate the answer
    	x0=y0=2510;x1=y1=0;
    	for (int i=0;i<=2502;i++)
    		for (int j=0;j<=2502;j++)
    			if (ok[i][j])
    			{
    				x0=min(x0,i);y0=min(y0,j);
    				x1=max(x1,i);y1=max(y1,j);
    			}
    	return (x1-x0+1)*(y1-y0+1);
    }
};
