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

#ifndef __simple_application_location_descriptor_h__
#define __simple_application_location_descriptor_h__

#include "descriptor.h"

class SimpleApplicationLocationDescriptor : public Descriptor
{
	protected:
		std::string initial_path;

	public:
		SimpleApplicationLocationDescriptor(const uint8_t * const buffer);

		const std::string &getInitialPath(void) const;
};

#endif /* __simple_application_location_descriptor_h__ */
