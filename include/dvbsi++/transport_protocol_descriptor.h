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
 
#ifndef __transport_protocol_descriptor_h__
#define __transport_protocol_descriptor_h__

#include "descriptor.h"

class OcTransport
{
	protected:
		unsigned remoteConnection			: 1;
		unsigned originalNetworkId			: 16;
		unsigned transportStreamId			: 16;
		unsigned serviceId				: 16;
		unsigned componentTag				: 8;

	public:
		OcTransport(const uint8_t * const buffer);

		uint8_t getRemoteConnection(void) const;
		uint16_t getOriginalNetworkId(void) const;
		uint16_t getTransportStreamId(void) const;
		uint16_t getServiceId(void) const;
		uint8_t getComponentTag(void) const;
};

class Url
{
	protected:
		unsigned urlLength				: 8;
		std::string url;

	public:
		Url(const uint8_t * const buffer);

		uint8_t getLength(void) const;
		const std::string &getUrl(void) const;
};

typedef std::list<Url *> UrlList;
typedef UrlList::iterator UrlIterator;
typedef UrlList::const_iterator UrlConstIterator;

class IpTransport
{
	protected:
		unsigned remoteConnection			: 1;
		unsigned originalNetworkId			: 16;
		unsigned transportStreamId			: 16;
		unsigned serviceId				: 16;
		unsigned alignmentIndicator			: 1;
		UrlList urls;

	public:
		IpTransport(const uint8_t * const buffer, size_t length);
		~IpTransport(void);

		uint8_t getRemoteConnection(void) const;
		uint16_t getOriginalNetworkId(void) const;
		uint16_t getTransportStreamId(void) const;
		uint16_t getServiceId(void) const;
		uint8_t getAlignmentIndicator(void) const;
		const UrlList *getUrls(void) const;
};

class InteractionTransport
{
	protected:
		Url *urlBase;
		UrlList urlExtensions;

	public:
		InteractionTransport(const uint8_t * const buffer, size_t &length);
		~InteractionTransport(void);

		const Url *getUrlBase(void) const;
		const UrlList *getUrlExtensions(void) const;
};

typedef std::list<InteractionTransport*> InteractionTransportList;
typedef InteractionTransportList::iterator InterActionTransportIterator;
typedef InteractionTransportList::const_iterator InterActionTransportConstIterator;

class TransportProtocolDescriptor : public Descriptor
{
	protected:
		unsigned protocolId				: 16;
		unsigned transportProtocolLabel			: 8;
		OcTransport *ocTransport;
		IpTransport *ipTransport;
		InteractionTransportList interactionTransports;

	public:
		TransportProtocolDescriptor(const uint8_t * const buffer);
		~TransportProtocolDescriptor(void);

		uint16_t getProtocolId(void) const;
		uint8_t getTransportProtocolLabel(void) const;
		const OcTransport *getOcTransport(void) const;
		const IpTransport *getIpTransport(void) const;
		const InteractionTransportList *getInteractionTransports(void) const;
};

#endif /* __transport_protocol_descriptor_h__ */
