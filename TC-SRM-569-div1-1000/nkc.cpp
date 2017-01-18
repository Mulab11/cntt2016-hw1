#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct matrix
{long long a[17][17];};
int D;
long long mod=1e9+9;
matrix tmp,st;
matrix operator*(const matrix &x,const matrix &y)//矩阵乘法 
{
	memset(tmp.a,0,sizeof(tmp.a));
	int i,j,k;
	for(i=0;i<=D;i++)
	for(j=0;j<=D;j++)
	for(k=0;k<=D;k++)
	(tmp.a[i][j]+=x.a[i][k]*y.a[k][j])%=mod;
	return tmp;
}
matrix ksm(matrix d,int c)
{
	matrix ret=st;
	while(c)
	{
		if(c&1) ret=ret*d;
		d=d*d;c/=2;
	}
	return ret;
}
matrix T[41];
struct MegaFactorial
{
	int countTrailingZeros(int N, int K, int B)
	{
		D=K;
		int fn=1,p;
		//对于所有的base分别处理 
		if(B==2) p=2;
		if(B==3) p=3;
		if(B==4) p=2,mod*=2,fn=2;
		if(B==5) p=5;
		if(B==6) p=3;
		if(B==7) p=7;
		if(B==8) p=2,mod*=3,fn=3;
		if(B==9) p=3,mod*=2,fn=2;
		if(B==10) p=5;
		int i,j;
		for(i=0;i<=D;i++)
		st.a[i][i]=1;//初始化单位矩阵 
		int TMP=p,cnt=0;
		T[0].a[0][0]=1;
		for(i=1;i<=D;i++)
		for(j=i;j<=D;j++)
		T[0].a[i][j]=1;
		while(TMP<=N)
		{
			cnt++;
			T[cnt]=ksm(T[cnt-1],p);
			for(i=1;i<=D;i++)
			T[cnt].a[0][i]++;
			TMP*=p;
		}//处理k次方项 
		TMP/=p;
		matrix di=st;
		while(N!=0)
		{
			if(TMP<=N)
			{
				while(TMP<=N)
				di=di*T[cnt],N-=TMP;
			}
			cnt--;
			TMP/=p;
		}
		return di.a[0][D]/fn;
	}
};