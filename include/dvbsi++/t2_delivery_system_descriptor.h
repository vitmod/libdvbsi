/*
 * Copyright (C) 2016 Andreas Oberritter <obi@saftware.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * See the file 'COPYING' in the top level directory for details.
 */

#ifndef __t2_delivery_system_descriptor_h__
#define __t2_delivery_system_descriptor_h__

#include "extension_descriptor.h"

typedef std::list<uint32_t> T2FrequencyList;
typedef T2FrequencyList::iterator T2FrequencyIterator;
typedef T2FrequencyList::const_iterator T2FrequencyConstIterator;

class T2Subcell
{
	protected:
		unsigned cellIdExtension			: 8;
		unsigned transposerFrequency			: 32;

	public:
		T2Subcell(const uint8_t * const buffer);

		uint8_t getCellIdExtension(void) const;
		uint32_t getTransposerFrequency(void) const;
};

typedef std::list<T2Subcell *> T2SubcellList;
typedef T2SubcellList::iterator T2SubcellIterator;
typedef T2SubcellList::const_iterator T2SubcellConstIterator;

class T2Cell
{
	protected:
		unsigned cellId					: 16;
		unsigned frequencyLoopLength			: 8;
		T2FrequencyList centreFrequencies;
		unsigned subcellInfoLoopLength			: 8;
		T2SubcellList subcells;

		uint8_t length;

	public:
		T2Cell(const uint8_t * const buffer, bool tfsFlag);
		~T2Cell(void);

		uint16_t getCellId(void) const;
		uint8_t getFrequencyLoopLength(void) const;
		const T2FrequencyList *getCentreFrequencies(void) const;
		uint8_t getSubcellInfoLoopLength(void) const;
		const T2SubcellList *getSubcells(void) const;

		uint8_t getLength() const;
};

typedef std::list<T2Cell *> T2CellList;
typedef T2CellList::iterator T2CellIterator;
typedef T2CellList::const_iterator T2CellConstIterator;

class T2DeliverySystemDescriptor : public ExtensionDescriptor
{
	protected:
		unsigned plpId					: 8;
		unsigned t2SystemId				: 16;
		unsigned sisoMiso				: 2;
		unsigned bandwidth				: 4;
		unsigned guardInterval				: 3;
		unsigned transmissionMode			: 3;
		unsigned otherFrequencyFlag			: 1;
		unsigned tfsFlag				: 1;
		T2CellList cells;

	public:
		T2DeliverySystemDescriptor(const uint8_t * const buffer);
		~T2DeliverySystemDescriptor(void);

		uint8_t getPlpId(void) const;
		uint16_t getT2SystemId(void) const;
		uint8_t getSisoMiso(void) const;
		uint8_t getBandwidth(void) const;
		uint8_t getGuardInterval(void) const;
		uint8_t getTransmissionMode(void) const;
		bool getOtherFrequencyFlag(void) const;
		bool getTfsFlag(void) const;

		const T2CellList *getCells(void) const;
};

#endif /* __t2_delivery_system_descriptor_h__ */
