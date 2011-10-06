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

#ifndef __graphics_constraints_descriptor_h__
#define __graphics_constraints_descriptor_h__

#include "descriptor.h"

typedef std::vector<uint8_t> GraphicsConfigurationByteVector;
typedef GraphicsConfigurationByteVector::iterator GraphicsConfigurationByteIterator;
typedef GraphicsConfigurationByteVector::const_iterator GraphicsConfigurationByteConstIterator;

class GraphicsConstraintsDescriptor : public Descriptor
{
	protected:
		union {
			struct {
				unsigned reserved				: 5;
				unsigned canRunWithoutVisibleUi			: 1;
				unsigned handlesConfigurationChanged		: 1;
				unsigned handlesExternallyControlledVideo	: 1;
			} s;
			uint8_t flags;
		} u;
		GraphicsConfigurationByteVector graphicsConfigurationBytes;

	public:
		GraphicsConstraintsDescriptor(const uint8_t * const buffer);

		bool canRunWithoutVisibleUi(void) const { return u.s.canRunWithoutVisibleUi; };
		bool handlesConfigurationChanged(void) const { return u.s.handlesConfigurationChanged; };
		bool handlesExternallyControlledVideo(void) const { return u.s.handlesExternallyControlledVideo; };
		const GraphicsConfigurationByteVector *getGraphicsConfigurationBytes(void) const { return &graphicsConfigurationBytes; }
};

#endif /* __graphics_constraints_descriptor_h__ */
