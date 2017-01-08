#include<bits/stdc++.h>
using namespace std;
const int MAXN=2005,oo=1000000000,dx[]={-1,0,1,0},dy[]={0,-1,0,1};
struct edge
{
	int v,n,b,c,a;
}e[MAXN*10];
int n,m,K,tt,h[MAXN],S,T,d[MAXN],q[MAXN],p[MAXN],pe[MAXN],he,ta,i,j,k,l,B,W,F,C;
bool b[MAXN];
inline void add(int u,int v,int c,int a)
{
	e[++tt].v=v;
	e[tt].n=h[u];
	e[tt].b=tt+1;
	e[tt].c=0;
	e[tt].a=a;
	h[u]=tt;
	e[++tt].v=u;
	e[tt].n=h[v];
	e[tt].b=tt-1;
	e[tt].c=c;
	e[tt].a=-a;
	h[v]=tt;
}
bool spfa()//求最小费用增广路 
{
	memset(d,127,sizeof(d));
	he=ta=0;
	d[q[ta++]=S]=0;
	b[S]=1;
	while(he!=ta)
	{
		b[i=q[he++]]=0;
		if(he==MAXN)he=0;
    	for(j=h[i];j;j=e[j].n)if(e[e[j].b].c&&d[e[j].v]>d[i]+e[j].a)
	    {
	    	p[e[j].v]=i;
	    	pe[e[j].v]=j;
	    	d[e[j].v]=d[i]+e[j].a;
	    	if(!b[e[j].v])
	    	{
	    		b[q[ta++]=e[j].v]=1;
	    		if(ta==MAXN)ta=0;
	    	}
	    }
    }
	return d[T]!=2139062143;
}
class CurvyonRails
{
    public:
        int getmin(vector <string> field)
        {
            n=field.size();
            m=field[0].size();
            S=n*m*3;
            T=n*m*3+1;
            for(i=0;i<n;i++)for(j=0;j<m;j++)if(field[i][j]!='w')if((i^j)&1)//建图 
            {
                B++;
                add(S,i*m+j,2,0);
                add(i*m+j,(i+n)*m+j,1,0);
                add(i*m+j,(i+n*2)*m+j,1,0);
                add(i*m+j,(i+n)*m+j,1,field[i][j]=='C');
                add(i*m+j,(i+n*2)*m+j,1,field[i][j]=='C');
                for(k=0;k<4;k++)if(i+dx[k]>=0&&i+dx[k]<n&&j+dy[k]>=0&&j+dy[k]<m&&field[i+dx[k]][j+dy[k]]!='w')add((i+(k&1)*n+n)*m+j,(i+dx[k]+(k&1)*n+n)*m+j+dy[k],1,0);
            }
            else
            {
                W++;
                add(i*m+j,T,2,0);
                add((i+n)*m+j,i*m+j,1,0);
                add((i+n*2)*m+j,i*m+j,1,0);
                add((i+n)*m+j,i*m+j,1,field[i][j]=='C');
                add((i+n*2)*m+j,i*m+j,1,field[i][j]=='C');
            }
            if(B!=W)return -1;//黑点数不等于白点数显然无解 
	    	while(spfa())//最小费用最大流 
	    	{
	    		for(i=T,j=oo;i!=S;i=p[i])j=min(j,e[e[pe[i]].b].c);
	    		F+=j;
		    	for(i=T;i!=S;i=p[i])
		    	{
		    		C+=j*e[pe[i]].a;
		    		e[pe[i]].c+=j;
		    		e[e[pe[i]].b].c-=j;
		    	}
	    	}
	    	if(F==B<<1)return C;//判断是否满流 
	    	return -1;
        }
};