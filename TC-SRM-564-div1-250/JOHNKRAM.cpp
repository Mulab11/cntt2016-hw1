#include<bits/stdc++.h>
using namespace std;
class KnightCircuit2
{
    public:
        int maxSize(int w, int h)
        {
            if(min(w,h)==1)return 1;//1行 
            if(min(w,h)==2)return max(w,h)+1>>1;//2行 
            if(max(w,h)==3)return 8;//3*3
            return w*h;//其他 
        }
};