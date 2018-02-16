/*
 * Copyright (c) 2013 - Mauro Carvalho Chehab <m.chehab@samsung.com>
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
 * Described on ARIB STD-B10 as Partial reception descriptor
 */

#include <libdvbv5/desc_partial_reception.h>
#include <libdvbv5/dvb-fe.h>
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include <parse_string.h>
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
#include <parse_string.h>
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

int isdb_desc_partial_reception_init(struct dvb_v5_fe_parms *parms,
			      const uint8_t *buf, struct dvb_desc *desc)
{
	struct isdb_desc_partial_reception *d = (void *)desc;
	unsigned char *p = (unsigned char *)buf;
	size_t len;
	int i;

	d->partial_reception = malloc(d->length);
	if (!d->partial_reception) {
		dvb_logerr("%s: out of memory", __func__);
		return -1;
	}

	memcpy(d->partial_reception, p, d->length);

<<<<<<< HEAD
<<<<<<< HEAD
       len = d->length / sizeof(*d->partial_reception);
=======
	len = d->length / sizeof(d->partial_reception);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	len = d->length / sizeof(d->partial_reception);
=======
       len = d->length / sizeof(*d->partial_reception);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

	for (i = 0; i < len; i++)
		bswap16(d->partial_reception[i].service_id);
	return 0;
}

void isdb_desc_partial_reception_free(struct dvb_desc *desc)
{
	struct isdb_desc_partial_reception *d = (void *)desc;
	if (d->partial_reception)
		free(d->partial_reception);
}

void isdb_desc_partial_reception_print(struct dvb_v5_fe_parms *parms, const struct dvb_desc *desc)
{
	struct isdb_desc_partial_reception *d = (void *)desc;
	int i;
	size_t len;

<<<<<<< HEAD
<<<<<<< HEAD
       len = d->length / sizeof(*d->partial_reception);
=======
	len = d->length / sizeof(d->partial_reception);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	len = d->length / sizeof(d->partial_reception);
=======
       len = d->length / sizeof(*d->partial_reception);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

	for (i = 0; i < len; i++) {
		dvb_loginfo("|           service ID[%d]     %d", i, d->partial_reception[i].service_id);
	}
}
