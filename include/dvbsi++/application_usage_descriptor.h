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

#ifndef __application_usage_descriptor_h__
#define __application_usage_descriptor_h__

#include "descriptor.h"

class ApplicationUsageDescriptor : public Descriptor
{
	protected:
		unsigned usageType		: 8;

	public:
		ApplicationUsageDescriptor(const uint8_t * const buffer);

		uint8_t getUsageType(void) const;
};

#endif /* __application_usage_descriptor_h__ */
