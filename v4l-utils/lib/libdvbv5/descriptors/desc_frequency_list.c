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

#include <libdvbv5/desc_frequency_list.h>
#include <libdvbv5/dvb-fe.h>

int dvb_desc_frequency_list_init(struct dvb_v5_fe_parms *parms, const uint8_t *buf, struct dvb_desc *desc)
{
	struct dvb_desc_frequency_list *d = (struct dvb_desc_frequency_list *) desc;
	size_t len;
	int i;
	const uint8_t *p = buf;

	len = sizeof(*d) - offsetof(struct dvb_desc_frequency_list, bitfield);
	memcpy(&d->bitfield, p, len);
	p += len;

	d->frequencies = (d->length - len) / sizeof(d->frequency[0]);

<<<<<<< HEAD
<<<<<<< HEAD
	d->frequency = calloc(d->frequencies, sizeof(*d->frequency));
=======
	d->frequency = calloc(d->frequencies, sizeof(d->frequency));
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	d->frequency = calloc(d->frequencies, sizeof(d->frequency));
=======
	d->frequency = calloc(d->frequencies, sizeof(*d->frequency));
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

	for (i = 0; i < d->frequencies; i++) {
		d->frequency[i] = ((uint32_t *) p)[i];
		bswap32(d->frequency[i]);
		switch (d->freq_type) {
			case 1: /* satellite - to get kHz */
			case 3: /* terrestrial - to get Hz */
				d->frequency[i] *= 10;
				break;
			case 2: /* cable - to get Hz */
				d->frequency[i] *= 100;
				break;
			case 0: /* not defined */
			default:
				break;
		}
	}
	return 0;
}

void dvb_desc_frequency_list_print(struct dvb_v5_fe_parms *parms, const struct dvb_desc *desc)
{
	const struct dvb_desc_frequency_list *d = (const struct dvb_desc_frequency_list *) desc;
	dvb_loginfo("|           type: %d", d->freq_type);
	int i = 0;

	for (i = 0; i < d->frequencies; i++) {
		dvb_loginfo("|           frequency : %u", d->frequency[i]);
	}
}

