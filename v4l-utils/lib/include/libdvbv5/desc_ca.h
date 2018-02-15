/*
 * Copyright (c) 2013 - Andre Roth <neolynx@gmail.com>
 *
<<<<<<< HEAD
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation version 2.1 of the License.
=======
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
<<<<<<< HEAD
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
=======
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * Or, point your browser to http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 *
 * Described at ETSI EN 300 468 V1.11.1 (2010-04)
 */

<<<<<<< HEAD
/**
 * @file desc_ca.h
 * @ingroup descriptors
 * @brief Provides the descriptors for Conditional Access
 * @copyright GNU Lesser General Public License version 2.1 (LGPLv2.1)
 * @author Andre Roth
 *
 * @par Relevant specs
 * The descriptor described herein is defined at:
 * - ETSI EN 300 468 V1.11.1 (2010-04)
 *
 * @see http://www.etherguidesystems.com/help/sdos/mpeg/semantics/mpeg-2/descriptors/CA_descriptor.aspx
 *
 * @par Bug Report
 * Please submit bug reports and patches to linux-media@vger.kernel.org
 */

=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
#ifndef _CA_H
#define _CA_H

#include <libdvbv5/descriptors.h>

<<<<<<< HEAD
/**
 * @struct dvb_desc_ca
 * @ingroup descriptors
 * @brief Contains the private data for Conditional Access
 *
 * @param type			descriptor tag
 * @param length		descriptor length
 * @param next			pointer to struct dvb_desc
 * @param ca_id			Conditional Access ID
 * @param ca_pid		Conditional Access ID
 * @param privdata		pointer to private data buffer
 * @param privdata_len		length of the private data
 */
struct dvb_desc_ca {
	uint8_t type;
	uint8_t length;
	struct dvb_desc *next;
=======
struct dvb_desc_ca {
	DVB_DESC_HEADER();
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2

	uint16_t ca_id;
	union {
		uint16_t bitfield1;
		struct {
			uint16_t ca_pid:13;
			uint16_t reserved:3;
		} __attribute__((packed));
	} __attribute__((packed));

	uint8_t *privdata;
	uint8_t privdata_len;
} __attribute__((packed));

struct dvb_v5_fe_parms;

<<<<<<< HEAD
/** @brief initial descriptor field at dvb_desc_ca struct */
#define dvb_desc_ca_field_first ca_id
/** @brief last descriptor field at dvb_desc_ca struct */
=======
#define dvb_desc_ca_field_first ca_id
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
#define dvb_desc_ca_field_last  privdata

#ifdef __cplusplus
extern "C" {
#endif

<<<<<<< HEAD
/**
 * @brief Initializes and parses the CA descriptor
 * @ingroup descriptors
 *
 * @param parms	struct dvb_v5_fe_parms pointer to the opened device
 * @param buf	buffer containing the descriptor's raw data
 * @param desc	pointer to struct dvb_desc to be allocated and filled
 *
 * This function allocates a the descriptor and fills the fields inside
 * the struct. It also makes sure that all fields will follow the CPU
 * endianness. Due to that, the content of the buffer may change.
 *
 * @return On success, it returns the size of the allocated struct.
 *	   A negative value indicates an error.
 */
int dvb_desc_ca_init(struct dvb_v5_fe_parms *parms, const uint8_t *buf,
		      struct dvb_desc *desc);

/**
 * @brief Prints the content of the CA descriptor
 * @ingroup descriptors
 *
 * @param parms	struct dvb_v5_fe_parms pointer to the opened device
 * @param desc	pointer to struct dvb_desc
 */
void dvb_desc_ca_print(struct dvb_v5_fe_parms *parms,
		       const struct dvb_desc *desc);

/**
 * @brief Frees all data allocated by the CA descriptor
 * @ingroup descriptors
 *
 * @param desc pointer to struct dvb_desc to be freed
 */
void dvb_desc_ca_free(struct dvb_desc *desc);
=======
int dvb_desc_ca_init (struct dvb_v5_fe_parms *parms, const uint8_t *buf, struct dvb_desc *desc);
void dvb_desc_ca_print(struct dvb_v5_fe_parms *parms, const struct dvb_desc *desc);
void dvb_desc_ca_free (struct dvb_desc *desc);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2

#ifdef __cplusplus
}
#endif

#endif
