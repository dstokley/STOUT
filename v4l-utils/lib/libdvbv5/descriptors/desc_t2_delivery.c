/*
 * Copyright (c) 2013 - Mauro Carvalho Chehab <m.chehab@samsung.com>
 *
<<<<<<< HEAD
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
=======
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation version 2.1 of the License.
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
<<<<<<< HEAD
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
=======
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * Or, point your browser to http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 *
 * Based on ETSI EN 300 468 V1.11.1 (2010-04)
 */

#include <libdvbv5/desc_extension.h>
#include <libdvbv5/desc_t2_delivery.h>
#include <libdvbv5/dvb-fe.h>

int dvb_desc_t2_delivery_init(struct dvb_v5_fe_parms *parms,
			       const uint8_t *buf,
			       struct dvb_extension_descriptor *ext,
			       void *desc)
{
	struct dvb_desc_t2_delivery *d = desc;
	unsigned char *p = (unsigned char *) buf;
	size_t desc_len = ext->length - 1, len, len2;
<<<<<<< HEAD
	int i;
=======
	int i, pos = 0;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d

	len = offsetof(struct dvb_desc_t2_delivery, bitfield);
	len2 = offsetof(struct dvb_desc_t2_delivery, centre_frequency);

	if (desc_len < len) {
		dvb_logwarn("T2 delivery descriptor is too small");
		return -1;
	}
	if (desc_len < len2) {
<<<<<<< HEAD
		memcpy(p, buf, len);
		bswap16(d->system_id);

		if (desc_len != len)
			dvb_logwarn("T2 delivery descriptor is truncated");

		return -2;
	}
	memcpy(p, buf, len2);
	p += len2;

	len = desc_len - (p - buf);
	memcpy(&d->centre_frequency, p, len);
	p += len;

	if (d->tfs_flag)
		d->frequency_loop_length = 1;
	else {
		d->frequency_loop_length = *p;
		p++;
	}

	d->centre_frequency = calloc(d->frequency_loop_length,
				     sizeof(*d->centre_frequency));
	if (!d->centre_frequency) {
		dvb_logerr("%s: out of memory", __func__);
		return -3;
	}

	memcpy(d->centre_frequency, p, sizeof(*d->centre_frequency) * d->frequency_loop_length);
	p += sizeof(*d->centre_frequency) * d->frequency_loop_length;

	for (i = 0; i < d->frequency_loop_length; i++)
		bswap32(d->centre_frequency[i]);

	d->subcel_info_loop_length = *p;
	p++;

	d->subcell = calloc(d->subcel_info_loop_length, sizeof(*d->subcell));
	if (!d->subcell) {
		dvb_logerr("%s: out of memory", __func__);
		return -4;
	}
	memcpy(d->subcell, p, sizeof(*d->subcell) * d->subcel_info_loop_length);

	for (i = 0; i < d->subcel_info_loop_length; i++)
		bswap16(d->subcell[i].transposer_frequency);
=======
		memcpy(d, buf, len);
		bswap16(d->system_id);

		/* It is valid to have length == 4 */
		if (desc_len == len)
			return 0;

		dvb_logwarn("T2 delivery descriptor is truncated");
		return -2;
	}
	memcpy(d, buf, len2);
	bswap16(d->system_id);
	bswap16(d->bitfield);
	p += len2;

	while (desc_len - (p - buf)) {
		if (desc_len - (p - buf) < sizeof(uint16_t)) {
			dvb_logwarn("T2 delivery descriptor is truncated");
			return -2;
		}

		d->cell = realloc(d->cell, (d->num_cell + 1) * sizeof(*d->cell));
		if (!d->cell) {
			dvb_logerr("%s: out of memory", __func__);
			return -3;
		}

		d->cell[d->num_cell].cell_id = *(uint16_t *)p;
		bswap16(d->cell[d->num_cell].cell_id);
		p += sizeof(uint16_t);

		if (d->tfs_flag) {
			d->cell[d->num_cell].num_freqs = *p;
			p++;
		}
		else
			d->cell[d->num_cell].num_freqs = 1;

		d->frequency_loop_length += d->cell[d->num_cell].num_freqs;
		d->centre_frequency = realloc(d->centre_frequency,
					      d->frequency_loop_length * sizeof(*d->centre_frequency));
		if (!d->centre_frequency) {
			dvb_logerr("%s: out of memory", __func__);
			return -3;
		}

		d->cell[d->num_cell].centre_frequency = &d->centre_frequency[pos];

		memcpy(&d->centre_frequency[pos], p, sizeof(*d->centre_frequency) * d->cell[d->num_cell].num_freqs);
		p += sizeof(*d->centre_frequency) * d->cell[d->num_cell].num_freqs;

		for (i = 0; i < d->cell[d->num_cell].num_freqs; i++) {
			bswap32(d->centre_frequency[pos]);
			pos++;
		}

		/* Handle subcel frequency table */
		d->cell[d->num_cell].subcel_length = *p;
		d->cell[d->num_cell].subcel = NULL;

		p++;

		if (d->cell[d->num_cell].subcel_length) {
			d->cell[d->num_cell].subcel = calloc(d->cell[d->num_cell].subcel_length,
							     sizeof (*d->cell[d->num_cell].subcel));

			if (!d->cell[d->num_cell].subcel) {
				dvb_logerr("%s: out of memory", __func__);
				return -3;
			}
		}

		for (i = 0; i < d->cell[d->num_cell].subcel_length; i++) {
			if (desc_len - (p - buf) < sizeof(uint8_t) + sizeof(uint32_t)) {
				dvb_logwarn("T2 delivery descriptor is truncated");
				return -2;
			}
			d->cell[d->num_cell].subcel[i].cell_id_extension = *p;
			p++;

			// Add transposer_frequency at centre_frequency table
			d->frequency_loop_length++;
			d->centre_frequency = realloc(d->centre_frequency,
						      d->frequency_loop_length * sizeof(*d->centre_frequency));
			memcpy(&d->centre_frequency[pos], p, sizeof(*d->centre_frequency));
			bswap32(d->centre_frequency[pos]);
			d->cell[d->num_cell].subcel[i].transposer_frequency = d->centre_frequency[pos];
			pos++;

			p += sizeof(*d->centre_frequency);
		}
		d->num_cell++;
	}

