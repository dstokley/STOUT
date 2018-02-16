/*
 * Copyright (c) 2013 - Mauro Carvalho Chehab <m.chehab@samsung.com>
 * Copyright (c) 2013 - Andre Roth <neolynx@gmail.com>
 *
<<<<<<< HEAD
<<<<<<< HEAD
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation version 2.1 of the License.
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation version 2.1 of the License.
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
<<<<<<< HEAD
<<<<<<< HEAD
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
=======
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
=======
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * Or, point your browser to http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 *
 */

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @file vct.h
 * @ingroup dvb_table
 * @brief Provides the descriptors for TVCT and CVCT tables
 * @copyright GNU Lesser General Public License version 2.1 (LGPLv2.1)
 * @author Mauro Carvalho Chehab
 * @author Andre Roth
 *
 * @par Relevant specs
 * The table described herein is defined at:
 * - ATSC A/65:2009
 *
 * @see http://www.etherguidesystems.com/help/sdos/atsc/syntax/tablesections/TVCT.aspx
 * @see http://www.etherguidesystems.com/help/sdos/atsc/syntax/tablesections/CVCT.aspx
 *
 * @par Bug Report
 * Please submit bug reports and patches to linux-media@vger.kernel.org
 */

<<<<<<< HEAD
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
#ifndef _VCT_H
#define _VCT_H

#include <stdint.h>
#include <unistd.h> /* ssize_t */

#include <libdvbv5/atsc_header.h>

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @def ATSC_TABLE_TVCT
 *	@brief TVCT table ID
 *	@ingroup dvb_table
 * @def ATSC_TABLE_CVCT
 *	@brief CVCT table ID
 *	@ingroup dvb_table
 * @def ATSC_TABLE_VCT_PID
 *	@brief Program ID with the VCT tables on it
 *	@ingroup dvb_table
 */
<<<<<<< HEAD
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
#define ATSC_TABLE_TVCT     0xc8
#define ATSC_TABLE_CVCT     0xc9
#define ATSC_TABLE_VCT_PID  0x1ffb

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @struct atsc_table_vct_channel
 * @brief ATSC VCT channel table (covers both CVCT and TVCT)
 * @ingroup dvb_table
 *
 * @param modulation_mode	modulation mode
 * @param minor_channel_number	minor channel number
 * @param major_channel_number	major channel number
 * @param carrier_frequency	carrier frequency
 * @param channel_tsid		channel tsid
 * @param program_number	program number
 * @param service_type		service type
 * @param hide_guide		hide guide
 * @param out_of_band		out of band (CVCT only)
 * @param path_select		path select (CVCT only)
 * @param hidden		hidden
 * @param access_controlled	access controlled
 * @param ETM_location		ETM location
 * @param source_id		source ID
 * @param descriptors_length	length of the descriptors
 *
 * @param descriptor		pointer to struct dvb_desc
 * @param next pointer to another struct atsc_table_vct_channel
 * @param descriptors_length	length of the descriptors
 * @param short_name		short name. The __short_name is converted
 *				from UTF-16 to locale charset when parsed
 *
 * This structure is used to store the original VCT channel table,
 * converting the integer fields to the CPU endianness.
 *
 * The undocumented parameters are used only internally by the API and/or
 * are fields that are reserved. They shouldn't be used, as they may change
 * on future API releases.
 *
 * Everything after atsc_table_vct_channel::descriptor (including it) won't
 * be bit-mapped * to the data parsed from the MPEG TS. So, metadata are
 * added there.
 */
<<<<<<< HEAD
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
struct atsc_table_vct_channel {
	uint16_t	__short_name[7];

	union {
		uint32_t bitfield1;
		struct {
			uint32_t	modulation_mode:8;
			uint32_t	minor_channel_number:10;
			uint32_t	major_channel_number:10;
			uint32_t	reserved1:4;
		} __attribute__((packed));
	} __attribute__((packed));

	uint32_t	carrier_frequency;
	uint16_t	channel_tsid;
	uint16_t	program_number;
	union {
		uint16_t bitfield2;
		struct {
			uint16_t	service_type:6;
			uint16_t	reserved2:3;
			uint16_t	hide_guide:1;
			uint16_t	out_of_band:1;	/* CVCT only */
			uint16_t	path_select:1;	/* CVCT only */
			uint16_t	hidden:1;
			uint16_t	access_controlled:1;
			uint16_t	ETM_location:2;

		} __attribute__((packed));
	} __attribute__((packed));

	uint16_t source_id;
	union {
		uint16_t bitfield3;
		struct {
			uint16_t descriptors_length:10;
			uint16_t reserved3:6;
		} __attribute__((packed));
	} __attribute__((packed));

	/*
<<<<<<< HEAD
<<<<<<< HEAD
	 * Everything after atsc_table_vct_channel::descriptor (including it)
	 * won't be bit-mapped to the data parsed from the MPEG TS. So,
	 * metadata are added there
=======
	 * Everything after descriptor (including it) won't be bit-mapped
	 * to the data parsed from the MPEG TS. So, metadata are added there
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	 * Everything after descriptor (including it) won't be bit-mapped
	 * to the data parsed from the MPEG TS. So, metadata are added there
=======
	 * Everything after atsc_table_vct_channel::descriptor (including it)
	 * won't be bit-mapped to the data parsed from the MPEG TS. So,
	 * metadata are added there
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	 */
	struct dvb_desc *descriptor;
	struct atsc_table_vct_channel *next;

