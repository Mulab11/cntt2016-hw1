# TheBrickTowerMediumDivOne
作者：徐懿

关键词：数学 贪心 
## 题目简述
给定一个长度为$$heights.size()$$的序列$$heights$$。

你需要球出一个$$0$$到$$heights.size()-1$$的排列$$a$$,在使得$$1.\quad \sum_{i=1}^{heights.size()-1}max(heights_{a_i},heights_{a_{i-1}})$$最小的情况下，$$a$$的字典序尽可能小。 

$$heights$$中元素与$$heights.size()$$均为$$[1,47]$$之间的整数。

## 解法
经过观察可以发现，$$a$$必定为

	存在一个$$i$$，使得$$\forall 0<j\le i,heights_{a_j}\le heights_{a_{j-1}}$$且$$\forall i<j<heights.size(),heights_{a_{j-1}}\le heights_{a_j}$$。

中字典序最小的序列。 

根据字典序的性质，我们可以在满足$$1.$$的情况下尽量把将编号小的数排在前面，贪心地。

具体地，我们以编号从小到大的顺序依次尝试，只要满足$$1.$$，就将其$$push_back$$。最后将没有选入的数按数值为第一关键字递增，序号为第二关键字递增排序，置入答案排列的末尾。 

具体细节参见代码。
```C++
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
```
