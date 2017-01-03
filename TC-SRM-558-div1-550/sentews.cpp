#include <algorithm>
#include<vector>
#include<string>
using namespace std;
int n=0,m=0;
long long ans=0;
int f[1111]={};struct ff{int x,y;}g[1111]={};
int getsum(int a,int b){if(a>b)swap(a,b);return (a+b)*(b-a+1)/2;}
int getpos1(double x)
{
	for(int i=n-1;i>=0;i--)
		if(f[i]<x)return i;
	return -1;
}
int getpos2(double x)
{
	for(int i=0;i<n;i++)
		if(f[i]>x)return i;
	return n;
}
class Ear
{
public:
	
	long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY)
	{
		string temp="0";int temp2=0;
		for(int i=0;i<redX.size();i++)temp+=redX[i];
		temp+=' ';
		for(int i=0;i<temp.size();i++)
		{
			if(temp[i]==' ')
				f[n++]=temp2,temp2=0;
			else
				temp2=temp2*10+temp[i]-'0';
		}
		temp="0";temp2=0;
		for(int i=0;i<blueX.size();i++)temp+=blueX[i];
		temp+=' ';
		for(int i=0;i<temp.size();i++)
		{
			if(temp[i]==' ')
				g[m++].x=temp2,temp2=0;
			else
				temp2=temp2*10+temp[i]-'0';
		}
		temp="0";temp2=0;m=0;
		for(int i=0;i<blueY.size();i++)temp+=blueY[i];
		temp+=' ';
		for(int i=0;i<temp.size();i++)
		{
			if(temp[i]==' ')
				g[m++].y=temp2,temp2=0;
			else
				temp2=temp2*10+temp[i]-'0';
		}
		sort(f,f+n);
		for(int i=0;i<m-1;i++)
			for(int j=i+1;j<m;j++)
			{
				int x1=g[i].x,x2=g[j].x,y1=g[i].y,y2=g[j].y;
				if(y1==y2)continue;
				if(y1>y2)swap(y1,y2),swap(x1,x2);
				int xx1,xx2,yy1,yy2;
				xx1=getpos1(x1),xx2=getpos1(x2-1.0*(x2-x1)*y2/(y2-y1));
				yy1=getpos2(x1),yy2=getpos2(x2-1.0*(x2-x1)*y2/(y2-y1));
				if(xx1>=xx2)xx2=xx1-1;
				if(yy1<=yy2)yy2=yy1+1;
				if(xx2<0||yy2>=n)continue;
				ans+=getsum(xx1-xx2,xx1)*getsum(yy2-yy1,n-yy1-1);
			}
		return ans;
	}
};
