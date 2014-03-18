#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/virtio.h>
#include "vsend_ioctl.h"
#include "virtio.h"
#include <linux/scatterlist.h>

#define  MAJOR_NUMBER   234
#define  DEVICE_NAME "vsend"

struct virtqueue vsend_vq;

static int vsend_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct scatterlist sg[2];
	Vsend_data *data;

	if(_IOC_TYPE(cmd) != VSEND_IOCTL_MAGIC)
		return -EINVAL;
	
	switch(cmd)
	{

	case VSEND_IOCTL_TEST:
		printk( "ioctl test\n" );
  		break;
 	case VSEND_IOCTL_WRITE:
		data=(Vsend_data *)arg;
		
		sg_init_table(sg,ARRAY_SIZE(sg));
		sg_set_buf(&sg[0],"test1",5);
		sg_set_buf(&sg[1],"test2",5);
		virtqueue_add_sgs(&vsend_vq,sg,0,0,data,GFP_ATOMIC);		
				
		printk("file1: %s\n",data->file1);
		printk("file2: %s\n",data->file2);
		printk( "write test\n" );
  		break;
 	}

	return 0;
}

static int vsend_open( struct inode *inode, struct file *filp ) 
{
  printk( "open device\n" );
  return 0;
}

static int vsend_release( struct inode *inode, struct file *filp )
{
  printk( "release device\n" );
  return 0;
}

static struct file_operations fops = {
  .open = vsend_open,
  .release = vsend_release,
  .unlocked_ioctl = vsend_ioctl
};

static int virtvsend_probe(struct virtio_device *vdev)
{
	//struct virtio_vsend *vsend;
	
	return 0;
}

static void virtvsend_remove(struct virtio_device *vdev)
{

}

static const struct virtio_device_id id_table[] = {
	{ 13, VIRTIO_DEV_ANY_ID },
	{ 0 },	
	/*
	{ VIRTIO_ID_BLOCK, VIRTIO_DEV_ANY_ID },
	{ 0 },
	*/
};

static unsigned int features[] = {
	0
	/*	
	VIRTIO_BLK_F_SEG_MAX, VIRTIO_BLK_F_SIZE_MAX, VIRTIO_BLK_F_GEOMETRY,
	VIRTIO_BLK_F_RO, VIRTIO_BLK_F_BLK_SIZE, VIRTIO_BLK_F_SCSI,
	VIRTIO_BLK_F_WCE, VIRTIO_BLK_F_TOPOLOGY, VIRTIO_BLK_F_CONFIG_WCE
	*/
};

static void virtvsend_config_changed(struct virtio_device *vdev)
{
	//struct virtio_vsend *vsend = vdev->priv;
}

static struct virtio_driver virtio_vsend_driver = {
	.feature_table		= features,
	.feature_table_size	= ARRAY_SIZE(features),
	.driver.name		= KBUILD_MODNAME,
	.driver.owner		= THIS_MODULE,
	.id_table			= id_table,
	.probe				= virtvsend_probe,
	.remove				= virtvsend_remove,
	.config_changed		= virtvsend_config_changed,
//#ifdef CONFIG_PM
	//.freeze			= virtblk_freeze,
	//.restore		= virtblk_restore,
//#endif
};

int vsend_init( void )
{
	int error;
	
	register_chrdev( MAJOR_NUMBER, DEVICE_NAME, &fops );
	error= register_virtio_driver(&virtio_vsend_driver);
	if (error)
	{
		unregister_chrdev( MAJOR_NUMBER,DEVICE_NAME );
		printk("module exit\n");
		return error;	
	}
	printk("module init\n");

	return 0;
}

void vsend_exit( void )
{
	unregister_chrdev( MAJOR_NUMBER,DEVICE_NAME );
	unregister_virtio_driver(&virtio_vsend_driver);
	printk("module exit\n");
}

module_init( vsend_init );
module_exit( vsend_exit );

MODULE_LICENSE( "GPL" );
