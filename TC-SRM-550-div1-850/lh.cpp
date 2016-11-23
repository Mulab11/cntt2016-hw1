#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class ConversionMachine{
	static const int maxn=20,mod=1000000007;
	
	int l;
	int num[maxn][maxn],top;
	int A[80][80],B[80][80],fz[80][80];
	
	void MOD(int &a){
		if (a>=mod) a-=mod;
	}
	
	void mul(int x[80][80],int y[80][80]){
		memset(fz,0,sizeof(fz));
		for (int i=0;i<=top;++i)
		for (int j=0;j<=top;++j) if (x[i][j])
		for (int k=0;k<=top;++k) if (y[j][k]) MOD(fz[i][k]+=(long long)x[i][j]*y[j][k]%mod);
		memcpy(x,fz,sizeof(fz));
		return;
	}
	
	public:
		int countAll(string word1, string word2, vector<int> costs, int maxCost){
			l=word1.length();
			int cnt[3]={0,0,0};
			int sum=0;
			for (int i=0;i<l;++i){
				int tmp=0;
				while(word1[i]!=word2[i]){
					tmp++;
					maxCost-=costs[word1[i]-'a'];
					word1[i]++;
					if (maxCost<0) return 0;
					if (word1[i]=='d') word1[i]='a';
				}
				sum+=tmp;
				cnt[tmp]++;
			}
			int t=0;
			for (int i=0;i<3;++i) t+=costs[i];
			sum+=maxCost/t*3;
			for (int i=0;i<=l;++i)
			for (int j=0;i+j<=l;++j) num[i][j]=top++;
			A[0][num[cnt[0]][cnt[1]]]=1;
			for (int i=0;i<=l;++i)
			for (int j=0;i+j<=l;++j){
				if (i) B[num[i][j]][num[i-1][j]]=i;
				if (j) B[num[i][j]][num[i+1][j-1]]=j;
				if (i+j<l) B[num[i][j]][num[i][j+1]]=l-i-j;
			}
			B[num[l][0]][top]=1;
			B[top][top]=1;
			while(sum){
				if (sum&1) mul(A,B);
				mul(B,B);
				sum>>=1;
			}
			return (A[0][num[l][0]]+A[0][top])%mod;
		}
};
