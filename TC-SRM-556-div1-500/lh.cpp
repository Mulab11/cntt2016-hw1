#include<vector>
#include<string>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class LeftRightDigitsGame2{
	private:
		static const int maxn=55;
		bool dp[maxn][maxn][2];
		string rec[maxn][maxn],mn[maxn];
		void min(string &a,const string&b){
			if (a=="") a=b;
			for (int i=0;i<a.length();++i) if (a[i]>b[i]){
				a=b;
				break;
			}
			else if (a[i]<b[i]) break;
			return;
		}
	
	public:
		string minNumber(string A, string B){
			int n=A.length();
			for (int i=0;i<n;++i)
			if (A[0]==B[i]){
				dp[0][i][0]=true;
//				printf("i=%d\n",i);
			}
			else if (A[0]>B[i]){
				dp[0][i][1]=true;
				rec[0][i]=A[0];
			}
			mn[0]=A[0];
			for (int i=1;i<n;++i){
				mn[i]=mn[i-1]+A[i];
				min(mn[i],A[i]+mn[i-1]);
			}
			for (int i=1;i<n;++i)
			for (int j=0;j<n-i;++j){
				if (dp[i-1][j][0]&&A[i]==B[j+i]) dp[i][j][0]=true;
				if (dp[i-1][j+1][0]&&A[i]==B[j]) dp[i][j][0]=true;
				if (dp[i-1][j][0]&&A[i]>B[j+i]){
					dp[i][j][1]=true;
					rec[i][j]=B.substr(j,i)+A[i];
				}
				if (A[i]>B[j]&&dp[i-1][j+1][0]){
					dp[i][j][1]=true;
					min(rec[i][j],A[i]+B.substr(j+1,i));
				}
				if (dp[i-1][j][1]){
					dp[i][j][1]=true;
					min(rec[i][j],rec[i-1][j]+A[i]);
				}
				if (A[i]>B[j]){
					dp[i][j][1]=true;
					min(rec[i][j],A[i]+mn[i-1]);
				}
				if (A[i]==B[j]&&dp[i-1][j+1][1]){
					dp[i][j][1]=true;
					min(rec[i][j],A[i]+rec[i-1][j+1]);
				}
//				printf("rec[%d][%d]=",i,j);
//				cout<<rec[i][j]<<endl;
			}
			if (dp[n-1][0][0]) return B;
			if (dp[n-1][0][1]) return rec[n-1][0];
			return "";
		}
};
