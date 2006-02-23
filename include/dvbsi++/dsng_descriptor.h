/*
 *  $Id$
 *
 *  Copyright (C) 2006 Marcel Siegert <mws@twisted-brains.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * See the file 'COPYING' in the top level directory for details.
 */
#ifndef __dsng_descriptor_h__
#define __dsng_descriptor_h__

#include "descriptor.h"

typedef std::vector<uint8_t> PrivateDataByteVector;
typedef PrivateDataByteVector::iterator PrivateDataByteIterator;
typedef PrivateDataByteVector::const_iterator PrivateDataByteConstIterator;

class DSNGDescriptor : public Descriptor
{
	protected:
		PrivateDataByteVector privateDataBytes;

	public:
		DSNGDescriptor(const uint8_t* const buffer);
		virtual ~DSNGDescriptor();

		const PrivateDataByteVector* getPrivateDataBytes(void) const;
};

#endif /* __dsng_descriptor_h__ */
