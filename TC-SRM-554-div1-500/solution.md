# TheBrickTowerMediumDivOne
作者：徐懿

关键词：数学 贪心 
## 题目简述
给定一个长度为$$heights.size()$$的序列$$heights$$。

下文均用$$n$$代替$$heights.size()$$。

对于一个$$0$$到$$n-1$$的排列$$a$$,定义$$f(a)=\sum_{i=1}^{n-1}max(heights_{a_i},heights_{a_{i-1}})$$。

你需要球出一个$$0$$到$$n-1$$的排列$$a$$,在使得$$f(a)$$最小的情况下，$$a$$的字典序尽可能小。 

$$heights$$中元素与$$n$$均为属于$$[1,47]$$的整数。

## 约定及泉岭序列
对于一个元素不相同且均为属于$$[0,n)$$的整数的序列$$b$$，设$$h$$中最大数的下标为$$i$$，$$b$$的长度为$$m$$。满足$$\forall b'$$为$$b$$的重排列，$$f(b)\le f(b')$$。我们称$$b$$为泉岭序列。

## 引理一
对于一个泉岭序列$$b$$，有$$b_0=i$$或$$b_{m-1}=i$$。

若引理一不成立，我们可以将$$i$$取出并置于$$b_{0}$$或$$b_{m-1}$$，构成$$b'$$。

$$f(b')=f(b)-2\times h_i+h_i+max(b中i的位置左右两数)<f(b)$$

这与$$f(b)$$最小矛盾，故引理一成立。

## 引理二 
对于一个泉岭序列$$b$$。设删去$$b$$中代表$$h$$中最大数的下标后形成$$b'$$，$$b'$$为一个泉岭序列。

由引理一，$$h$$中最大数下标必定在$$b_{0}$$或$$b_{m-1}$$，它对$$f(b)$$的贡献恒为$$h$$中最大数，与其他数独立，若要满足$$f(b)$$最小，$$f(b')$$也要最小化，故$$b'$$为泉岭序列。

## 定理一
对于一个泉岭序列$$b$$，$$\exists i$$，使得$$\forall 0<j\le i,heights_{b_j}\le heights_{b_{j-1}}$$且$$\forall i<j<m,heights_{b_{j-1}}\le heights_{b_j}$$。

当$$m=1$$时，结论显然成立。

当$$m>1$$时，由引理一，$$h$$中最大数下标必定在$$b_{0}$$或$$b_{m-1}$$，这与本定理相符。由引理二，在$$b$$中去掉这个数后得到泉岭序列$$b'$$，归纳得证。

## 算法
我们可以由定理一，根据字典序的性质，贪心地构造出$$a$$。

具体地，我们以编号从小到大的顺序依次尝试，只要满足当前这个数的$$heights$$小于上一个数，就将其$$push\_back$$。最后将没有选入的数按数值为第一关键字递增，序号为第二关键字递增排序，置入答案排列的末尾。 

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