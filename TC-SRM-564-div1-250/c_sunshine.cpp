#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

class KnightCircuit2
{
	public:
	
	int maxSize(int w,int h)
	{
		if(min(w,h)==1)return 1;//can't jump.
		if(min(w,h)==2)return (max(w,h)+1)/2;//can only jump to right.
		if(max(w,h)==3)return 8;//special situation: can not reach the centre cell.
		return w*h;//Otherwise can reach each cell.
	}
};

