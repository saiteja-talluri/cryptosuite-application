#include "bigint.h"
#include "dislog.cpp"
#include "math.h"
#include <sstream>
#include <map>
using namespace std;
struct primefield{
    bigint x,y;
    primefield add(bigint p,bigint a,bigint b)
    {
        bigint m;primefield C;
        m=((b-y)*inverse((a-x).abs(),p))%p;
        if (a-x<0)m=-m;
        C.x=(((m%p)*(m%p)-x%p-a%p)%p+p)%p;
        C.y=((-y%p+(m%p)*(x%p-C.x%p))%p+p)%p;
        return C;
    }
};

struct primefield1{
    bigint x,y;
    bigint a,b;//a,b in X^3+aX+b
    primefield1 doubling(bigint p)
    {
        bigint m;primefield1 C;
        m=((bigint(3)*x%p*x%p+a%p)*inverse(bigint(2)*y.abs()%p,p));
        if (y<0)m=-m;
        C.x=(((m%p)*(m%p)-x%p-x%p)%p+p)%p;
        C.y=((-y%p+(m%p)*(x%p-C.x%p))%p+p)%p;
        return C;
    }
};