#include "bigint.h"
#include <sstream>
#include <map>
using namespace std;
typedef pair<bigint,bigint> pa;

bigint add(bigint a,bigint b,bigint c){
	bigint temp=(a+b)%c;
	return temp;
}
