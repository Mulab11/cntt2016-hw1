#include <bits/stdc++.h>

using namespace std;

const int mo=1e9+7;
typedef long long LL;
int n,m,cost[3][3],pa[12][12],a[105][105],b[105][105];
void mul(int (*a)[105],int (*b)[105]){//矩阵乘法 
	static int c[105][105];
	memset(c,0,sizeof c);//清零 
	for(int i=1;i<=m;++i)
		for(int k=1;k<=m;++k)
			for(int j=1;j<=m;++j)
			c[i][j]=(c[i][j]+LL(a[i][k])*b[k][j])%mo; 
	memcpy(a,c,sizeof c);//复制 
}

class ConversionMachine {
public:
	int countAll(string word1, string word2, vector <int> costs, int maxCost) {
		n=word1.size();
		cost[0][1]=costs[0];cost[0][2]=costs[0]+costs[1];
		cost[1][0]=costs[1]+costs[2];cost[1][2]=costs[1];
		cost[2][0]=costs[2];cost[2][1]=costs[2]+costs[0];
		LL sum=0,res=0;int d1=0,d2=0;
		for(int i=0;i<n;++i){
			sum+=cost[word1[i]-'a'][word2[i]-'a'];//计算最小花费 
			if(word1[i]==word2[i]);
			else if(word1[i]+1==word2[i]||(word1[i]=='c'&&word2[i]=='a'))++res,++d1;
			else res+=2,++d2;//记录初始状态 
		}
		if(maxCost<sum)return 0;
		res+=3*(maxCost-sum)/(LL(costs[0])+costs[1]+costs[2]);//计算实际的次数 
		for(int i=0;i<=n;++i)
			for(int j=0;i+j<=n;++j)pa[i][j]=++m;
		for(int i=0;i<=n;++i)
			for(int j=0;i+j<=n;++j){
				if(j)a[pa[i][j]][pa[i+1][j-1]]=j;
				if(i)a[pa[i][j]][pa[i-1][j]]=i;
				if(i+j<n)a[pa[i][j]][pa[i][j+1]]=n-i-j;//构造转移矩阵 
			}
		a[1][++m]=1;a[m][m]=1;//添加辅助点和自环 
		for(int i=1;i<=m;++i)b[i][i]=1;//单位矩阵 
		for(++res;res;res>>=1){//矩阵快速幂 
			if(res&1)mul(b,a);
			mul(a,a);
		}
		return b[pa[d1][d2]][m];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
