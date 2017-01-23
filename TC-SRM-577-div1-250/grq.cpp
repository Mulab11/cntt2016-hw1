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

vi a,room[30];
vi make(vector<string> a){
	string s="";
	int now=0;
	vi res;res.clear();
	for(int i=0;i<a.size();i++) s+=a[i];
	for(int i=0;i<s.length();i++)
		if(s[i]>='0'&&s[i]<='9') now=now*10+s[i]-'0'; else res.pb(now),now=0;
	res.pb(now);
	return res;
}

class EllysRoomAssignmentsDiv1{
public:
	double getAverage(vector<string> ratings){
		a=make(ratings);
		int xhk=a[0],n=a.size(),r=n/20;
		if(n%20) r++;
		sort(a.begin(),a.end());
		reverse(a.begin(),a.end());
		double ans=0.0;
		for(int i=0;i<n;i+=r){
			int sum=0,isok=0,k=0;
			for(int j=0;j<r&&j+i<n;j++){
				if(a[i+j]==xhk) isok=1;
				sum+=a[i+j];k++;
			}
			if(isok){
				if(i+r<n) ans+=xhk;
				else ans=(ans+xhk)/((n+r-1)/r);
			}
			else{
			if(i+r<n) ans+=(double)sum/r;
			else if(i+r==n){
				ans+=(double)sum/r;
				ans/=(double)(n/r);
			}
			else
				ans=(double)k/r*((double)sum/k+ans)/(n/r+1)+(double)(r-k)/r*ans/(n/r);
			}
		}
		return ans;
	}
};

