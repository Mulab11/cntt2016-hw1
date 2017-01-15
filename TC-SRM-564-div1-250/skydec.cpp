#include<bits/stdc++.h>
using namespace std;
class KnightCircuit2{
public:
    int maxSize(int w, int h){
        //只有一行，答案显然为1
        if(min(w,h)==1)return 1;
        //只有两行，答案只跟列有关
        if(min(w,h)==2)return (max(w,h)+1)/2;
        //3*3是8
        if(w==3&&h==3)return 8;
        //可以发现3*4答案是12，于是新增一行，那一行也肯定都能到，于是答案都是w*h
        return w*h;
    }
};

