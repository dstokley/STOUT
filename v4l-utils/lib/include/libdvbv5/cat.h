/*
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
 * @file cat.h
 * @ingroup dvb_table
 * @brief Provides the table parser for the CAT (Conditional Access Table)
 * @copyright GNU Lesser General Public License version 2.1 (LGPLv2.1)
 * @author Andre Roth
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
#ifndef _CAT_H
#define _CAT_H

#include <stdint.h>
#include <unistd.h> /* ssize_t */

#include <libdvbv5/header.h>

<<<<<<< HEAD
<<<<<<< HEAD
=======
#define DVB_TABLE_CAT      0x01
#define DVB_TABLE_CAT_PID  0x0001

=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @def DVB_TABLE_CAT
 *	@brief ATSC CAT table ID
 * 	@ingroup dvb_table
 * @def DVB_TABLE_CAT_PID
 *	@brief ATSC PID table ID
 * 	@ingroup dvb_table
 */
#define DVB_TABLE_CAT      0x01
#define DVB_TABLE_CAT_PID  0x0001

/**
 * @struct dvb_table_cat
 * @brief ATSC CAT table
 *
 * @param header	struct dvb_table_header content
 * @param descriptor	pointer to struct dvb_desc
 */
<<<<<<< HEAD
=======
#define DVB_TABLE_CAT      0x01
#define DVB_TABLE_CAT_PID  0x0001

>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
struct dvb_table_cat {
	struct dvb_table_header header;
	struct dvb_desc *descriptor;
} __attribute__((packed));

struct dvb_v5_fe_parms;

#ifdef __cplusplus
extern "C" {
#endif

<<<<<<< HEAD
<<<<<<< HEAD
=======
ssize_t dvb_table_cat_init (struct dvb_v5_fe_parms *parms, const uint8_t *buf, ssize_t buflen, struct dvb_table_cat **table);
void dvb_table_cat_free(struct dvb_table_cat *cat);
void dvb_table_cat_print(struct dvb_v5_fe_parms *parms, struct dvb_table_cat *t);
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @brief Initializes and parses CAT table
 *
 * @param parms	struct dvb_v5_fe_parms pointer to the opened device
 * @param buf buffer containing the CAT raw data
 * @param buflen length of the buffer
 * @param table pointer to struct dvb_table_cat to be allocated and filled
 *
 * This function allocates an CAT table and fills the fields inside
 * the struct. It also makes sure that all fields will follow the CPU
 * endianness. Due to that, the content of the buffer may change.
 *
 * @return On success, it returns the size of the allocated struct.
 *	   A negative value indicates an error.
 */
ssize_t dvb_table_cat_init(struct dvb_v5_fe_parms *parms, const uint8_t *buf,
			   ssize_t buflen, struct dvb_table_cat **table);

/**
 * @brief Frees all data allocated by the CAT table parser
 *
 * @param table pointer to struct dvb_table_cat to be freed
 */
void dvb_table_cat_free(struct dvb_table_cat *table);

/**
 * @brief Prints the content of the CAT table
 *
 * @param parms	struct dvb_v5_fe_parms pointer to the opened device
 * @param table pointer to struct dvb_table_cat
 */
void dvb_table_cat_print(struct dvb_v5_fe_parms *parms,
			 struct dvb_table_cat *table);
<<<<<<< HEAD
=======
ssize_t dvb_table_cat_init (struct dvb_v5_fe_parms *parms, const uint8_t *buf, ssize_t buflen, struct dvb_table_cat **table);
void dvb_table_cat_free(struct dvb_table_cat *cat);
void dvb_table_cat_print(struct dvb_v5_fe_parms *parms, struct dvb_table_cat *t);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

#ifdef __cplusplus
}
#endif

#endif
