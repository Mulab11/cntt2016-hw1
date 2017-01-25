class TriangleXor{
public:
	int theArea(int W){
		double S=W+1;
		for(int i=1,s=-2;i<=W;i++,s=-s)S+=s*(W+1.0-i)*W/(W+i);
		return int(S*W/2);
	}
};
