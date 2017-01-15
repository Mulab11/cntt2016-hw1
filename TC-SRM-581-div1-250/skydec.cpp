#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int N=55;
int L,n;
int sum[N];
int ct[N];
int all[N];
int gtw[N];
string Main(){
    //预处理每个答案的区间有几个
    rep(i,1,n-L+1)all[sum[i+L-1]-sum[i-1]]++;
    string gt="";
    rep(i,1,n){
        bool must=0;
        bool hav=0;
        memset(gtw,0,sizeof gtw);
        //枚举包含i的区间
        rep(j,max(i-L+1,1),min(i,n-L+1)){
            //如果包含i的区间都没有被需求，则一定不能被监视到
            hav|=((ct[sum[j+L-1]-sum[j-1]])>0);
            gtw[sum[j+L-1]-sum[j-1]]++;
        }
        //如果去掉包含i的区间后，需求不够的话，那么i一定要被摄像头监视到
        rep(j,0,n)if(ct[j])if(all[j]-gtw[j]<ct[j])must=1;

        //统计答案
        if(!hav)gt=gt+"-";
        else if(must)gt=gt+"+";
        else gt=gt+"?";
    }
    return gt;
}
class SurveillanceSystem{
    public:
    string getContainerInfo(string cont, vector <int> reports, int L){
        //预处理
        n=cont.size();
        rep(i,1,n)sum[i]=sum[i-1]+(cont[i-1]=='X');
        rep(i,0,reports.size()-1)ct[reports[i]]++;
        ::L=L;
        return Main();
    }
};



