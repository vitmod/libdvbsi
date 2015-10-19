/*
 * $Id$
 *
 * Copyright (C) 2002-2005 Andreas Oberritter <obi@saftware.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * See the file 'COPYING' in the top level directory for details.
 */

#include <dvbsi++/application_information_section.h>
#include <dvbsi++/byte_stream.h>

ApplicationInformation::ApplicationInformation(const uint8_t * const buffer)
{
	unsigned int length;

	applicationIdentifier = new ApplicationIdentifier(&buffer[0]);
	applicationControlCode = buffer[6];
	applicationDescriptorsLoopLength = DVB_LENGTH(&buffer[7]);

	for (size_t i = 0; i < applicationDescriptorsLoopLength; i += length) {
		if (i + 2 > applicationDescriptorsLoopLength)
			break;
		length = buffer[i + 10] + 2;
		if (i + length > applicationDescriptorsLoopLength)
			break;
		descriptor(&buffer[i + 9], SCOPE_MHP);
	}
}

ApplicationInformation::~ApplicationInformation(void)
{
	delete applicationIdentifier;
}

const ApplicationIdentifier *ApplicationInformation::getApplicationIdentifier(void) const
{
	return applicationIdentifier;
}

uint8_t ApplicationInformation::getApplicationControlCode(void) const
{
	return applicationControlCode;
}

ApplicationInformationSection::ApplicationInformationSection(const uint8_t * const buffer) : LongCrcSection(buffer),
	commonDescriptorsLength(0),
	applicationLoopLength(0)
{
	unsigned int pos, length;

	if (sectionLength < 13)
		return;

	commonDescriptorsLength = DVB_LENGTH(&buffer[8]);
	if (sectionLength < 13 + commonDescriptorsLength)
		return;

	for (pos = 10; pos < 10 + commonDescriptorsLength; pos += length) {
		if (pos + 2 > 10 + commonDescriptorsLength)
			break;
		length = buffer[pos + 1] + 2;
		if (pos + length > 10 + commonDescriptorsLength)
			break;
		descriptor(&buffer[pos], SCOPE_MHP);
	}

	if (pos != 10 + commonDescriptorsLength)
		return;

	applicationLoopLength = DVB_LENGTH(&buffer[pos]);
	if (sectionLength < 13 + commonDescriptorsLength + applicationLoopLength)
		return;

	for (pos += 2; pos < 12 + commonDescriptorsLength + applicationLoopLength; pos += length) {
		if (pos + 9 > 12 + commonDescriptorsLength + applicationLoopLength)
			break;
		length = DVB_LENGTH(&buffer[pos + 7]) + 9;
		if (pos + length > 12 + commonDescriptorsLength + applicationLoopLength)
			break;
		applicationInformation.push_back(new ApplicationInformation(&buffer[pos]));
	}
}

ApplicationInformationSection::~ApplicationInformationSection(void)
{
	for (ApplicationInformationIterator i = applicationInformation.begin(); i != applicationInformation.end(); ++i)
		delete *i;
}

const ApplicationInformationList *ApplicationInformationSection::getApplicationInformation(void) const
{
	return &applicationInformation;
}

