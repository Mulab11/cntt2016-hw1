#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=2600;
bool a[N];
int n,k;
int pre[N],suf[N];
int numm[N][N];
LL Main(){
    rep(i,1,n){
        int num=0;
        bool ok=0;
        per(j,i,1){
            if(a[j]){
                num++;
                ok|=(num>=k);
            }
            else{
                num=0;
            }
            if(ok)pre[i]++;
        }
        num=0;
        ok=0;
        rep(j,i,n){
            if(a[j]){
                num++;
                ok|=(num>=k);
            }
            else{
                num=0;
            }
            if(ok)suf[i]++;
        }
    }

    LL ans=0;
    rep(i,1,n){
        ans+=suf[i+1]*1ll*i*(i+1)/2;
        ans+=pre[i]*1ll*(n-i)*(n-i+1)/2;
    }
    LL sum=0;
    rep(i,1,n){
        ans-=sum*suf[i];
        sum+=pre[i];
    }

    rep(i,1,n){
        rep(j,0,n)numm[i][j]+=numm[i-1][j];
        
        int pre=0;
        int dd=1;
        int num=0;
        per(j,i,1){
            if(a[j]){
                if(dd)pre++;
                num++;
                if(num>=k)break;
            }
            else{
                num=0;dd=0;
            }
            numm[i][pre]++;
        }
    }

    rep(i,1,n)per(j,n,0)numm[i][j]+=numm[i][j+1];
    rep(i,1,n){
        int pre=0;
        int dd=1;
        int num=0;
        rep(j,i,n){
            if(a[j]){
                if(dd)++pre;
                num++;
                if(num>=k)break;
            }
            else{
                num=0;dd=0;
            }
            ans+=numm[i-1][k-pre];
        }
    }
    return ans;
}
class LittleElephantAndRGB{
public:
    LL getNumber(vector <string> list, int minGreen){
        ::k=minGreen;
        string now="";
        rep(i,0,list.size()-1)now=now+list[i];
        n=now.size();
        rep(i,1,n)a[i]=(now[i-1]=='G');
        return Main();
    }
};