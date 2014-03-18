#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include "vsend_ioctl.h"

int main()
{
	int fd=0;
	int ret=0;
	Vsend_data data;
	strcpy(data.file1,"~/test1.txt");	
	strcpy(data.file2,"~/test2.txt");

	fd=open("/dev/vsend",O_RDWR);
	if(fd==-1)
	{
		perror("open");
		return 0;
	}
	printf("fd: %d\n",fd);

	ret=ioctl(fd,VSEND_IOCTL_WRITE,&data);
	printf("ret : %x\n",ret);

	close(fd);
	return 0;
}
