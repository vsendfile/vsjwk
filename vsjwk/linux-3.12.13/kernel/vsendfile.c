#include <linux/linkage.h>

asmlinkage ssize_t sys_vsendfile(const char *source, const char *destination)
{
	ssize_t revtval;

	retval = 1;

	return retval;
}
