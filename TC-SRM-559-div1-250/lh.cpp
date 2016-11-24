#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class HyperKnight{
	int mov[8][2],use[2][100],top[2];
	int n,m;
	
	int check(int x,int y){
		int ret=0;
		for (int i=0;i<8;++i){
			int tx=x+mov[i][0],ty=y+mov[i][1];
			if (tx>=1&&tx<=n&&ty>=1&&ty<=m) ret++;
		}
		return ret;
	}
	
	public:
		long long countCells(int a, int b, int numRows, int numColumns, int k){
			long long ans=0;
			n=numRows;
			m=numColumns;
			ans=0;
			mov[0][0]=a;mov[0][1]=b;
			mov[1][0]=a;mov[1][1]=-b;
			mov[2][0]=-a;mov[2][1]=b;
			mov[3][0]=-a;mov[3][1]=-b;
			mov[4][0]=b;mov[4][1]=a;
			mov[5][0]=b;mov[5][1]=-a;
			mov[6][0]=-b;mov[6][1]=a;
			mov[7][0]=-b;mov[7][1]=-a;
			top[0]=top[1]=0;
			use[0][top[0]++]=1;
			use[0][top[0]++]=a+1;
			use[0][top[0]++]=b+1;
			use[0][top[0]++]=numRows-a+1;
			use[0][top[0]++]=numRows-b+1;
			sort(use[0],use[0]+top[0]);
			top[0]=unique(use[0],use[0]+top[0])-use[0];
			use[0][top[0]]=numRows+1;
			
			
			use[1][top[1]++]=1;
			use[1][top[1]++]=a+1;
			use[1][top[1]++]=b+1;
			use[1][top[1]++]=numColumns-a+1;
			use[1][top[1]++]=numColumns-b+1;
			sort(use[1],use[1]+top[1]);
			top[1]=unique(use[1],use[1]+top[1])-use[1];
			use[1][top[1]]=numColumns+1;
			
			for (int i=0;i<top[0];++i){
				for (int j=0;j<top[1];++j) if (check(use[0][i],use[1][j])==k)
				ans+=(long long)(use[0][i+1]-use[0][i])*(long long)(use[1][j+1]-use[1][j]);
			}
			return ans;
		}
};