>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
	return 0;
}

void dvb_desc_t2_delivery_print(struct dvb_v5_fe_parms *parms,
				const struct dvb_extension_descriptor *ext,
				const void *desc)
{
	const struct dvb_desc_t2_delivery *d = desc;
<<<<<<< HEAD
	int i;

	dvb_loginfo("|           plp_id                    %d", d->plp_id);
	dvb_loginfo("|           system_id                 %d", d->system_id);
=======
	int i, j, k;

	dvb_loginfo("|           plp_id                    0x%04x", d->plp_id);
	dvb_loginfo("|           system_id                 0x%04x", d->system_id);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d

	if (ext->length - 1 <= 4)
		return;

	dvb_loginfo("|           tfs_flag                  %d", d->tfs_flag);
	dvb_loginfo("|           other_frequency_flag      %d", d->other_frequency_flag);
<<<<<<< HEAD
	dvb_loginfo("|           transmission_mode         %d", d->transmission_mode);
	dvb_loginfo("|           guard_interval            %d", d->guard_interval);
	dvb_loginfo("|           reserved                  %d", d->reserved);
	dvb_loginfo("|           bandwidth                 %d", d->bandwidth);
	dvb_loginfo("|           SISO MISO                 %d", d->SISO_MISO);

	for (i = 0; i < d->frequency_loop_length; i++)
		dvb_loginfo("|           centre frequency[%d]   %d", i, d->centre_frequency[i]);

	for (i = 0; i < d->subcel_info_loop_length; i++) {
		dvb_loginfo("|           cell_id_extension[%d]  %d", i, d->subcell[i].cell_id_extension);
		dvb_loginfo("|           transposer frequency   %d", d->subcell[i].transposer_frequency);
=======
	dvb_loginfo("|           transmission_mode         %s (%d)",
		    fe_transmission_mode_name[dvbt2_transmission_mode[d->transmission_mode]], d->transmission_mode);
	dvb_loginfo("|           guard_interval            %s (%d)",
		    fe_guard_interval_name[dvbt2_interval[d->guard_interval]], d->guard_interval );
	dvb_loginfo("|           reserved                  %d", d->reserved);
	dvb_loginfo("|           bandwidth                 %.2f MHz (%d)",
		    dvbt2_bw[d->bandwidth]/ 1000000., d->bandwidth);
	dvb_loginfo("|           SISO/MISO mode            %s", siso_miso[d->SISO_MISO]);

	/*
	 * All frequencies are also at the per-cell data. Yet, as the flat
	 * frequency table is what's used to add new transponders for DVB-T2
	 * scan, let's display the flat table too
	 */
	for (i = 0; i < d->frequency_loop_length; i++)
		dvb_loginfo("|           frequency[%d]              %.5f MHz", i, d->centre_frequency[i] / 100000.);


	for (i = 0; i < d->num_cell; i++) {
		struct dvb_desc_t2_delivery_cell *cell = &d->cell[i];
		dvb_loginfo("|           Cell ID                   0x%04x", cell->cell_id);
		for (j = 0; j < cell->num_freqs; j++) {
			dvb_loginfo("|              centre frequency[%d]    %.5f MHz", j, cell->centre_frequency[j] / 100000.);

			for (k = 0; k < cell->subcel_length; k++) {
				struct dvb_desc_t2_delivery_subcell *subcel = &cell->subcel[k];
				dvb_loginfo("|           |- subcell        %d", subcel->cell_id_extension);
				dvb_loginfo("|              |- transposer  %.5f MHz", subcel->transposer_frequency / 100000.);
			}
		}
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
	}
}

void dvb_desc_t2_delivery_free(const void *desc)
{
	const struct dvb_desc_t2_delivery *d = desc;
<<<<<<< HEAD
=======
	int i;
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d

	if (d->centre_frequency)
		free(d->centre_frequency);

<<<<<<< HEAD
	if (d->subcell)
		free(d->subcell);
=======
	if (d->cell) {
		for (i = 0; i < d->num_cell; i++)
			if (d->cell[i].subcel)
				free(d->cell[i].subcel);
		free (d->cell);
	}

	// No need to free d->subcell, as it is always NULL
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
}

const unsigned dvbt2_bw[] = {
	[0] =  8000000,
	[1] =  7000000,
	[2] =  6000000,
	[3] =  5000000,
	[4] = 10000000,
	[5] =  1712000,
	[6 ...15] = 0,		/* Reserved */
};
const uint32_t dvbt2_interval[] = {
	[0] = GUARD_INTERVAL_1_32,
	[1] = GUARD_INTERVAL_1_16,
	[2] = GUARD_INTERVAL_1_8,
	[3] = GUARD_INTERVAL_1_4,
	[4] = GUARD_INTERVAL_1_128,
	[5] = GUARD_INTERVAL_19_128,
	[6] = GUARD_INTERVAL_19_256,
	[7 ...15] = GUARD_INTERVAL_AUTO /* Reserved */
};
const unsigned dvbt2_transmission_mode[] = {
	[0] = TRANSMISSION_MODE_2K,
	[1] = TRANSMISSION_MODE_8K,
	[2] = TRANSMISSION_MODE_4K,
	[3] = TRANSMISSION_MODE_1K,
	[4] = TRANSMISSION_MODE_16K,
	[5] = TRANSMISSION_MODE_32K,
	[6 ...7] = TRANSMISSION_MODE_AUTO,	/* Reserved */
};
<<<<<<< HEAD
=======
const char *siso_miso[4] = {
	[0] = "Single Input, Single Output (SISO)",
	[1] = "Multiple Input, Single Output (MISO)",
	[2 ...3] = "reserved",
};
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
