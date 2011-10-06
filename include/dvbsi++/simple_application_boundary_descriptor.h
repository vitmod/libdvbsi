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

#ifndef __simple_application_boundary_descriptor_h__
#define __simple_application_boundary_descriptor_h__

#include "descriptor.h"

class BoundaryExtension
{
	protected:
		std::string boundaryExtension;

	public:
		BoundaryExtension(const uint8_t * const buffer);

		const std::string &getBoundaryExtension(void) const;
};

typedef std::list<BoundaryExtension *> BoundaryExtensionList;
typedef BoundaryExtensionList::iterator BoundaryExtensionIterator;
typedef BoundaryExtensionList::const_iterator BoundaryExtensionConstIterator;

class SimpleApplicationBoundaryDescriptor : public Descriptor
{
	protected:
		BoundaryExtensionList boundaryExtensions;

	public:
		SimpleApplicationBoundaryDescriptor(const uint8_t * const buffer);
		~SimpleApplicationBoundaryDescriptor(void);

		const BoundaryExtensionList *getBoundaryExtensions(void) const;
};

#endif /*  __simple_application_boundary_descriptor_h__ */
