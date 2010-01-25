/*
 * $Id$
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * See the file 'COPYING' in the top level directory for details.
 */

#ifndef __logical_channel_descriptor_h__
#define __logical_channel_descriptor_h__

#include "descriptor.h"

class LogicalChannel
{
protected:
	unsigned serviceId : 16;
	unsigned visibleServiceFlag : 1;
	unsigned logicalChannelNumber : 10;

public:
	LogicalChannel(const uint8_t *const buffer);
	~LogicalChannel(void);

	uint16_t getServiceId(void) const;
	uint8_t getVisibleServiceFlag(void) const;
	uint16_t getLogicalChannelNumber(void) const;
};

typedef std::list<LogicalChannel *> LogicalChannelList;
typedef LogicalChannelList::iterator LogicalChannelListIterator;
typedef LogicalChannelList::const_iterator LogicalChannelListConstIterator;

class LogicalChannelDescriptor : public Descriptor
{
protected:
	LogicalChannelList channelList;

public:
	LogicalChannelDescriptor(const uint8_t *const buffer);
	~LogicalChannelDescriptor(void);

	const LogicalChannelList *getChannelList(void) const;
};

#endif /* __logical_channel_descriptor_h__ */
