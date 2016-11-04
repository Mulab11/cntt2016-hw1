#include <bits/stdc++.h>

std::vector<int> h,a;

bool cmp(int i,int j)//以数值为第一关键字递增，序号为第二关键字递增排序 
{
	if(h[i]!=h[j])return h[i]<h[j];
	return i<j;
}

class TheBrickTowerMediumDivOne
{
	public:
		std::vector<int> find(std::vector<int> height) 
		{
			h=height;
			a.resize(h.size());
			int j=-1;
			for(int i=0;i<h.size();i++)
			{
				if(!i || h[i]<=h[a[j]])a[++j]=i;//前缀不递增的一段 
				else a[h.size()+j-i]=i;//后缀不递减的一段（乱序） 
			}
			std::sort(a.begin()+j+1,a.end(),cmp);//将后缀排序 
			return a;
		}
};