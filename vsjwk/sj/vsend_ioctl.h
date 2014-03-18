typedef struct _Vsend_data
{
	char file1[50];
	char file2[50];
} Vsend_data;

#define VSEND_IOCTL_MAGIC	's' 
#define VSEND_IOCTL_TEST	_IO(VSEND_IOCTL_MAGIC,0)
#define VSEND_IOCTL_WRITE	_IOW(VSEND_IOCTL_MAGIC,1,Vsend_data)
