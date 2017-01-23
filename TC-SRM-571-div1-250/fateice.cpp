#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
class FoxAndMp3
{
	int n;
	vector<string> p;
	inline void dfs(int i,string x)
	{
		if(i>n || p.size()==50)
		  return;
		if(i)
		  p.push_back(x+".mp3");
		int j;
		for(j=!i;j<10;j++)
		  dfs(i*10+j,x+char(j+'0'));
	}
public:
	vector<string> playList(int nn)
	{
		n=nn;
		dfs(0,"");
		return p;
    }
};
