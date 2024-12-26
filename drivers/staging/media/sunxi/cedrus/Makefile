# SPDX-License-Identifier: GPL-2.0
obj-$(CONFIG_VIDEO_SUNXI_CEDRUS) += sunxi-cedrus.o

sunxi-cedrus-y = cedrus.o \
		 cedrus_context.o \
		 cedrus_dec.o \
		 cedrus_dec_h264.o \
		 cedrus_dec_h265.o \
		 cedrus_dec_mpeg2.o \
		 cedrus_dec_vp8.o \
		 cedrus_enc.o \
		 cedrus_enc_h264.o \
		 cedrus_engine.o \
		 cedrus_proc.o

KERN_DIR=/lib/modules/$(shell uname -r)/build/

host:
	make -C $(KERN_DIR) M=$(PWD) CONFIG_VIDEO_SUNXI_CEDRUS=m modules
clean:
	make -C $(KERN_DIR) M=$(PWD) CONFIG_VIDEO_SUNXI_CEDRUS=m clean
help:
	make -C $(KERN_DIR) M=$(PWD) CONFIG_VIDEO_SUNXI_CEDRUS=m help
