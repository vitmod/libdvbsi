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

#include <dvbsi++/transport_protocol_descriptor.h>
#include <dvbsi++/byte_stream.h>

OcTransport::OcTransport(const uint8_t * const buffer)
{
	remoteConnection = (buffer[0] >> 7) & 0x01;
	if (remoteConnection) {
		originalNetworkId = r16(&buffer[1]);
		transportStreamId = r16(&buffer[3]);
		serviceId = r16(&buffer[5]);
		componentTag = buffer[7];
	}
	else {
		originalNetworkId =
		transportStreamId =
		serviceId = 0;
		componentTag = buffer[1];
	}
}

uint8_t OcTransport::getRemoteConnection(void) const
{
	return remoteConnection;
}

uint16_t OcTransport::getOriginalNetworkId(void) const
{
	return originalNetworkId;
}

uint16_t OcTransport::getTransportStreamId(void) const
{
	return transportStreamId;
}

uint16_t OcTransport::getServiceId(void) const
{
	return serviceId;
}

uint8_t OcTransport::getComponentTag(void) const
{
	return componentTag;
}

Url::Url(const uint8_t * const buffer)
{	urlLength = buffer[0];
	url.assign((const char*)&buffer[1], urlLength);
}

uint8_t Url::getLength(void) const
{
	return urlLength;
}

const std::string &Url::getUrl(void) const
{
	return url;
}

IpTransport::IpTransport(const uint8_t * const buffer, size_t length)
{
	int pos = 0;
	remoteConnection = (buffer[pos++] >> 7) & 0x01;
	if (remoteConnection) {
		originalNetworkId = r16(&buffer[pos]);
		transportStreamId = r16(&buffer[pos+2]);
		serviceId = r16(&buffer[pos+4]);
		pos += 6;
	}
	else {
		originalNetworkId =
		transportStreamId =
		serviceId = 0;
	}
	alignmentIndicator = (buffer[pos++] >> 7) & 0x01;
	while (pos < length) {
		Url *url = new Url(&buffer[pos]);
		urls.push_back(url);
		pos += url->getLength() + 1;
	}
}

IpTransport::~IpTransport(void)
{
	for (UrlIterator i = urls.begin(); i != urls.end(); ++i)
		delete *i;
}

uint8_t IpTransport::getRemoteConnection(void) const
{
	return remoteConnection;
}

uint16_t IpTransport::getOriginalNetworkId(void) const
{
	return originalNetworkId;
}

uint16_t IpTransport::getTransportStreamId(void) const
{
	return transportStreamId;
}

uint16_t IpTransport::getServiceId(void) const
{
	return serviceId;
}

uint8_t IpTransport::getAlignmentIndicator(void) const
{
	return alignmentIndicator;
}

const UrlList *IpTransport::getUrls(void) const
{
	return &urls;
}

InteractionTransport::InteractionTransport(const uint8_t * const buffer, size_t &length)
{
	int pos = 0;
	urlBase = new Url(&buffer[pos]);
	pos += urlBase->getLength() + 1;
	length -= pos;
	if (pos > 1 && length > 0) {
		int num_extensions = buffer[pos++];
		length -= 1;
		pos += 1;
		for (size_t i = 0; i < num_extensions && length > 0; ++i) {
			Url *urlExtension = new Url(&buffer[pos]);
			int bytes = urlExtension->getLength() + 1;
			length -= bytes;
			pos += bytes;
			urlExtensions.push_back(urlExtension);
		}
	}
}

InteractionTransport::~InteractionTransport(void)
{
	delete urlBase;
	for (UrlIterator i = urlExtensions.begin(); i != urlExtensions.end(); ++i)
		delete *i;
}

const Url *InteractionTransport::getUrlBase(void) const
{
	return urlBase;
}

const UrlList *InteractionTransport::getUrlExtensions(void) const
{
	return &urlExtensions;
}

TransportProtocolDescriptor::TransportProtocolDescriptor(const uint8_t * const buffer) : Descriptor(buffer)
{
	ASSERT_MIN_DLEN(5);

	protocolId = r16(&buffer[2]);
	transportProtocolLabel = buffer[4];
	switch (protocolId) {
		case 0x0001:
			if (buffer[5] & 0x80)
				ASSERT_MIN_DLEN(11);
			ocTransport = new OcTransport(&buffer[5]);
			break;
		case 0x0002:
			if (buffer[5] & 0x80)
				ASSERT_MIN_DLEN(11);
			ipTransport = new IpTransport(&buffer[5], descriptorLength - 5);
			break;
		case 0x0003:
		{
			size_t bytesLeft = descriptorLength - 3;
			int pos = 5;
			while (bytesLeft > 0 && valid) {
				int oldBytesLeft = bytesLeft;
				InteractionTransport *p = new InteractionTransport(&buffer[pos], bytesLeft);
				interactionTransports.push_back(p);
				if (!p->getUrlBase()->getLength())
					valid = false;
				pos += bytesLeft - oldBytesLeft;
			}
			break;
		}
	}
}

TransportProtocolDescriptor::~TransportProtocolDescriptor(void)
{
	switch (protocolId) {
		case 0x0001:
			delete ocTransport;
			break;
		case 0x0002:
			delete ipTransport;
			break;
		case 0x0003:
			for (InterActionTransportIterator it(interactionTransports.begin()); it != interactionTransports.end(); ++it)
				delete *it;
			break;
	}
}

uint16_t TransportProtocolDescriptor::getProtocolId(void) const
{
	return protocolId;
}

uint8_t TransportProtocolDescriptor::getTransportProtocolLabel(void) const
{
	return transportProtocolLabel;
}

const OcTransport *TransportProtocolDescriptor::getOcTransport(void) const
{
	return ocTransport;
}

const IpTransport *TransportProtocolDescriptor::getIpTransport(void) const
{
	return ipTransport;
}

const InteractionTransportList *TransportProtocolDescriptor::getInteractionTransports(void) const
{
	return &interactionTransports;
}
