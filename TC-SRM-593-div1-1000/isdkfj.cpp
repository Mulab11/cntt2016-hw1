#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int mo=1000000007;
char s[2000005];
int f[2000005],q[2000005],su[2000005];
inline void get(int&x,int y){if((x+=y)>=mo)x-=mo;}
inline void got(int&x,int y){if((x-=y)<0)x+=mo;}

class WolfDelaymasterHard {
public:
	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd) {
		for(int i=1;i<=N;++i)s[i]='?';
		LL x=w0;
		for(int i=0;i<wlen;++i){
			s[x+1]='w';
			x=(x*wmul+wadd)%N;
		}
		x=o0;
		for(int i=0;i<olen;++i){
			s[x+1]='o';
			x=(x*omul+oadd)%N;
		}//构造字符串 
		int t=1;
		while((t<<1)<=N){
			if(s[t]!='?')break;
			if(s[(t<<1)-1]=='w')break;
			if(s[(t<<1)]=='w')break;
			++t;
		}//初始化 
		f[0]=1;get(q[2],1);got(q[t<<1],1);su[0]=f[0];
		for(int i=2,w=-1,o1=-1,o2=-1,la=-1,l,r;i<=N;i+=2){
			get(q[i],q[i-2]);
			f[i]=q[i];
			if(s[i]=='w'){
				w=i;o2=-1;
				o1=s[i-1]=='o'?i-1:la;
			}else if(s[i-1]=='w'){
				w=i-1;o1=la;
				o2=s[i]=='o'?i:-1;
			}
			if(s[i]=='o')la=i;
			else if(s[i-1]=='o')la=i-1;
			if(o2==-1){
				if(s[i-1]=='o')o2=i-1;
				else if(s[i]=='o')o2=i;
			}//更新最近的w跟前后的o 
			if(w!=-1){
				l=1,r=i-w;
				if(o1!=-1)r=min(r,(i-o1)>>1);
				if(o2!=-1)l=max(l,i-o2+1);
				r=min(r,i>>1);
				l=max(l,(i-w+2)>>1);
				if(l<=r){
					get(f[i],su[i-(l<<1)]);
					if((r<<1)<i)got(f[i],su[i-(r<<1)-2]);
					//前半段至少一个w的转移 
				}
			}
			t=max(1,t-2);
			while(i+(t<<1)<=N){
				if(s[i+t]!='?')break;
				if(s[i+(t<<1)-1]=='w')break;
				if(s[i+(t<<1)]=='w')break;
				++t;
			}
			get(q[i+2],f[i]);got(q[i+(t<<1)],f[i]);//前半段全是?转移 
			su[i]=su[i-2];get(su[i],f[i]);//前缀和 
		}
		return f[N];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
