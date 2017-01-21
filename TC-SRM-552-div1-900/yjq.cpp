
#include <bits/stdc++.h>

using namespace std ;

typedef long long LL ; 

bool flag[1000005]={0};
vector<int>v;
class HolyNumbers{
    public:
    void Init(int n){
        for(int i=2;i<=sqrt(n+1.0);i++){
            if(flag[i]) continue;
            for(int j=2;j*i<=n;j++)
                flag[i*j]=true;
        }
        for(int i=2;i<=n;i++)
            if(!flag[i])
               v.push_back(i);
    }
    LL solve(int idx,LL up){
        if(idx>=v.size()||v[idx]>up)  return 1;
        if((LL)v[idx]*v[idx]>=up){
            int k=upper_bound(v.begin()+idx,v.end(),up)-v.begin();
            return k-idx+1;
        }
        LL p=v[idx];
        LL ans=solve(idx+1,up);
        for(LL num=p;num<=up&&num>0;num*=p*p)
            ans+=solve(idx+1,up/num);
        return ans;
    }
    LL count(LL upTo, int maximalPrime){
        v.clear();
        Init(maximalPrime);
        return solve(0,upTo);
    }
};


