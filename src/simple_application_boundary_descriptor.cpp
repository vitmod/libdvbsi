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

#include <dvbsi++/simple_application_boundary_descriptor.h>

BoundaryExtension::BoundaryExtension(const uint8_t * const buffer)
{
	boundaryExtension.assign((char *)&buffer[1], buffer[0]);
}

const std::string &BoundaryExtension::getBoundaryExtension(void) const
{
	return boundaryExtension;
}

SimpleApplicationBoundaryDescriptor::SimpleApplicationBoundaryDescriptor(const uint8_t * const buffer) : Descriptor(buffer)
{
	ASSERT_MIN_DLEN(1);
	size_t pos = 2;
	uint8_t boundary_extension_count = buffer[pos++];
	for (size_t i = 0; i < boundary_extension_count; ++i) {
		ASSERT_MIN_DLEN(pos - 1 + buffer[pos]);
		boundaryExtensions.push_back(new BoundaryExtension(&buffer[pos]));
		pos += buffer[pos] + 1;
	}
}

SimpleApplicationBoundaryDescriptor::~SimpleApplicationBoundaryDescriptor(void)
{
	for (BoundaryExtensionIterator i = boundaryExtensions.begin(); i != boundaryExtensions.end(); ++i)
		delete *i;
}

const BoundaryExtensionList *SimpleApplicationBoundaryDescriptor::getBoundaryExtensions(void) const
{
	return &boundaryExtensions;
}
