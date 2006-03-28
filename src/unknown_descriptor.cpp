/*
 * $Id$
 *
 * Copyright (C) 2005 Andreas Monzner <andreas.monzner@multimedia-labs.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * See the file 'COPYING' in the top level directory for details.
 */

#include <dvbsi++/unknown_descriptor.h>

UnknownDescriptor::UnknownDescriptor(const uint8_t * const buffer) : Descriptor(buffer)
{
}

