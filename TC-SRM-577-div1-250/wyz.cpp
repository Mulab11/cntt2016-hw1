// BEGIN CUT HERE

// END CUT HERE
#line 5 "EllysRoomAssignmentsDiv1.cpp"
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


const int maxn=505;

class EllysRoomAssignmentsDiv1{
	int a[maxn],n;
	public:
	double getAverage(vector <string> ratings){
		st="";
		for (int i=0;i<ratings.size();++i) st+=ratings[i];
		stamp=0;
		n=0;
		while (stamp<st.size()) a[n++]=read();
		int elly=a[0];
		sort(a,a+n,greater<int>());
		int r=(n-1)/20+1,m=0;
		double ret=0;
		for (int i=0;i<n;i+=r){
			double sum=0;
			for (int j=i;sum>=0&&j<i+r;++j)
				if (j>=n) sum+=ret/m;
				else if (a[j]==elly) sum=-1;
				else sum+=a[j];
			++m;
			if (sum<0) ret+=elly;
			else ret+=sum/r;
		}
		return ret/m;
	}
};
