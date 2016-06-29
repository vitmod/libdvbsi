/*
 * Copyright (C) 2016 Andreas Oberritter <obi@saftware.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * See the file 'COPYING' in the top level directory for details.
 */

#include <dvbsi++/byte_stream.h>
#include <dvbsi++/t2_delivery_system_descriptor.h>

T2Subcell::T2Subcell(const uint8_t * const buffer)
{
	cellIdExtension = buffer[0];
	transposerFrequency = r32(&buffer[1]);
}

uint8_t T2Subcell::getCellIdExtension(void) const
{
	return cellIdExtension;
}

uint32_t T2Subcell::getTransposerFrequency(void) const
{
	return transposerFrequency;
}

T2Cell::T2Cell(const uint8_t * const buffer, bool tfsFlag)
{
	size_t i, pos = 2;

	cellId = r16(&buffer[0]);

	if (tfsFlag) {
		frequencyLoopLength = buffer[pos++];
		for (i = 0; i < frequencyLoopLength; i += 4)
			centreFrequencies.push_back(r32(&buffer[pos + i]));
		pos += frequencyLoopLength;
	} else {
		frequencyLoopLength = 0;
		centreFrequencies.push_back(r32(&buffer[pos]));
		pos += 4;
	}

	subcellInfoLoopLength = buffer[pos++];
	for (i = 0; i < subcellInfoLoopLength; i += 5)
		subcells.push_back(new T2Subcell(&buffer[pos + i]));
	pos += subcellInfoLoopLength;

	length = pos;
}

T2Cell::~T2Cell(void)
{
	for (T2SubcellIterator i = subcells.begin(); i != subcells.end(); ++i)
		delete *i;
}

uint16_t T2Cell::getCellId(void) const
{
	return cellId;
}

uint8_t T2Cell::getFrequencyLoopLength(void) const
{
	return frequencyLoopLength;
}

const T2FrequencyList *T2Cell::getCentreFrequencies(void) const
{
	return &centreFrequencies;
}

uint8_t T2Cell::getSubcellInfoLoopLength(void) const
{
	return subcellInfoLoopLength;
}

const T2SubcellList *T2Cell::getSubcells(void) const
{
	return &subcells;
}

uint8_t T2Cell::getLength() const
{
	return length;
}

T2DeliverySystemDescriptor::T2DeliverySystemDescriptor(const uint8_t * const buffer) : ExtensionDescriptor(buffer)
{
	T2Cell *cell;
	size_t pos;

	ASSERT_MIN_DLEN(4);

	plpId = buffer[3];
	t2SystemId = r16(&buffer[4]);

	if (descriptorLength > 4) {
		ASSERT_MIN_DLEN(6);
		sisoMiso = (buffer[6] >> 6) & 3;
		bandwidth = (buffer[6] >> 2) & 0xf;
		guardInterval = (buffer[7] >> 5) & 7;
		transmissionMode = (buffer[7] >> 2) & 7;
		otherFrequencyFlag = (buffer[7] >> 1) & 1;
		tfsFlag = buffer[7] & 1;
		for (pos = 8; pos < descriptorLength + 2; pos += cell->getLength()) {
			cell = new T2Cell(&buffer[pos], tfsFlag);
			cells.push_back(cell);
		}
	} else {
		sisoMiso = 0;
		bandwidth = 0;
		guardInterval = 0;
		transmissionMode = 0;
		otherFrequencyFlag = 0;
		tfsFlag = 0;
	}
}

T2DeliverySystemDescriptor::~T2DeliverySystemDescriptor(void)
{
	for (T2CellIterator i = cells.begin(); i != cells.end(); ++i)
		delete *i;
}

uint8_t T2DeliverySystemDescriptor::getPlpId(void) const
{
	return plpId;
}

uint16_t T2DeliverySystemDescriptor::getT2SystemId(void) const
{
	return t2SystemId;
}

uint8_t T2DeliverySystemDescriptor::getSisoMiso(void) const
{
	return sisoMiso;
}

uint8_t T2DeliverySystemDescriptor::getBandwidth(void) const
{
	return bandwidth;
}

uint8_t T2DeliverySystemDescriptor::getGuardInterval(void) const
{
	return guardInterval;
}

uint8_t T2DeliverySystemDescriptor::getTransmissionMode(void) const
{
	return transmissionMode;
}

bool T2DeliverySystemDescriptor::getOtherFrequencyFlag(void) const
{
	return otherFrequencyFlag;
}

bool T2DeliverySystemDescriptor::getTfsFlag(void) const
{
	return tfsFlag;
}

const T2CellList *T2DeliverySystemDescriptor::getCells(void) const
{
	return &cells;
}