	/* The channel_short_name is converted to locale charset by vct.c */

	char short_name[32];
} __attribute__((packed));

<<<<<<< HEAD
<<<<<<< HEAD
=======
struct atsc_table_vct {
	ATSC_HEADER();

	uint8_t num_channels_in_section;

	/*
	 * Everything after descriptor (including it) won't be bit-mapped
	 * to the data parsed from the MPEG TS. So, metadata are added there
	 */
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @struct atsc_table_vct
 * @brief ATSC VCT table (covers both CVCT and TVCT)
 * @ingroup dvb_table
 *
 * @param header			struct dvb_table_header content
 * @param protocol_version		protocol version
 * @param num_channels_in_section	num channels in section
 * @param channel			pointer to struct channel
 * @param descriptor			pointer to struct descriptor
 *
 * Everything after atsc_table_vct::channel (including it) won't be bit-mapped
 * to the data parsed from the MPEG TS. So, metadata are added there
 */
struct atsc_table_vct {
	struct dvb_table_header header;
	uint8_t  protocol_version;

	uint8_t num_channels_in_section;

<<<<<<< HEAD
=======
struct atsc_table_vct {
	ATSC_HEADER();

	uint8_t num_channels_in_section;

	/*
	 * Everything after descriptor (including it) won't be bit-mapped
	 * to the data parsed from the MPEG TS. So, metadata are added there
	 */
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	struct atsc_table_vct_channel *channel;
	struct dvb_desc *descriptor;
} __attribute__((packed));

<<<<<<< HEAD
<<<<<<< HEAD
=======

=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @union atsc_table_vct_descriptor_length
 * @brief ATSC VCT descriptor length
 * @ingroup dvb_table
 *
 * @param descriptor_length	descriptor length
 *
 * Used internally by the library to parse the descriptor length endianness.
 */
<<<<<<< HEAD
=======

>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
union atsc_table_vct_descriptor_length {
	uint16_t bitfield;
	struct {
		uint16_t descriptor_length:10;
		uint16_t reserved:6;
	} __attribute__((packed));
} __attribute__((packed));

<<<<<<< HEAD
<<<<<<< HEAD
=======
#define atsc_vct_channel_foreach(_channel, _vct) \
	for (struct atsc_table_vct_channel *_channel = _vct->channel; _channel; _channel = _channel->next) \
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @brief Macro used to find channels on a VCT table
 * @ingroup dvb_table
 *
 * @param _channel	channel to seek
 * @param _vct		pointer to struct atsc_table_vct_channel
 */
 #define atsc_vct_channel_foreach(_channel, _vct) \
	if (_vct && _vct->channel) \
		for (struct atsc_table_vct_channel *_channel = _vct->channel; _channel; _channel = _channel->next) \
<<<<<<< HEAD
=======
#define atsc_vct_channel_foreach(_channel, _vct) \
	for (struct atsc_table_vct_channel *_channel = _vct->channel; _channel; _channel = _channel->next) \
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

struct dvb_v5_fe_parms;

#ifdef __cplusplus
extern "C" {
#endif

<<<<<<< HEAD
<<<<<<< HEAD
=======
ssize_t atsc_table_vct_init (struct dvb_v5_fe_parms *parms, const uint8_t *buf, ssize_t buflen, struct atsc_table_vct **table);
void atsc_table_vct_free(struct atsc_table_vct *vct);
void atsc_table_vct_print(struct dvb_v5_fe_parms *parms, struct atsc_table_vct *vct);
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @brief Initializes and parses VCT table
 * @ingroup dvb_table
 *
 * @param parms	struct dvb_v5_fe_parms pointer to the opened device
 * @param buf buffer containing the VCT raw data
 * @param buflen length of the buffer
 * @param table pointer to struct atsc_table_vct to be allocated and filled
 *
 * This function allocates an ATSC VCT table and fills the fields inside
 * the struct. It also makes sure that all fields will follow the CPU
 * endianness. Due to that, the content of the buffer may change.
 *
 * @return On success, it returns the size of the allocated struct.
 *	   A negative value indicates an error.
 */
ssize_t atsc_table_vct_init(struct dvb_v5_fe_parms *parms, const uint8_t *buf,
			    ssize_t buflen, struct atsc_table_vct **table);
/**
 * @brief Frees all data allocated by the VCT table parser
 * @ingroup dvb_table
 *
 * @param table pointer to struct atsc_table_vct to be freed
 */
void atsc_table_vct_free(struct atsc_table_vct *table);
/**
 * @brief Prints the content of the VCT table
 * @ingroup dvb_table
 *
 * @param parms	struct dvb_v5_fe_parms pointer to the opened device
 * @param table pointer to struct atsc_table_vct
 */
void atsc_table_vct_print(struct dvb_v5_fe_parms *parms,
			  struct atsc_table_vct *table);
<<<<<<< HEAD
=======
ssize_t atsc_table_vct_init (struct dvb_v5_fe_parms *parms, const uint8_t *buf, ssize_t buflen, struct atsc_table_vct **table);
void atsc_table_vct_free(struct atsc_table_vct *vct);
void atsc_table_vct_print(struct dvb_v5_fe_parms *parms, struct atsc_table_vct *vct);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

#ifdef __cplusplus
}
#endif

#endif
