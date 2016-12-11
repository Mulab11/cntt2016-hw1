#include<iostream>
#include<cstdio>
#define W(a,b) work(a,b,dep+1);
using namespace std;
int w,ans=4;
void  work(int n,int x,int dep)
{
	if(n==x&&x==1)ans=min(ans,dep);
	if(dep>=ans-1)return;
	int X=x/w+(x>x/w*w),Y=x-X*w+w,Xn=n/w+(n>n/w*w),Yn=n-Xn*w+w,_Q=(X-1)*(Y-1),_W=X-1,_E=(X-1)*(w-Y),t,tt;
	int _A=Y-1,_D=(X==Xn?Yn-Y:w-Y),_Z=(Xn-X-1)*(Y-1)+min(Yn,Y-1),_X=Xn-X-(Yn<Y),_C=max(0,(Xn-X-1)*(w-Y)+max(Yn-Y,0));
	if(_X)W(n-_X-_C,x)
	if(_Z)W(n-_Z-_X-_C,x)
	if(_D)W(n-_D-_C,x)
	if(_A)W(n-_A-_Z,x-_A)
	if(_E)W(n-_E-_D-_C,x-_E)
	if(_W)W(n-_W-_E,x-_W-_E)
	if(_W)W(n-_W,x-_W)
	if(_Q)W(n-_Q-_W-_E,x-_Q-_W-_E)
	if(_Q)W(n-_Q-_W,x-_Q-_W)
	if(_Q)W(n-_Q,x-_Q)
	if(_Q)W(n-_Q-_A-_Z,x-_Q-_A)
	if(X>1)t=((x-w)/(X-1)+((x-w)/(X-1)*(X-1)!=(x-w))),tt=t*(X-1),W(n-tt-(tt<=w-Y)*((Xn-X)*t+Yn-Y),x-tt)
	if(X==Xn&&w>Y&&(Y-1)>=(w-Y)&&(Y-1)%(w-Y)==0&&(Y-1)/(w-Y)<=(X-1))ans=min(ans,dep+2);
}
class FoxAndAvatar
{
	public:
	int minimalSteps(int n,int W,int x)
	{
		w=W;
		if(x%W==0&&n<2*x&&W%(x/W)==0)ans=2;
		work(n,x,0);
		return ans;
	}
};
