/*
 * $Id$
 *
 * Copyright (C) 2004-2005 Stéphane Esté-Gracias <sestegra@free.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * See the file 'COPYING' in the top level directory for details.
 */

#ifndef __module_link_descriptor_h__
#define __module_link_descriptor_h__

#include "descriptor.h"

class ModuleLinkDescriptor : public Descriptor
{
	protected:
		unsigned position				: 8;
		unsigned moduleId				: 16;

	public:
		ModuleLinkDescriptor(const uint8_t * const buffer);

		uint8_t getPosition(void) const;
		uint16_t getModuleId(void) const;
};

#endif /* __module_link_descriptor_h__ */
