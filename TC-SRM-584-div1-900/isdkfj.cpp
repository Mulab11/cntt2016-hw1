#include <bits/stdc++.h>

using namespace std;

int f[105][105],g[1<<10][105];

class FoxTheLinguist {
public:
	int minimalHours(int n, vector <string> courseInfo) {
		string s;
		memset(f,0x3f,sizeof f);
		for(int i=0;i<courseInfo.size();++i)s+=courseInfo[i];
		for(int i=0;i<s.size();i+=12){
			int x=(s[i]-'A')*10+s[i+1]-'0',y=(s[i+4]-'A')*10+s[i+5]-'0',z=(s[i+7]-'0')*1000+(s[i+8]-'0')*100+(s[i+9]-'0')*10+s[i+10]-'0';
			f[x][y]=min(f[x][y],z);//数据里有重边 QAQ 
		}
		int N=n*10;
		for(int i=0;i<N;++i)f[i][i]=0;
		for(int i=0;i<n;++i){
			f[N][i*10]=0;//新建一个点，向所有0连边 
			for(int j=1;j<=9;++j)f[i*10+j][i*10+j-1]=0;//向上连边 
		}
		for(int k=0;k<=N;++k)
			for(int i=0;i<=N;++i)
				for(int j=0;j<=N;++j)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//floyd
		memset(g,0x3f,sizeof g);
		for(int i=0;i<=N;++i)g[0][i]=0;
		for(int i=0;i<n;++i)g[1<<i][i*10+9]=0;
		for(int s=0;s<1<<n;++s){
			for(int s0=s;s0>(s^s0);s0=(s0-1)&s)//枚举子集 
				for(int i=0;i<=N;++i)g[s][i]=min(g[s][i],g[s^s0][i]+g[s0][i]);
			for(int i=0;i<=N;++i)
				for(int j=0;j<=N;++j)//相同子集不同根的更新 
				if(g[s][i]>g[s][j]+f[i][j])g[s][i]=g[s][j]+f[i][j];
		}
		if(g[(1<<n)-1][N]==0x3f3f3f3f)return -1;
		return g[(1<<n)-1][N];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
