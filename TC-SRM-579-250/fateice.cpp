#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
class UndoHistory
{
public:
	int minPresses(vector<string> s)
	{
		int n=s.size(),m,ans=0;
		int i,j;
		string t;
	    map<string,int> p;  //用来记录一个字符串是否是历史版本  如果值是i+1说明恰好是第i个串 
		p[t]=1; 
		for(i=0;i<n;i++)
		  {
		   t=s[i];
		   m=t.size();
		   //查询最长的在历史版本中的前缀 
		   for(j=m-1;j>=0;j--)
		     {
		      if(p[t])
		        break;
		      t.erase(j);
			 }
		   //如果这个前缀恰好是上一个串加一个字母，那么直接从上一个串转移过来更优 
		   if(j>0 && p[t]<i+1)
		     {
		      t.erase(j);
			  if(p[t]==i+1)
			    j--;
			 }
		   //统计答案 
		   if(p[t]==i+1)
		     ans+=m-1-j+1;
		   else
		     ans+=m-1-j+3;
		   t=s[i];
		   p[t]=i+2;
		   //将当前串的所有前缀加入历史版本 
		   for(j=m-1;j>=0;j--)
		     {
		      t.erase(j);
			  p[t]=1;
			 }
		  }
		return ans;
	}
};
