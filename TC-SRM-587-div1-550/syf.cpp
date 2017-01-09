//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#include<string>
#include<cstdio>
#include<cctype>
#include<cassert>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>

#define For(i,x,y) for (int i=x;i<y;i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> Vi;
typedef vector<string> Vs;

db res,tmp;

class TriangleXor{
public:
	int theArea(int w){
		res=0.5*w*(w+1);
		For(i,1,w+1){	//将计算的图形面积分成几个部分，分别计算，用相似三角形计算面积。
			tmp=w*(1-1.0*i/(w+i))*(w-i+1);
			i&1?res-=tmp:res+=tmp;
		}
		return int(res);
	}
} T;