#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <vector>
#include <bitset>
#include <cstdio>
#include <string>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define REP(i,x,y)  for(int i=(int)x;i<=(int)y;i++)
#define FOR(i,x,y)  for(int i=(int)x;i< (int)y;i++)
#define PER(i,x,y)  for(int i=(int)x;i>=(int)y;i--)
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define md ((L+R)/2)
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int,int> PII;
const	int P=1e9+7;
const	int inf=1e9;
const	ll Inf=1e16;
const	int N=55;
const	int M=1<<16;

inline int IN(){
	char ch=getchar();int x=0,f=0;
	for(;ch<48||ch>57;ch=getchar()) f=ch=='-';
	for(;ch>=48&&ch<=57;ch=getchar()) x=(x<<1)+(x<<3)+ch-48;
	return f?(-x):x;
}

int Pow(int x,int y,int p){
	int a=1;
	for(;y;y>>=1,x=(ll)x*x%p) if(y&1) a=(ll)a*x%p;
	return a;
}

int n;
db x[N],y[N];
db pr[N];

db sqr(db x){
	return x * x;
}

db dist(int u, int v){
	return sqr(x[u] - x[v]) + sqr(y[u] - y[v]);
}

struct Constellation{
	db expectation(vector<int> a, vector<int> b, vector<int> prob){
		n = a.size();
		REP(i, 1, n) x[i] = a[i - 1];
		REP(i, 1, n) y[i] = b[i - 1];
		REP(i, 1, n) pr[i] = prob[i - 1] * .001;
		db ans = 0;
		REP(i, 1, n)
		REP(j, 1, n){
			if(i == j) continue;
			db prb = pr[i] * pr[j];
			REP(k, 1, n){
				if(k == i || k == j) continue;
				db cha = (x[j] - x[i]) * (y[k] - y[i]) - (x[k] - x[i]) * (y[j] - y[i]);
				if(cha == 0){
					if(max(dist(k, i), dist(k, j)) > dist(j, i)){
						prb *= (1 - pr[k]);
					}
				}else
				if(cha < 0) prb *= (1 - pr[k]);
			}
			ans += prb * (x[i] * y[j] - y[i] * x[j]);
		}
		return ans / 2;
	}
}stu;