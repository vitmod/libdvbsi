/*
 * $Id$
 *
 * Copyright (C) 2011 Andreas Monzner <andreas.monzner@dream-property.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * See the file 'COPYING' in the top level directory for details.
 */
#include <dvbsi++/application_usage_descriptor.h>

ApplicationUsageDescriptor::ApplicationUsageDescriptor(const uint8_t* const buffer) : Descriptor(buffer)
{
	ASSERT_MIN_DLEN(1);
	usageType = buffer[2];
}

uint8_t ApplicationUsageDescriptor::getUsageType(void) const
{
	return usageType;
}
