#include<bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>
using namespace std;
vector<int>rating;
string s;
bool cmp(const int &a,const int &b){return a>b;}

/*
simple期望线性性
*/

class EllysRoomAssignmentsDiv1{
public:
	double getAverage(vector<string>ss){
		rep(i,0,ss.size()-1) s+=ss[i];
		for (int i=0;i<s.size();i+=5) rating.pb(s[i]*1000+s[i+1]*100+s[i+2]*10+s[i+3]-'0'*1111);
		int n=rating.size(),r=(n-1)/20+1,Elly=rating[0];
		sort(rating.begin(),rating.end(),cmp);
		double ans=0;
		int peo=n/r,rem=n%r;
		bool same=0;
		int sum=0;
		rep(j,n-rem,n-1){
			if (rating[j]==Elly) same=1;
			sum+=rating[j];
		}
		if (same){
			int sum=0;
			rep(i,0,n/r*r-1) sum+=rating[i];
			ans+=1.0*sum/(peo+1)/r;
			ans+=1.0*Elly/(peo+1);
		}
		else{
			ans+=1.0*sum/(peo+1)/r;
			for (int i=0;i+r<=n;i+=r){
				bool same=0;
				int sum=0;
				rep(j,i,i+r-1){
					if (rating[j]==Elly) same=1;
					sum+=rating[j];
				}
				if (same) ans+=1.0*Elly/(peo+1)*rem/r+1.0*Elly/peo*(r-rem)/r;
				else ans+=1.0*sum/r/(peo+1)*rem/r+1.0*sum/r/peo*(r-rem)/r;
			}
		}
		return ans;
	}
};
