#include <bits/stdc++.h>

using namespace std;

const int mo=1000000009;
int f[305][305][3],n,s[305];

class TheExperiment {
public:
	int countPlacements(vector <string> intensity, int M, int L, int A, int B) {
		for(int i=0;i<intensity.size();++i)
			for(int j=0;j<intensity[i].size();++j){
				++n;
				s[n]=s[n-1]+intensity[i][j]-48;
			}
		f[0][0][0]=1;
		for(int i=1;i<=n;++i)
			for(int j=0;j<=M;++j){
				f[i][j][0]=(f[i-1][j][0]+f[i-1][j][1])%mo;//不放 
				if(j){
					for(int k=max(i-L,0);k<i;++k)
						if(s[i]-s[k]>=A&&s[i]-s[k]<=B)f[i][j][1]=(f[i][j][1]+f[k][j-1][1])%mo;
					if(i>=L&&s[i]-s[i-L]>=A&&s[i]-s[i-L]<=B){
						f[i][j][1]=(f[i][j][1]+f[i-L][j-1][0])%mo;
						f[i][j][1]=(f[i][j][1]+f[i-L][j-1][2])%mo;
					}//刚好放到 
					for(int k=max(i-L+1,0);k<i;++k)
					if(s[i]-s[k]>=A&&s[i]-s[k]<=B){
						f[i][j][2]=(f[i][j][2]+f[k][j-1][0])%mo;
						f[i][j][2]=(f[i][j][2]+f[k][j-1][2])%mo;
					}//多出来 
				}
			}
		return (f[n][M][0]+f[n][M][1])%mo;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
