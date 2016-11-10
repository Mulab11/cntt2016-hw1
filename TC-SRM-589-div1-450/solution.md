# GearsDiv1
作者：尤艺霖

关键词：二分图最大独立集

## 题目简述
给出 $$N$$ 个被染成红色，绿色或蓝色的齿轮，求至少删除多少个齿轮才可以满足以下三个条件：

1.给每个颜色分配一个方向（顺时针或者逆时针）。

2.**相同**颜色的齿轮必须按照**相同**的方向旋转。

3.这些齿轮中存在着若干对咬合关系，具有咬合关系的齿轮必须按照**相反**方向旋转，保证不存在两个颜色相同的齿轮具有咬合关系。

输入一个表示齿轮颜色的字符串和一个表示咬合关系的矩阵，输出最少删除的齿轮个数。

保证齿轮总数大于或等于2，小于或等于50。
## 算法
发现齿轮的颜色只有三种，考虑枚举每种颜色的方向。

可以发现，三种颜色的齿轮全部转向一样的方案一定不会优于让其中一种颜色的齿轮反向旋转的方案，因为在三种颜色的齿轮同向旋转的方案中，将一种颜色的齿轮转向一定不会让结果变劣，因为这不会产生更多的转向相同的咬合关系。

由于顺时针旋转和逆时针旋转是相似的，不妨设目前的状态是两种颜色逆时针旋转，一种颜色顺时针旋转。可以发现，顺时针旋转的那一种颜色是可以忽略的，因为它不会贡献任何转向相同的咬合关系。所以问题转化为了如何解决两种颜色之间的咬合关系，考虑按照这两种颜色之间的咬合关系构建一个二分图，将问题转化为二分图最大独立集问题，从而使用网络流解决。

建图过程参见代码(mxf是网络流)：

```C++
inline int get(char C)
{
	if(C=='R')return 1;
	if(C=='G')return 2;
	return 3;
}
struct GearsDiv1
{
	int n,ans;
	inline int getmin(string color,vector<string>graph)
	{
		n=color.length(); 
		ans=n+1;
		for (int ip=1;ip<=3;ip++)// pick the color(ip-1) as the useless color
		{
			mxf.init(n+1,0,n+1);
			for (int i=1;i<=n;i++)
			{
				for (int j=1;j<=n;j++)
				{
					if(graph[i-1][j-1]=='Y'&&(get(color[i-1])==ip&&get(color[j-1])==ip%3+1))
					{
						mxf.addedge(i,j,1);// build the graph
					}
				}
			}
			for (int i=1;i<=n;i++)
			{
				if(get(color[i-1])==ip)
				{
					mxf.addedge(Sta,i,1);
				}
				else if(get(color[i-1])==ip%3+1)
				{
					mxf.addedge(i,Des,1);
				}
			}
			ans=min(ans,mxf.solve());// it is actually ans=min(ans,n-(n-mxf.solve()))
		}
		return ans;
	}
};
```