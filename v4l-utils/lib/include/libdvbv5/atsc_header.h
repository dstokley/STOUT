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

#ifndef _ATSC_HEADER_H
#define _ATSC_HEADER_H

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @file atsc_header.h
 * @ingroup dvb_table
 * @brief Provides some common ATSC stuff
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
#include <stdint.h>
#include <unistd.h> /* ssize_t */

#include <libdvbv5/header.h>

<<<<<<< HEAD
<<<<<<< HEAD
=======
#define ATSC_BASE_PID  0x1FFB

=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
/**
 * @def ATSC_BASE_PID
 *	@brief ATSC PID for the Program and System Information Protocol
 * @ingroup dvb_table
 */
#define ATSC_BASE_PID  0x1FFB

#ifndef _DOXYGEN

/* Deprecated, as it causes troubles with doxygen */
<<<<<<< HEAD
=======
#define ATSC_BASE_PID  0x1FFB

>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
#define ATSC_HEADER() \
	struct dvb_table_header header; \
	uint8_t  protocol_version; \

#define ATSC_TABLE_HEADER_PRINT(_parms, _table) \
	dvb_table_header_print(_parms, &_table->header); \
	dvb_loginfo("| protocol_version %d", _table->protocol_version); \

<<<<<<< HEAD
<<<<<<< HEAD
#endif /* _DOXYGEN */
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

#endif
=======
#endif /* _DOXYGEN */

<<<<<<< HEAD
#endif
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
#endif /* _ATSC_HEADER_H */
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
