#include <bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int mod=1e9+7;
int ti,n,cnt,l,r,num[20][20];
struct matrix{
	int a[120][120];
	void clear(){memset(a,0,sizeof(a));}
	void e(){clear();for(int i=0;i<=cnt;i++) a[i][i]=1;}
	void add(int x,int y,int z){a[x][y]=(a[x][y]+z)%mod;}
}one;
inline matrix operator * (matrix a,matrix b){
	matrix tmp;tmp.clear();
	for(int i=0;i<=cnt;i++)
		for(int j=0;j<=cnt;j++)
			for(int k=0;k<=cnt;k++)
				(tmp.a[i][j]+=(ll)a.a[i][k]*b.a[k][j]%mod)%=mod;
	return tmp;
}//矩阵乘法
inline matrix exp(matrix x,int y){
	matrix ans;ans.e();
	while(y){
		if(y&1) ans=ans*x;
		x=x*x;y>>=1;
	}
	return ans;
}//快速幂 

class ConversionMachine{
public:
	int countAll(string word1, string word2, vector <int> costs, int maxCost){
		l=r=cnt=ti=0;n=word1.length();
		one.clear();
		for(int i=0;i<n;i++){
			int a=word1[i]-'a',b=word2[i]-'a',si=0;
			while(a!=b){
				maxCost-=costs[a];
				if(maxCost<0) return 0;
				ti++;si++;
				a=(a+1)%3;
			}
			if(si==1) r++;
			if(si==2) l++;
		}//计算固定的操作代价 
		if(maxCost<0) return 0;//特判无解情况 
		ti+=maxCost/(costs[0]+costs[1]+costs[2])*3;//计算最大的可行次数 
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n-i;j++)
				num[i][j]=++cnt;
		for(int a=0;a<=n;a++)
			for(int b=0;b<=n-a;b++){
				int c=n-a-b;
				if(a) one.add(num[a-1][b+1],num[a][b],a);
				if(b) one.add(num[a][b-1],num[a][b],b);
				if(c) one.add(num[a+1][b],num[a][b],c);
			}//构建转移矩阵 
		one.add(0,1,1);
		one.add(0,0,1);//0表示方案总数
		matrix ans=exp(one,ti+1);
		return ans.a[0][num[l][r]];
	}
};