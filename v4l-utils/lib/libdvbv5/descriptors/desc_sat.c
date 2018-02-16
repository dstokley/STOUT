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

#include <libdvbv5/desc_sat.h>
#include <libdvbv5/dvb-fe.h>

int dvb_desc_sat_init(struct dvb_v5_fe_parms *parms, const uint8_t *buf, struct dvb_desc *desc)
{
	struct dvb_desc_sat *sat = (struct dvb_desc_sat *) desc;
<<<<<<< HEAD
<<<<<<< HEAD
=======
	/* copy from .length */
	memcpy(((uint8_t *) sat ) + sizeof(sat->type) + sizeof(sat->next) + sizeof(sat->length),
		buf,
		sat->length);
	bswap16(sat->orbit);
	bswap32(sat->bitfield);
	bswap32(sat->frequency);
	sat->orbit = bcd(sat->orbit);
	sat->frequency   = bcd(sat->frequency) * 10;
	sat->symbol_rate = bcd(sat->symbol_rate) * 100;
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	ssize_t size = sizeof(struct dvb_desc_sat) - sizeof(struct dvb_desc);

	if (size > desc->length) {
		dvb_logerr("dvb_desc_sat_init short read %d/%zd bytes", desc->length, size);
		return -1;
	}

	memcpy(desc->data, buf, size);
	bswap16(sat->orbit);
	bswap32(sat->bitfield);
	bswap32(sat->frequency);
	sat->orbit = dvb_bcd(sat->orbit);
	sat->frequency   = dvb_bcd(sat->frequency) * 10;
	sat->symbol_rate = dvb_bcd(sat->symbol_rate) * 100;
<<<<<<< HEAD
=======
	/* copy from .length */
	memcpy(((uint8_t *) sat ) + sizeof(sat->type) + sizeof(sat->next) + sizeof(sat->length),
		buf,
		sat->length);
	bswap16(sat->orbit);
	bswap32(sat->bitfield);
	bswap32(sat->frequency);
	sat->orbit = bcd(sat->orbit);
	sat->frequency   = bcd(sat->frequency) * 10;
	sat->symbol_rate = bcd(sat->symbol_rate) * 100;
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0

	return 0;
}

void dvb_desc_sat_print(struct dvb_v5_fe_parms *parms, const struct dvb_desc *desc)
{
	const struct dvb_desc_sat *sat = (const struct dvb_desc_sat *) desc;
	char pol;
	switch(sat->polarization) {
		case 0:
			pol = 'H';
			break;
		case 1:
			pol = 'V';
			break;
		case 2:
			pol = 'L';
			break;
		case 3:
			pol = 'R';
			break;
	}
	dvb_loginfo("|           modulation_system %s", sat->modulation_system ? "DVB-S2" : "DVB-S");
	dvb_loginfo("|           frequency         %d %c", sat->frequency, pol);
	dvb_loginfo("|           symbol_rate       %d", sat->symbol_rate);
	dvb_loginfo("|           fec               %d", sat->fec);
	dvb_loginfo("|           modulation_type   %d", sat->modulation_type);
	dvb_loginfo("|           roll_off          %d", sat->roll_off);
	dvb_loginfo("|           orbit             %.1f %c", (float) sat->orbit / 10.0, sat->west_east ? 'E' : 'W');
}

const unsigned dvbs_dvbc_dvbs_freq_inner[] = {
	[0]  = FEC_AUTO,
	[1]  = FEC_1_2,
	[2]  = FEC_2_3,
	[3]  = FEC_3_4,
	[4]  = FEC_5_6,
	[5]  = FEC_7_8,
	[6]  = FEC_8_9,
	[7]  = FEC_3_5,
	[8]  = FEC_4_5,
	[9]  = FEC_9_10,
	[10 ...14] = FEC_AUTO,	/* Currently, undefined */
	[15] = FEC_NONE,
};

const unsigned dvbs_polarization[] = {
	[0] = POLARIZATION_H,
	[1] = POLARIZATION_V,
	[2] = POLARIZATION_L,
	[3] = POLARIZATION_R
};

const unsigned dvbs_rolloff[] = {
	[0] = ROLLOFF_35,
	[1] = ROLLOFF_25,
	[2] = ROLLOFF_20,
	[3] = ROLLOFF_AUTO,	/* Reserved */
};

const unsigned dvbs_modulation[] = {
	[0] = QAM_AUTO,
	[1] = QPSK,
	[2] = PSK_8,
	[3] = QAM_16
};

