#include<bits/stdc++.h>
using namespace std;
int i,j,a[300],ans;
class LittleElephantAndBalls
{
    public:
        int getNumber(string S)
        {
            for(i=0;i<S.size();j+=++a[S[i++]]<3)ans+=j;
            return ans;
        }
};
