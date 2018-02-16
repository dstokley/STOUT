/*
 * Copyright (c) 2011-2012 - Mauro Carvalho Chehab
 * Copyright (c) 2012 - Andre Roth <neolynx@gmail.com>
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
 * Based on ETSI EN 300 468 V1.11.1 (2010-04)
 *
 */

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @file desc_terrestrial_delivery.h
 * @ingroup descriptors
 * @brief Provides the descriptors for the DVB-T terrestrial delivery system descriptor
 * @copyright GNU Lesser General Public License version 2.1 (LGPLv2.1)
 * @author Mauro Carvalho Chehab
 * @author Andre Roth
 *
 * @par Relevant specs
 * The descriptor described herein is defined at:
 * - ETSI EN 300 468 V1.11.1
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
#ifndef _TERRESTRIAL_DELIVERY_H
#define _TERRESTRIAL_DELIVERY_H

#include <libdvbv5/descriptors.h>

<<<<<<< HEAD
<<<<<<< HEAD
=======
struct dvb_desc_terrestrial_delivery {
	DVB_DESC_HEADER();
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @struct dvb_desc_terrestrial_delivery
 * @ingroup descriptors
 * @brief Structure containing the DVB-T terrestrial delivery system descriptor
 *
 * @param type			descriptor tag
 * @param length		descriptor length
 * @param next			pointer to struct dvb_desc
 * @param centre_frequency	centre frequency, multiplied by 10 Hz
 * @param bandwidth		bandwidth
 * @param priority		priority (0 = LP, 1 = HP)
 * @param time_slice_indicator	time slicing indicator
 * @param mpe_fec_indicator	mpe fec indicator. If 1, MPE-FEC is not used.
 * @param constellation		constellation
 * @param hierarchy_information	hierarchy information
 * @param code_rate_hp_stream	code rate hp stream
 * @param code_rate_lp_stream	code rate lp stream
 * @param guard_interval	guard interval
 * @param transmission_mode	transmission mode
 * @param other_frequency_flag	other frequency flag
 */
struct dvb_desc_terrestrial_delivery {
	uint8_t type;
	uint8_t length;
	struct dvb_desc *next;
<<<<<<< HEAD
=======
struct dvb_desc_terrestrial_delivery {
	DVB_DESC_HEADER();
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

	uint32_t centre_frequency;
	uint8_t reserved_future_use1:2;
	uint8_t mpe_fec_indicator:1;
	uint8_t time_slice_indicator:1;
	uint8_t priority:1;
	uint8_t bandwidth:3;
	uint8_t code_rate_hp_stream:3;
	uint8_t hierarchy_information:3;
	uint8_t constellation:2;
	uint8_t other_frequency_flag:1;
	uint8_t transmission_mode:2;
	uint8_t guard_interval:2;
	uint8_t code_rate_lp_stream:3;
	uint32_t reserved_future_use2;
} __attribute__((packed));

struct dvb_v5_fe_parms;

#ifdef __cplusplus
extern "C" {
#endif

<<<<<<< HEAD
<<<<<<< HEAD
=======
int dvb_desc_terrestrial_delivery_init (struct dvb_v5_fe_parms *parms, const uint8_t *buf, struct dvb_desc *desc);
void dvb_desc_terrestrial_delivery_print(struct dvb_v5_fe_parms *parms, const struct dvb_desc *desc);
extern const unsigned dvbt_bw[];
extern const unsigned dvbt_modulation[];
extern const unsigned dvbt_hierarchy[];
extern const unsigned dvbt_code_rate[];
extern const uint32_t dvbt_interval[];
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @brief Initializes and parses the DVB-T terrestrial delivery system descriptor
 *
 * @param parms	struct dvb_v5_fe_parms pointer to the opened device
 * @param buf	buffer containing the descriptor's raw data
 * @param desc	pointer to struct dvb_desc to be allocated and filled
 *
 * This function initializes and makes sure that all fields will follow the CPU
 * endianness. Due to that, the content of the buffer may change.
 *
 * Currently, no memory is allocated internally.
 *
 * @return On success, it returns the size of the allocated struct.
 *	   A negative value indicates an error.
 */
int dvb_desc_terrestrial_delivery_init(struct dvb_v5_fe_parms *parms,
				       const uint8_t *buf,
				       struct dvb_desc *desc);

/**
 * @brief Prints the content of the DVB-T terrestrial delivery system descriptor
 * @ingroup descriptors
 *
 * @param parms	struct dvb_v5_fe_parms pointer to the opened device
 * @param desc	pointer to struct dvb_desc
 */
void dvb_desc_terrestrial_delivery_print(struct dvb_v5_fe_parms *parms,
					 const struct dvb_desc *desc);

/**
 * @brief converts from internal representation into bandwidth in Hz
 */
extern const unsigned dvbt_bw[];

/**
 * @brief converts from the descriptor's modulation into enum fe_modulation,
 *	  as defined by DVBv5 API.
 */
extern const unsigned dvbt_modulation[];

/**
 * @brief converts from the descriptor's hierarchy into enum fe_hierarchy,
 *	  as defined by DVBv5 API.
 */
extern const unsigned dvbt_hierarchy[];

/**
 * @brief converts from the descriptor's FEC into enum fe_code_rate,
 *	  as defined by DVBv5 API.
 */
extern const unsigned dvbt_code_rate[];

/**
 * @brief converts from internal representation into enum fe_guard_interval,
 * as defined at DVBv5 API.
 */
extern const uint32_t dvbt_interval[];

/**
 * @brief converts from the descriptor's transmission mode into
 *	  enum fe_transmit_mode, as defined by DVBv5 API.
 */
<<<<<<< HEAD
=======
int dvb_desc_terrestrial_delivery_init (struct dvb_v5_fe_parms *parms, const uint8_t *buf, struct dvb_desc *desc);
void dvb_desc_terrestrial_delivery_print(struct dvb_v5_fe_parms *parms, const struct dvb_desc *desc);
extern const unsigned dvbt_bw[];
extern const unsigned dvbt_modulation[];
extern const unsigned dvbt_hierarchy[];
extern const unsigned dvbt_code_rate[];
extern const uint32_t dvbt_interval[];
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
extern const unsigned dvbt_transmission_mode[];

#ifdef __cplusplus
}
#endif

#endif
