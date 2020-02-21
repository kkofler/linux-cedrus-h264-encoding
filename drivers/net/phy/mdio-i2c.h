/* SPDX-License-Identifier: GPL-2.0 */
/*
 * MDIO I2C bridge
 *
 * Copyright (C) 2015 Russell King
 */
#ifndef MDIO_I2C_H
#define MDIO_I2C_H

struct device;
struct i2c_adapter;
struct mii_bus;

struct mii_bus *mdio_i2c_alloc(struct device *parent, struct i2c_adapter *i2c);
struct mii_bus *mdio_smbus_alloc(struct device *parent, struct i2c_adapter *i2c);

/*
 * I2C bus addresses 0x50 and 0x51 are normally an EEPROM, which is
 * specified to be present in SFP modules.  These correspond with PHY
 * addresses 16 and 17.  Disallow access to these "phy" addresses.
 */
static inline bool i2c_mii_valid_phy_id(int phy_id)
{
	return phy_id != 0x10 && phy_id != 0x11;
}

static inline unsigned int i2c_mii_phy_addr(int phy_id)
{
	return phy_id + 0x40;
}

#endif
