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

#include <dvbsi++/simple_application_location_descriptor.h>

SimpleApplicationLocationDescriptor::SimpleApplicationLocationDescriptor(const uint8_t * const buffer) : Descriptor(buffer)
{
	initial_path.assign((char *)&buffer[2], descriptorLength);
}

const std::string &SimpleApplicationLocationDescriptor::getInitialPath(void) const
{
	return initial_path;
}
