#include <bits/stdc++.h>

using namespace std;

int f[1<<12][131],su[1<<12];
void get(int&x,int y){if(x<y)x=y;}

class KeyDungeonDiv1 {
public:
	int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys) {
		int n=doorR.size();
		for(int i=0;i<n;++i)su[1<<i]=roomR[i]-doorR[i]+roomG[i]-doorG[i]+roomW[i];
		for(int i=1;i<(1<<n);++i)su[i]=su[i^(i&-i)]+su[i&-i];//子集和 
		memset(f,-1,sizeof f);
		f[0][keys[0]]=keys[2];//初始化 
		int ans=0,sum=keys[0]+keys[1]+keys[2];
		for(int s=0;s<(1<<n);++s)
			for(int R=0;R<=130;++R)if(f[s][R]>=0){
				int W=f[s][R],G=sum+su[s]-R-W;//每种钥匙个数 
				ans=max(ans,R+G+W);
				for(int i=0;i<n;++i)
				if(!(s&(1<<i))){
					if(R>=doorR[i]&&G>=doorG[i])
						get(f[s|(1<<i)][R-doorR[i]+roomR[i]],W+roomW[i]);
					if(R>=doorR[i]&&G<doorG[i]&&W+G>=doorG[i])
						get(f[s|(1<<i)][R-doorR[i]+roomR[i]],W+roomW[i]-doorG[i]+G);
					if(R<doorR[i]&&G>=doorG[i]&&W+R>=doorR[i])
						get(f[s|(1<<i)][roomR[i]],W+roomW[i]-doorR[i]+R);
					if(R<doorR[i]&&G<doorG[i]&&W+R+G>=doorR[i]+doorG[i])
						get(f[s|(1<<i)][roomR[i]],W+roomW[i]-doorR[i]+R-doorG[i]+G);
					//分情况转移 
				}
			}
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
