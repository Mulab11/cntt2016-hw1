#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const double eps=1e-7;
const int N=200015;
int n,m;
struct node{int x,y;}p[N];

string lose="Petya",win="Masha";

bool contain(int x,int y,int k){
	if(x>y) swap(x,y);
	return x<=k&&k<=y;
}
bool insert(int x,int y){
	p[++m]=(node){x,y};
	if(m>=3&&(ll)(p[m].x-p[m-1].x)*(p[m-1].y-p[m-2].y)!=(ll)(p[m].y-p[m-1].y)*(p[m-1].x-p[m-2].x)) return 1;
	return 0;
}//插入点(x,y)并判断和前面点是否共线 
inline int fl(double x){
	if((int)x>x) return (int)x-1;
	return (int)x;
}

class ConvexPolygonGame{
public:
	string winner(vector <int> X, vector <int> Y){
		n=X.size();m=0;
		for(int i=-100000;i<=100000;i++){
			double low=100006,high=-100005;int l,h;
			for(int j=0;j<n;j++)
				if(contain(X[j],X[(j+1)%n],i)){
					double y=((ld)Y[j]*(X[(j+1)%n]-i)+(ld)Y[(j+1)%n]*(i-X[j]))/(ld)(X[(j+1)%n]-X[j]);
					low=min(low,y+(i==X[j]||i==X[(j+1)%n]));high=max(high,y-(i==X[j]||i==X[(j+1)%n]));
				}//计算横坐标为i的点的上下界 
			
			if(low-fl(low)>eps) l=fl(low)+1; else l=fl(low);
			if(fl(high)+1-high>eps) h=fl(high); else h=fl(high)+1;
			for(int j=l;j<=h;j++)
				if(insert(i,j)) return win;
		} 
		return lose;
	}
};
