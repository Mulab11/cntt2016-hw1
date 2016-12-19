#include<cstdio>
#include<algorithm>
#include<string>
char f[333]={},g[31333]={};
int ans=1,size,n;
using namespace std;
int findzuo(int a,char b)//找到左面颜色相同的
{
	if(a<0||a>=size)
		return -10000;
	for(int i=a;i>=0;i--)
		if(g[i]==b)
			return i;
	return -10000;
}
int findyou(int a,char b)//找到右边颜色相同的
{
	if(a<0||a>=size)
		return 10000;
	for(int i=a;i<size;i++)
		if(g[i]==b)
			return i;
	return 10000;
}
class ColorfulChocolates {
  public:
    int maximumSpread(string chocolates, int maxSwaps)
	{
		size=chocolates.size();
		for(int i=0;i<size;i++)
			f[i]=chocolates[i];
		n=maxSwaps;
		for(int i=0;i<size;i++)//枚举每一个基准点
		{
			int m=n,tou=i-1,wei=i+1;
			for(int j=0;j<size;j++)
				g[j]=f[j];
			while(tou>=0||wei<size)
			{
				int x=findzuo(tou,g[i]),y=findyou(wei,g[i]);
				m-=min(tou-x,y-wei);
				if(m<0)//判断剩余交换次数
					break;
				if(tou-x<y-wei)
					g[x]=1,tou--;
				else
					g[y]=1,wei++;
			}
			if(ans<wei-tou-1)
				ans=wei-tou-1;
		}
		return ans;
	}
};
