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
 */

#include <libdvbv5/header.h>
#include <libdvbv5/descriptors.h>
#include <libdvbv5/dvb-fe.h>

void dvb_table_header_init(struct dvb_table_header *t)
{
	bswap16(t->bitfield);
	bswap16(t->id);
}

void dvb_table_header_print(struct dvb_v5_fe_parms *parms, const struct dvb_table_header *t)
{
	dvb_loginfo("| table_id         0x%02x", t->table_id);
	dvb_loginfo("| section_length      %d", t->section_length);
	dvb_loginfo("| one                 %d", t->one);
	dvb_loginfo("| zero                %d", t->zero);
	dvb_loginfo("| syntax              %d", t->syntax);
	dvb_loginfo("| transport_stream_id %d", t->id);
	dvb_loginfo("| current_next        %d", t->current_next);
	dvb_loginfo("| version             %d", t->version);
	dvb_loginfo("| one2                %d", t->one2);
	dvb_loginfo("| section_number      %d", t->section_id);
	dvb_loginfo("| last_section_number %d", t->last_section);
}

