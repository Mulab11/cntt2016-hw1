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
int a[N],n;
double Main(){
    //计算有R个房间
    int R=(n+19)/20;
    int eli=a[1];
    //排序
    sort(a+1,a+1+n);
    reverse(a+1,a+1+n);
    double ans=0;
    double res=0;
    int tt=0;
    rep(i,1,(n+R-1)/R){
        //枚举每次分配
        //这次分配选手l..r
        int l=(i-1)*R+1;
        int r=i*R;
        ++tt;
        if(r>n)r=n;
        bool hav=0;
        int sum=0;
        //计算rating和
        rep(j,l,r){
            sum+=a[j];
            if(a[j]==eli)hav=1;
        }
        if(r==n){
            //如果已经是最后一群的话需要特判
            if(hav){
                //计算平均值，要除人数tt
                res=(ans+eli)/tt;
            }
            else{
                //分情况讨论，他的房间的人数要么是tt，要么是tt-1
                //利用期望线性性计算即可
                res=((ans+(sum*1.)/(r-l+1))*((1.*(r-l+1))/R))/tt;
                res+=(ans)*(1-(1.*(r-l+1)/R))/(tt-1);
            }
            break;
        }
        if(hav){
            //如果这些人里有eli，则贡献就是他自己的rating
            ans+=eli;
        }
        else{
            //否则每个人都可能和eli一个房间，所以贡献是和/R
            ans+=(sum*1.)/R;
        }
    }
    return res;
}
class EllysRoomAssignmentsDiv1{
public:
    double getAverage(vector <string> ratings){
        //预处理
        string gt="";
        rep(i,0,ratings.size()-1)gt=gt+ratings[i];
        int now=0;
        rep(i,0,gt.size()-1){
            if(gt[i]==' '){
                a[++n]=now;
                now=0;
            }
            else{
                now=now*10+(gt[i]-'0');
            }
        }
        a[++n]=now;
        return Main();
    }
};