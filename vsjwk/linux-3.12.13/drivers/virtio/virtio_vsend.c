
#include "linux/virtio.h"
#include "linux/virtio_ids.h"
#include "linux/virtio_pci.h"
#include "virtio.h"

static struct virtio_device_id id_table[] = {
	{VIRTIO_ID_vsend, VIRTIO_DEV_ANY_ID},{0}
};

struct virtio_vsend {
	int size;
	void* data;
	void* mapbuf;
	struct semaphore sem;
	struct cdev cdev;
	struct virtio_device *vdev;
	struct virtqueue *vq[2];
} my_cdev;

static struct virtio_driver virtio_vsend_driver = {
	.feature_table		= features,
	.feature_table_size	= ARRAY_SIZE(features),
	.driver.name		= KBUILD_MODNAME,
	.driver.owner		= THIS_MODULE,
	.id_table			= id_table,
	.probe				= my_probe,
	.remove				= __devexit_p(my_remove),
};

register_virtio_driver(&virtio_vsend_driver);
unregister_virtio_driver(&virtio_vsend_driver);

