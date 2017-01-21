// BEGIN CUT HERE

// END CUT HERE
#line 5 "LeftRightDigitsGame2.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;


const int maxn=55;

class LeftRightDigitsGame2 {
	bool have_a(const string &_s){
		for (auto i:_s) if (i=='a') return 1;
		return 0;
	}
	string dp[maxn][maxn],mn[maxn][maxn],mx[maxn][maxn];
	string st[maxn][maxn];
	int n;
	public:
	string minNumber(string digits, string lowerBound){
		n=digits.size();
		for (int i=0;i<n;++i){
			mn[i][i]=digits[0];
			if (digits[0]>=lowerBound[i]) dp[i][i]=mn[i][i];
			else dp[i][i]="a";
			if (digits[0]>lowerBound[i]) mx[i][i]=mn[i][i];
			else mx[i][i]="a";
			st[i][i]=lowerBound[i];
			for (int j=i+1;j<n;++j)
				st[i][j]=st[i][j-1]+lowerBound[j];
		}
		for (int len=1;len<n;++len)
			for (int i=0,j;(j=i+len)<n;++i){
				mn[i][j]=min(mn[i][j-1]+digits[len],digits[len]+mn[i+1][j]);
				dp[i][j]="a";
				string tmp;
				if ((tmp=digits[len]+mn[i+1][j])>=st[i][j])if (!have_a(tmp))dp[i][j]=min(dp[i][j],tmp);
				if ((tmp=digits[len]+dp[i+1][j])>=st[i][j])if (!have_a(tmp))dp[i][j]=min(dp[i][j],tmp);
				if ((tmp=digits[len]+mx[i+1][j])>=st[i][j])if (!have_a(tmp))dp[i][j]=min(dp[i][j],tmp);
				if ((tmp=dp[i][j-1]+digits[len])>=st[i][j])if (!have_a(tmp))dp[i][j]=min(dp[i][j],tmp);
				if ((tmp=mn[i][j-1]+digits[len])>=st[i][j])if (!have_a(tmp))dp[i][j]=min(dp[i][j],tmp);
				if ((tmp=mx[i][j-1]+digits[len])>=st[i][j])if (!have_a(tmp))dp[i][j]=min(dp[i][j],tmp);
				
				mx[i][j]="a";
				if ((tmp=digits[len]+mn[i+1][j])>st[i][j])if (!have_a(tmp))mx[i][j]=min(mx[i][j],tmp);
				if ((tmp=digits[len]+dp[i+1][j])>st[i][j])if (!have_a(tmp))mx[i][j]=min(mx[i][j],tmp);
				if ((tmp=digits[len]+mx[i+1][j])>st[i][j])if (!have_a(tmp))mx[i][j]=min(mx[i][j],tmp);
				if ((tmp=dp[i][j-1]+digits[len])>st[i][j])if (!have_a(tmp))mx[i][j]=min(mx[i][j],tmp);
				if ((tmp=mn[i][j-1]+digits[len])>st[i][j])if (!have_a(tmp))mx[i][j]=min(mx[i][j],tmp);
				if ((tmp=mx[i][j-1]+digits[len])>st[i][j])if (!have_a(tmp))mx[i][j]=min(mx[i][j],tmp);
//				if (have_a(dp[i][j])) dp[i][j]="a";
			}
//		for (int i=0;i<n;++i)for (int j=i;j<n;++j)cout<<i<<' '<<j<<' '<<dp[i][j]<<endl;
		if (have_a(dp[0][n-1])) return "";
		return dp[0][n-1];
	}
};
