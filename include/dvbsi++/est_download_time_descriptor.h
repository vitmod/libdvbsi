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

#ifndef __est_download_time_descriptor_h__
#define __est_download_time_descriptor_h__

#include "descriptor.h"

class EstDownloadTimeDescriptor : public Descriptor
{
	protected:
		unsigned estDownloadTime			: 32;

	public:
		EstDownloadTimeDescriptor(const uint8_t * const buffer);

		uint32_t getEstDownloadTime(void) const;
};

#endif /* __est_download_time_descriptor_h__ */
