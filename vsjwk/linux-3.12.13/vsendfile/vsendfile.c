#include <linux/vsendfile.h>
//#include <linux/linkage.h>

asmlinkage long sys_vsendfile(const char *source, const char *destination)
{
	long retval;

	retval = 700;

	return retval;
}
