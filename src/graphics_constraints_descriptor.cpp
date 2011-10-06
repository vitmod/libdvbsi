/*
 * $Id$
 *
 * Copyright (C) 2011 Andreas Monzner <Andreas.Monzner@dream-property.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * See the file 'COPYING' in the top level directory for details.
 */

#include <dvbsi++/graphics_constraints_descriptor.h>

GraphicsConstraintsDescriptor::GraphicsConstraintsDescriptor(const uint8_t * const buffer) : Descriptor(buffer)
	,graphicsConfigurationBytes(descriptorLength > 1 ? descriptorLength - 1 : 0)
{
	ASSERT_MIN_DLEN(1);
	u.flags = buffer[2];
	if (descriptorLength > 1)
		graphicsConfigurationBytes.assign(&buffer[3], &buffer[3 + descriptorLength - 1]);
}
