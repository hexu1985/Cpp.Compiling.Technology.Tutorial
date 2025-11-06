#include <stdio.h>
#include "shlibdemo.h"

int shlib_demo_function(int x)
{
	printf("%s()\n", __FUNCTION__);
	return 2*x;
}
