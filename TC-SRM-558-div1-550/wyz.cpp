// BEGIN CUT HERE

// END CUT HERE
#line 5 "Ear.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
string st;int stamp;
inline int get_char(){
	if (stamp==st.size()) return -1;
	return st[stamp++];
}
inline int read(){
	int ret=0;char ch=get_char();
	while (ch<'0'||ch>'9') ch=get_char();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=get_char();
	}
	return ret;
}
void Input(vector<string> &_s,int *a,int &n){
	st="";
	for (int i=0;i<_s.size();++i) st+=_s[i];
	stamp=0;n=0;
	while (stamp<st.size()) a[n++]=read();
}


const int maxm=1e4;
const int maxn=305;

class Ear{
	int red[maxm+7];
	int count(int l,int r){
		if (l<1) l=1;
		if (r>maxm) r=maxm;
		return red[r]-red[l-1];
	}
	int x[maxn],y[maxn],n;
	public:
	long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY){
		Input(redX,x,n);
		memset(red,0,sizeof(red));
		for (int i=0;i<n;++i) ++red[x[i]];
		for (int i=1;i<=maxm;++i) red[i]+=red[i-1];
		Input(blueX,x,n);
		Input(blueY,y,n);
		ll ret=0;
		for (int i=0;i<n;++i)for (int j=0;j<n;++j)if (y[i]>y[j]){
			int l=(x[j]-x[i])*y[i]/(y[i]-y[j])+x[i],r=x[i];
			if (l>r) swap(l,r);
			int cnt0=count(1,x[j]-1),cnt1=count(l,x[j]-1);
			int cnt2=count(x[j]+1,maxm),cnt3=count(x[j]+1,r);
			ret+=1LL*(cnt0*(cnt0-1)/2-cnt1*(cnt1-1)/2)*(cnt2*(cnt2-1)/2-cnt3*(cnt3-1)/2);
		}
		return ret;
	}
};
