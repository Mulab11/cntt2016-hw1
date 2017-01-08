#include<bits/stdc++.h>
using namespace std;
#define ll long long
long double d[50][50],L[50],R[50],l1,r1;
int n,i,j,q[50],he,ta;
bool b[50];
long double dis(int a,int b,int c,int d)//求(a,b)与(c,d)两点距离，使用double会被卡精度 
{
    return sqrt((long double)((ll)(a-c)*(a-c)+(ll)(b-d)*(b-d)));
}
class CandyOnDisk
{
    public:
        string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty)
        {
            if(sx==tx&&sy==ty)return "YES";
            n=x.size();
            for(i=0;i<n;i++)for(j=0;j<n;j++)d[i][j]=dis(x[i],y[i],x[j],y[j]);//求圆心之间的距离 
            for(i=0;i<n;i++)L[i]=1;//初始合法区间为空 
            for(i=0;i<n;i++)if(dis(x[i],y[i],sx,sy)<=r[i])//起点在圆内，加入队列并更新合法区间 
            {
                b[i]=1;
                L[i]=R[i]=dis(x[i],y[i],sx,sy);
                q[ta++]=i;
            }
            while(he!=ta)//SPFA迭代 
            {
                b[i=q[he++]]=0;
                if(he==50)he=0;
                for(j=0;j<n;j++)if((x[i]!=x[j]||y[i]!=y[j])&&d[i][j]<=r[i]+r[j]&&R[i]>=d[i][j]-r[j]&&L[i]<=d[i][j]+r[j])//可以迭代 
                {
                    l1=max(d[i][j]-r[i],(long double)0.0);
                    r1=min(d[i][j]+r[i],(long double)r[j]);
                    if(L[j]>R[j]||L[j]<=r1&&l1<=R[j]&&(l1<L[j]||r1>R[j]))//可以更新答案区间 
                    {
                        if(L[j]>R[j])
                        {
                            L[j]=l1;
                            R[j]=r1;
                        }
                        else
                        {
                            L[j]=min(L[j],l1);
                            R[j]=max(R[j],r1);
                        }
                        if(!b[j])//不在队中，入队 
                        {
                            b[q[ta++]=j]=1;
                            if(ta==50)ta=0;
                        }
                    }
                }
            }
            for(i=0;i<n;i++)if(dis(x[i],y[i],tx,ty)>=L[i]&&dis(x[i],y[i],tx,ty)<=R[i])return "YES";//判断是否有解 
            return "NO";
        }
};