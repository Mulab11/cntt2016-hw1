#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
struct FoxAndFencing
{
string WhoCanWin(int a,int b,int c,int d,int s)
{
	if(a+c>=s) return "Ciel";
	if(s+a<=b+d) return "Liss";
	if(a==b||a+c==b+d) return "Draw";
	if(a>b)
	{
		if(a+c>b+b+d) return "Ciel";
		return "Draw";
	}
	if(a+a+c<b+d) return "Liss";
	return "Draw";
}
};