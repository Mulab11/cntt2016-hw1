class KnightCircuit2{
public:
	int maxSize(int w, int h){
		if(w>h){int t=w;w=h;h=t;}
		return w==1?1:w==2?h+1>>1:w==3&&h==3?8:w*h;
	}
};
