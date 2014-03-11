#ifndef __LINUX_VSENDFILE_H
#define __LINUX_VSENDFILE_H

#include <linux/unistd.h>
#include <linux/linkage.h>

asmlinkage long vsendfile(char* source, char* destination);

#endif
