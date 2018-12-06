#include "bigint.h"
#include <sstream>
#include <map>
using namespace std;
typedef pair<bigint,bigint> pa;

bigint exp(bigint a,bigint k,bigint c){
	if(k==0)return 1;
	if(k==1)return a%c;
	else if(k%2==0){
		bigint temp=exp(a,k/2,c);
		return (temp*temp)%c;
	}
	else{
		bigint temp=exp(a,(k-1)/2,c);
		return ((((a%c)*temp)%c)*temp)%c;
	}
}