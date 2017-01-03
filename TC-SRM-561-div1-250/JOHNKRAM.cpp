#include<bits/stdc++.h>
using namespace std;
int n,m,m1,m2,s1,s2,t1,t2,i,j,k,ans=1000000000,n1,n2,a1[55],a2[55],b1[55],b2[55];
class ICPCBalloons
{
    public:
        int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted)
        {
            n=balloonCount.size();
            for(i=0;i<n;i++)if(balloonSize[i]=='M')a1[++n1]=balloonCount[i];
            else a2[++n2]=balloonCount[i];
            m=maxAccepted.size();
            sort(a1+1,a1+n1+1,greater<int>());
            sort(a2+1,a2+n2+1,greater<int>());
            for(i=1;i<=n1;i++)s1+=a1[i];
            for(i=1;i<=n2;i++)s2+=a2[i];
            for(i=0;i<1<<m;i++)//枚举每道题气球大小 
            {
                for(j=m1=m2=0;j<m;j++)if(i>>j&1)b1[++m1]=maxAccepted[j];
                else b2[++m2]=maxAccepted[j];
                sort(b1+1,b1+m1+1,greater<int>());
                sort(b2+1,b2+m2+1,greater<int>());
                for(t1=t2=0,j=1;j<=m1;j++)t1+=b1[j];
                for(j=1;j<=m2;j++)t2+=b2[j];
                if(t1>s1||t2>s2)continue;//判断是否有解 
                for(j=1,k=0;j<=m1;j++)k+=max(b1[j]-a1[j],0);//贪心求解 
                for(j=1;j<=m2;j++)k+=max(b2[j]-a2[j],0);
                ans=min(ans,k);//计算答案 
            }
            if(ans==1000000000)ans=-1;//判断是否无解 
            return ans;
        }
};