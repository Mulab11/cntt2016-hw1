#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<iostream>

#define N 200005

using namespace std;
const int inf=(int)1e9;
int n,i,a[N],f[N],j,k;
int get(long long sum)//判断当前数是否合法
{
	   while (sum%5==0) sum/=5;
	   if (sum>1) return 0;
	   return 1;
}
class CuttingBitString{
public:
int getmin(string s)
{
	  n=s.length();
	  for (i=0;i<n;++i) a[i+1]=s[i]-'0';
	  memset(f,60,sizeof(f));
	  f[0]=0;
	  for (i=1;i<=n;++i)//枚举右端点
	    for (j=0;j<i;++j)//枚举左端点
	      if (f[j]<inf&&a[j+1]!=0)
		{
		        long long sum=0;
				for (k=j+1;k<=i;++k) sum=(sum*2+a[k]); 
				if (sum>1&&!get(sum)) continue; 
				f[i]=min(f[i],f[j]+1);
		}
	 if (f[n]>inf) return -1; //判断是否有合法解
	 return f[n];
}
}A;
string s;
int main()
{
	    cin>>s;
		A.getmin(s);
}