// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * MDIO SMBus bridge
 *
 * Copyright (C) 2020 Antoine Tenart
 *
 * Network PHYs can appear on SMBus when they are part of SFP modules.
 */
#include <linux/i2c.h>
#include <linux/phy.h>

#include "mdio-i2c.h"

static int smbus_mii_read(struct mii_bus *mii, int phy_id, int reg)
{
	struct i2c_adapter *i2c = mii->priv;
	union i2c_smbus_data data;
	int ret;

	ret = i2c_smbus_xfer(i2c, i2c_mii_phy_addr(phy_id), 0, I2C_SMBUS_READ,
			     reg, I2C_SMBUS_BYTE_DATA, &data);
	if (ret < 0)
		return 0xff;

	return data.byte;
}

static int smbus_mii_write(struct mii_bus *mii, int phy_id, int reg, u16 val)
{
	struct i2c_adapter *i2c = mii->priv;
	union i2c_smbus_data data;
	int ret;

	data.byte = val;

	ret = i2c_smbus_xfer(i2c, i2c_mii_phy_addr(phy_id), 0, I2C_SMBUS_WRITE,
			     reg, I2C_SMBUS_BYTE_DATA, &data);
	return ret < 0 ? ret : 0;
}

struct mii_bus *mdio_smbus_alloc(struct device *parent, struct i2c_adapter *i2c)
{
	struct mii_bus *mii;

	if (!i2c_check_functionality(i2c, I2C_FUNC_SMBUS_BYTE_DATA))
		return ERR_PTR(-EINVAL);

	mii = mdiobus_alloc();
	if (!mii)
		return ERR_PTR(-ENOMEM);

	snprintf(mii->id, MII_BUS_ID_SIZE, "smbus:%s", dev_name(parent));
	mii->parent = parent;
	mii->read = smbus_mii_read;
	mii->write = smbus_mii_write;
	mii->priv = i2c;

	return mii;
}

MODULE_AUTHOR("Antoine Tenart");
MODULE_DESCRIPTION("MDIO SMBus bridge library");
MODULE_LICENSE("GPL");
