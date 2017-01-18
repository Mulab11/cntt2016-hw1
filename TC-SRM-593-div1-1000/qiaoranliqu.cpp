#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>

#define ins insert

#define N 2000005

using namespace std;

const int Mo=(int)1e9+7;

char s[N];
int f[N],sum[N],ww[N],oo[N],i,j,m,n,p,k,prew[N],preo[N];
struct seg{
	   int l,r;
};
set<seg>st;
set<seg>::iterator it;
void jia(int &x,int y)
{
	x+=y; if(x>=Mo) x-=Mo;
}
inline bool operator <(seg a,seg b) { if (2*a.r-a.l!=2*b.r-b.l) return 2.*a.r-a.l<2*b.r-b.l; return a.l<b.l;}
int solve()
{
	   sum[0]=sum[1]=f[0]=1;
	   for (i=1;i<=n;++i) ww[i]=ww[i-1]+(s[i]=='w'),oo[i]=oo[i-1]+(s[i]=='o');
	   int now=0;
	   for (i=1;i<=n;++i)
	   {
	   	     preo[i]=now;
	   	     if (s[i]=='o') now=i;
	   }
	   now=0;
	   for (i=1;i<=n;++i)
	   {
	   	     if (s[i]=='w') now=i;
	   	     prew[i]=now;
	   }
	   for (i=2;i<=n;i+=2)
	   {
                if (s[i-1]=='w'||s[i]=='w')
                {
                	   st.clear();
                	   if(s[i]=='w')
                	   {
                	   	     st.ins((seg){preo[i]+1,i});
                	   }
                	   else 
                	   {
                	   	   if (s[i]!='o') st.ins((seg){preo[i]+1,i});
						   else st.ins((seg){preo[i]+1,i-1});
					   }
                }
                else 
                {
                	    if (s[i-1]=='o'&&s[i]=='?') st.ins((seg){i,i});
						if (s[i-1]=='?')
						{
							  if (!(i==2||s[i-1]=='o'))
							  {
							        seg x=(seg){preo[i-1]+1,i-2};
									st.erase(x);
									if (s[i]=='?') x.r=i; else x.r=i-1;
									st.ins(x);
							  }
							  else 
							  {
							  	     if (s[i]=='?') st.ins((seg){i-1,i});
							  	     else st.ins((seg){i-1,i-1});
							  }
					    }
				}
			it=st.end();
			if(it==st.begin()) { sum[i]=sum[i+1]=sum[i-2]; continue; }
			--it;
			for (;;)
			{
			    if (2*it->r-it->l>=i-1)
				{
					  int L=it->l,R;
					  R=min(it->r,it->r-(i-it->r-1));
					  if (ww[it->r]-ww[it->l-1]>0)
					  {
					  	      int mid=prew[it->r];
					  	      L=max(L,2*mid-i+1); 
					  }
					  if (L-2>=0) 
					  jia(f[i],(sum[R-1]+Mo-sum[L-2])%Mo);
					  else jia(f[i],sum[R-1]);
					  if (it==st.begin()) break;
					  --it; 
			    }
			    else 
			    {
			    	  if (it==st.begin()) 
			    	  {
			    	  	   st.erase(it); break; 
			    	  }
			    	  else
			    	  {
			    	  	   seg x=*it,y=*--it;
			    	  	   st.erase(x);
			    	  	   it=st.find(y);
			    	  }
			    }
		    }
		    sum[i]=sum[i+1]=(sum[i-2]+f[i])%Mo;
       }
       return f[n];
} 
class WolfDelaymasterHard{
   public:
   int countWords(int M, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd) 
   {
   	        n=M;
   	        for (i=0;i<n;++i) s[i]='?'; 
            long long x = w0;
            for(i=0;i<wlen;i++){
	         s[x] = 'w';	
             x = (x * wmul + wadd) % M;
            }
            x = o0;
            for(i=0;i<olen;i++){
	        s[x] = 'o';		  
	        x = (x * omul + oadd) % M;
            }
            for (i=M;i;--i) s[i]=s[i-1];
            return solve();
    }
}E;
int main()
{
   printf("%d\n",E.countWords(60,35,8,55,3,11,20,9,29));
}
