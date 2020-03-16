#include<stdlib.h>
typedef int BOOL;
#define TRUE (1)
#define FALSE (0)

#define CountOf(ary) (sizeof(ary)/sizeof(ary[0]))
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))
#define Clamp(value,low,high) (Min(Max(value,low),high))