#include <cstdio>
class FoxAndAvatar{
public:
	int w,ans;
	int max(int a,int b){return a>b?a:b;}
	void DFS(int n,int x,int dep){
		if(dep>=ans)return;
		if(n==1){ans=dep;return;}
		if(dep+1>=ans)return;
		if(n<=w&&(x==1||x==n)||n>w&&n<2*w&&x==w||n%w==1&&x==n){ans=dep+1;return;}
		if(dep+2>=ans)return;
		int qn=n/w,rn=n%w,qx=(x-1)/w,rx=(x-1)%w;
		for(int i=x-1,j,k,a,b;i--;){
			j=(a=i/w+1)*(b=i%w+1);k=0;
			if(b<=rx)k=max(k,(qn-qx-1)*b-max(-b,-rn));
			if(a<=qx&&b<w-rx)k=max(k,(qn-qx)*b-max(-b,-max(rn-rx-1,0)));
			DFS(n-j-k,x-j,dep+1);
		}
		DFS(n-max(n-(qx+1)*w,(qn-qx)*(w-rx-1)+max(rn-rx-1,0)),x,dep+1);
	}
	int minimalSteps(int n, int width, int x){
		w=width;ans=4;DFS(n,x,0);return ans;
	}
};
