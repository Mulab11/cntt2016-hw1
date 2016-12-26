#include <bits/stdc++.h>

using namespace std;

inline int solve(vector <string> f, int diff){
	int H=f.size(),W=f[0].size();
	if(H==1)return -1;
	int Ls[50][50]={{}}, Ps[50][50]={{}};
	// 前缀和
	for(int y=0; y<H; y++)
		for(int x=0; x<W; x++){
			Ls[y+1][x+1]=Ls[y][x+1]+Ls[y+1][x]-Ls[y][x]+(f[y][x]=='L');
			Ps[y+1][x+1]=Ps[y][x+1]+Ps[y+1][x]-Ps[y][x]+(f[y][x]=='P');
		}
	int res=-1;
	// 横向分界线
	for(int i=1; i<H; i++){
		int max1[2000]={};
		int max2[2000]={};
		fill(max1, max1+2000, -1);
		fill(max2, max2+2000, -1);
		// 上面的矩形
		for(int x1=0; x1<W; x1++)
			for(int x2=x1; x2<W; x2++)
				for(int y1=0; y1<i; y1++)
					for(int y2=y1; y2<i; y2++){
						int P=Ps[y2+1][x2+1]-Ps[y2+1][x1]-Ps[y1][x2+1]+Ps[y1][x1];
						int L=Ls[y2+1][x2+1]-Ls[y2+1][x1]-Ls[y1][x2+1]+Ls[y1][x1];
						max1[P-L+1000]=max(max1[P-L+1000], L+P);
					}
		// 下面的矩形
		for(int x1=0; x1<W; x1++)
			for(int x2=x1; x2<W; x2++)
				for(int y1=i; y1<H; y1++)
					for(int y2=y1; y2<H; y2++){
						int P=Ps[y2+1][x2+1]-Ps[y2+1][x1]-Ps[y1][x2+1]+Ps[y1][x1];
						int L=Ls[y2+1][x2+1]-Ls[y2+1][x1]-Ls[y1][x2+1]+Ls[y1][x1];
						max2[P-L+1000]=max(max2[P-L+1000], L+P);
					}
		// check一下是否合法
		for(int a=0; a<2000; a++)
			for(int b=0; b<2000; b++){
				if(max1[a]>=0 && max2[b]>=0 && abs(a+b-2000)<=diff){
					res=max(res, max1[a]+max2[b]);
				}
			}
	}
	return res;
}

struct FoxAndFlowerShopDivOne {
	int theMaxFlowers(vector <string> flowers, int maxDiff) {
		vector<string> rev(flowers[0].size(), string(flowers.size(), '.'));
		for(int i=0; i<flowers.size(); i++)
			for(int j=0; j<flowers[0].size(); j++)
				rev[j][i]=flowers[i][j];
		// 左右分离和上下分离的情况
		return max(solve(flowers, maxDiff), solve(rev, maxDiff));
	}
};