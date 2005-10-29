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

#ifndef __content_type_descriptor_h__
#define __content_type_descriptor_h__

#include "descriptor.h"

class ContentTypeDescriptor : public Descriptor
{
	protected:
		std::string contentType;

	public:
		ContentTypeDescriptor(const uint8_t * const buffer);

		const std::string &getContentType(void) const;
};

#endif /* __content_type_descriptor_h__ */
