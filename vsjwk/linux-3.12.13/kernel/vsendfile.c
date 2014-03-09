#include <linux/linkage.h>
#include <string.h>

asmlinkage long sys_vsendfile(char *path)
{
	return strlen(path);
}
