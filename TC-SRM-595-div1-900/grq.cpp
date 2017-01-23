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

const int N=55;
const double eps=1e-9;
int n;
struct node{
	int x,y;
}p[N];
node operator - (node a,node b){
	a.x-=b.x;a.y-=b.y;
	return a;
}
int mul(node a,node b){
	return a.x*b.y-a.y*b.x;
}
int check(node a,node b,node c){
	return mul(b-a,c-a);
}
double dis(node a,node b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

class Constellation{
public:
	double expectation(vector <int> x, vector <int> y, vector <int> prob){
		n=x.size();
		for(int i=0;i<n;i++) p[i]=(node){x[i],y[i]};
		double ans=0.0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(i==j) continue;
				double res=mul(p[i],p[j]);
				for(int k=0;k<n;k++){
					if(i==k||j==k) continue;
					int t=check(p[i],p[k],p[j]);
					if(t<0) res*=(1000-prob[k])/1000.0;
					if(!t&&dis(p[i],p[j])+eps<dis(p[i],p[k])+dis(p[j],p[k])) res*=(1000-prob[k])/1000.0;
				}
				ans+=res*prob[i]*prob[j]/1000000.0;
			}
		return fabs(ans)/2;
	}
};
