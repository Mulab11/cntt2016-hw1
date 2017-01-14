#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
template<class T>inline bool ten(T &x,const T &y){return y<x?x=y,1:0;}
template<class T>inline bool rel(T &x,const T &y){return x<y?x=y,1:0;}

class FoxAndAvatar
{
	public:
	int n,w,x,ans;
	
	bool canfinish(int n,int x)//Check if it can be done in one step.
	{
		if(x==1&&(w==1||n<=w))return 1;
		if(x==n&&(n%w==1||n<=w))return 1;
		if(n<2*w&&x==w)return 1;
		return 0;
	}
	
	void dfs(int n,int x,int s)
	{
		//If it has been done, we update the answer.
		if(n==1)ten(ans,s);
		//If it can be done in one step, update the answer.
		if(canfinish(n,x)){ten(ans,s+1);return;}
		//Stop searching if it can not be better than the current answer.
		if(s+2>=ans)return;
		int i,j,rx=(x-1)/w+1,r=(n-1)/w+1,cx=(x-1)%w+1,c=(n-1)%w+1;
		/*assume it looks like this:
		****
		******
		***x**
		******
		******
		*/
		//First let's think that n can always be less and while the answer won't be worse.
		//So we can minimum n while we change x.
		//remove all avatars above x.
		dfs(min(n,rx*w),x,s+1);
		//remove a rectangle of avatars under x
		for(int i=1;i<rx;i++)
			for(int j=1;j<=w;j++)
				dfs(n-i*j,x-i*j,s+1);
		//Remove a rectangle on left of x.
		//that means all avatars satisfying x>=i and y<=j
		for(int i=1;i<=rx;i++)
			for(int j=1;j<cx;j++)
				dfs(n-(r-i+1)*j+(j>c?j-c:0),x-(rx-i+1)*j,s+1);
		//Remove a rectangle on right of x.
		//that means all avatars satisfying x>=i and y>=j
		for(int i=1;i<rx;i++)
			for(int j=cx+1;j<=w;j++)
				dfs(n-(r-i+1)*(j-cx)+min(j-cx,j>c?j-c:0),x-(rx-i)*(j-cx),s+1);
	}
	
	int minimalSteps(int n,int width,int x)
	{
		this->n=n;
		this->w=width;
		this->x=x;
		//We can prove that the ans is at most 4.
		ans=4;
		//We search for no more than 2 steps and it will take O(n^2) time. 
		dfs(n,x,0);
		return ans;
	}
};

