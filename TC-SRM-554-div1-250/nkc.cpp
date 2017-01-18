#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<queue>
#include<map>
#include<bitset>
#include<stack>
#include<vector>
#include<set>
using namespace std;
#define MAXN 1010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define ll long long
#define eps 1e-8
struct TheBrickTowerEasyDivOne
{
	int find(int rc,int rh,int bc,int bh)
	{
		if(rh==bh)
		{//两种颜色高度不相等 
			return max(min(rc,bc-1),min(rc-1,bc))+1+min(rc,bc);;
		}
		return min(rc,bc-1)+1+min(rc-1,bc)+1+min(rc,bc);//相等 
	}
};

/*

*/