#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int N=55;
char a[N];int n;
int cnt[26];
int now1[26];
int now2[26];
bool cho[N];
int pre;
bool hefa(int x){
    rep(i,0,25)now1[i]=now2[i]=cnt[i];
    //先分配下前面的点的状态
    rep(i,1,x)if(cho[i])now1[a[i]-'a']--;
    else now2[a[i]-'a']--;
    //后面贪心即可，有解的条件就是前面的是否溢出
    rep(i,0,25)if(now1[i]<0)return 0;
    rep(i,0,25)if(now2[i]<0)return 0;
    return 1;
}
bool canchoose(int x){
    //假设他选，然后check是否能构造出合法解
    cho[x]=1;
    if(hefa(x)){
        cho[x]=0;return 1;
    }
    else{
        cho[x]=0;return 0;
    }
}
string Main(){
    //统计每个字符出现了几次
    rep(i,1,n)cnt[a[i]-'a']++;
    rep(i,0,25)cnt[i]/=2;

    rep(i,1,n/2){
        int can=0;
        //考虑逐位确定，贪心选取答案
        rep(j,pre+1,n)if(!cho[j])if(canchoose(j))if((!can)||(a[j]<a[can]))can=j;
        cho[can]=1;
        pre=can;
    }
    string dj="";
    rep(i,1,n)if(cho[i])dj=dj+a[i];
    return dj;
}
class FoxAndHandle{
public:
    string lexSmallestName(string S){
        //预处理
        n=S.size();
        rep(i,1,n)a[i]=S[i-1];
        return Main();
    }
};