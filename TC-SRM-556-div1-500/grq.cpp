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

int a[255];
bool dp[55][55][2][3];
string ans[55][55][2][3];

class LeftRightDigitsGame2{
public:
	string minNumber(string digits, string lowerBound){
		memset(a,0,sizeof(a));
		reverse(digits.begin(),digits.end());
		string s=lowerBound,d=digits;
		d=' '+d;s=' '+s;
		int n=s.size()-1;
		debug(n);
		memset(dp,0,sizeof(dp));
		dp[0][0][0][1]=1;
		ans[0][0][0][1]="";
		for(int i=0;i<=n;i++) ans[0][0][0][1]+=' ';
//		debuge;
		for(int i=1;i<=n+1;i++){
			for(int j=0;j<i;j++){
				for(int a=0;a<2;a++)
					for(int b=0;b<3;b++){
						if(!dp[i-1][j][a][b]) continue;
//						printf("%d %d %d %d\n",i-1,j,a,b);
//						cout<<ans[i-1][j][a][b]<<endl;
						if(i>n) continue;
						if(a||d[i]>=s[j+1]){
							int ta=a||(d[i]>s[j+1]);
							string tmp=ans[i-1][j][a][b];
							tmp[j+1]=d[i];
							if(!dp[i][j+1][ta][b]) ans[i][j+1][ta][b]=tmp; 
							else ans[i][j+1][ta][b]=min(ans[i][j+1][ta][b],tmp);
							dp[i][j+1][ta][b]=1;
						}
						int tb=b;
						if(d[i]<s[n-i+j+1]) tb=0;
						if(d[i]>s[n-i+j+1]) tb=2;
						
						string tmp=ans[i-1][j][a][b];
						tmp[n-i+j+1]=d[i];
//						debug(tmp);
						if(!dp[i][j][a][tb]) ans[i][j][a][tb]=tmp; 
						else ans[i][j][a][tb]=min(ans[i][j][a][tb],tmp);
						dp[i][j][a][tb]=1;
					}
			}
		}
		string res="";
		bool isok=0;
		for(int j=0;j<=n;j++){
			for(int b=0;b<3;b++)
				if(dp[n][j][1][b]){
					if(!isok) res=ans[n][j][1][b]; else res=min(res,ans[n][j][1][b]);
					isok=1;
				}
			for(int b=1;b<3;b++)
				if(dp[n][j][0][b]){
					if(!isok) res=ans[n][j][0][b]; else res=min(res,ans[n][j][0][b]);
					isok=1;
				}
		}
		debug(isok);
		if(!isok) return "";
		return res.substr(1);
	}
};
