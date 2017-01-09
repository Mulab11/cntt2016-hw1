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

Vi A;
int res,n;

class EelAndRabbit{
public:
	int getmax(Vi l,Vi t){
		n=l.size();
		For(i,0,n){
			A.pb(t[i]);
			A.pb(t[i]+l[i]);
		}
		For(i,0,A.size())	//枚举两个时刻的鱼，计算答案
			For(j,0,A.size()){
				int tmp=0;
				For(k,0,n){
					if (t[k]<=A[i]&&A[i]<=t[k]+l[k]||t[k]<=A[j]&&A[j]<=t[k]+l[k]) tmp++;
				}
				res=max(res,tmp);
			}
		return res;
	}
} T;