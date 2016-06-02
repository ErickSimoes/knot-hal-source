/*
 * Copyright (c) 2015, CESAR.
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license. See the LICENSE file for details.
 *
 */
#include <stdint.h>

#ifndef __NRF24L01_PROTO_NET_H__
#define __NRF24L01_PROTO_NET_H__

// protocol version
#define NRF24_VERSION_MAJOR	1
#define NRF24_VERSION_MINOR	0

// application packet size maximum
#define NRF24_APP_PACKET_SIZE_MAX		128

// net layer result codes
#define NRF24_SUCCESS						0
#define NRF24_ERROR							-1
#define NRF24_INVALID_VERSION		-2
#define NRF24_ECONNREFUSED		-3

// Network retransmiting parameters
#define NRF24_TIMEOUT_MS								45
#define NRF24_HEARTBEAT_SEND_MS			1000
#define NRF24_HEARTBEAT_TIMEOUT_MS		(NRF24_HEARTBEAT_SEND_MS * 2)
#define NRF24_RETRIES											200

// Network messages
#define NRF24_GATEWAY_REQ	0x00
#define NRF24_JOIN_LOCAL			0x01
#define NRF24_UNJOIN_LOCAL	0x02
#define NRF24_HEARTBEAT			0x03
#define NRF24_APP							0x04
#define NRF24_APP_FIRST			0x05
#define NRF24_APP_FRAG				0x06

/**
 * struct hdr_t - net layer message header
 * @net_addr: net address
 * @msg_type: message type
 * @offset: message fragment offset
 *
 * This struct defines the network layer message header
 */
typedef struct __attribute__ ((packed)) {
	uint16_t		net_addr;
	uint8_t		msg_type;
} hdr_t;

// Network message size parameters
#define NRF24_PW_SIZE							32
#define NRF24_PW_MSG_SIZE				(NRF24_PW_SIZE - sizeof(hdr_t))

/**
 * struct version_t - network layer version
 * @major: protocol version, major number
 * @minor: protocol version, minor number
 * @packet_size: application packet size maximum
 *
 * This struct defines the network layer version.
 */
typedef struct __attribute__ ((packed)) {
	uint8_t				major;
	uint8_t				minor;
	uint16_t				packet_size;
} version_t;

/**
 * struct join_t - network layer join message
 * @result: join process result
 * @version: network layer version
 * @hashid: id for network
 * @data: join data
 *
 * This struct defines the network layer join message.
 */
typedef struct __attribute__ ((packed)) {
	int8_t					result;
	version_t			version;
	uint32_t				hashid;
	uint32_t				data;
} join_t;

/**
 * union payload_t - defines a network layer payload
 * @hdr: net layer message header
 * @result: process result
 * @join: net layer join local message
 * @raw: raw data of network layer
 *
 * This union defines the network layer payload.
 */
typedef struct __attribute__ ((packed))  {
	hdr_t			hdr;
	union {
		int8_t		result;
		join_t		join;
		uint8_t	raw[NRF24_PW_MSG_SIZE];
	} msg;
} payload_t;

#endif //	__NRF24L01_PROTO_NET_H__
