/*
 * Copyright (c) 2011-2012 - Mauro Carvalho Chehab
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdvbv5/dvb-file.h>
#include <libdvbv5/dvb-v5-std.h>

<<<<<<< HEAD
<<<<<<< HEAD
=======
/*
 * Standard channel.conf format for DVB-T, DVB-C, DVB-S and ATSC
 */
static const char *channel_parse_modulation[] = {
	[APSK_16] =  "APSK16",
	[APSK_32] =  "APSK32",
	[DQPSK] =    "DQPSK",
	[PSK_8] =    "PSK8",
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
#define PTABLE(a) .table = a, .size=ARRAY_SIZE(a)

/*
 * Standard channel.conf format for DVB-T, DVB-C, DVB-S, DVB-S2 and ATSC
 */
static const char *channel_parse_modulation[] = {
	[APSK_16] =  "16APSK",
	[APSK_32] =  "32APSK",
	[DQPSK] =    "DQPSK",
	[PSK_8] =    "8PSK",
<<<<<<< HEAD
=======
/*
 * Standard channel.conf format for DVB-T, DVB-C, DVB-S and ATSC
 */
static const char *channel_parse_modulation[] = {
	[APSK_16] =  "APSK16",
	[APSK_32] =  "APSK32",
	[DQPSK] =    "DQPSK",
	[PSK_8] =    "PSK8",
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	[QAM_16] =   "QAM16",
	[QAM_32] =   "QAM32",
	[QAM_64] =   "QAM64",
	[QAM_128] =  "QAM128",
	[QAM_256] =  "QAM256",
	[QAM_AUTO] = "AUTO",
	[QPSK] =     "QPSK",
	[VSB_8] =    "8VSB",
	[VSB_16] =   "16VSB",
};

static const char *channel_parse_bandwidth[] = {
	[BANDWIDTH_1_712_MHZ] = "1.712MHz",
	[BANDWIDTH_5_MHZ] =     "5MHz",
	[BANDWIDTH_6_MHZ] =     "6MHz",
	[BANDWIDTH_7_MHZ] =     "7MHz",
	[BANDWIDTH_8_MHZ] =     "8MHz",
	[BANDWIDTH_10_MHZ] =    "10MHz",
	[BANDWIDTH_AUTO] =      "AUTO",
};

static const char *channel_parse_trans_mode[] = {
	[TRANSMISSION_MODE_1K] =   "1k",
	[TRANSMISSION_MODE_2K] =   "2k",
	[TRANSMISSION_MODE_4K] =   "4k",
	[TRANSMISSION_MODE_8K] =   "8k",
	[TRANSMISSION_MODE_16K] =  "16k",
	[TRANSMISSION_MODE_32K] =  "32k",
	[TRANSMISSION_MODE_AUTO] = "AUTO",
};

static const char *channel_parse_code_rate[12] = {
	[FEC_1_2] =  "1/2",
	[FEC_2_3] =  "2/3",
	[FEC_3_4] =  "3/4",
	[FEC_3_5] =  "3/5",
	[FEC_4_5] =  "4/5",
	[FEC_5_6] =  "5/6",
	[FEC_6_7] =  "6/7",
	[FEC_7_8] =  "7/8",
	[FEC_8_9] =  "8/9",
	[FEC_9_10] = "9/10",
	[FEC_AUTO] = "AUTO",
	[FEC_NONE] = "NONE",
};

static const char *channel_parse_guard_interval[] = {
	[GUARD_INTERVAL_1_4] =    "1/4",
	[GUARD_INTERVAL_1_8] =    "1/8",
	[GUARD_INTERVAL_1_16] =   "1/16",
	[GUARD_INTERVAL_1_32] =   "1/32",
	[GUARD_INTERVAL_1_128] =  "1/128",
	[GUARD_INTERVAL_19_128] = "19/128",
	[GUARD_INTERVAL_19_256] = "19/256",
	[GUARD_INTERVAL_AUTO] =   "AUTO",
};

static const char *channel_parse_hierarchy[] = {
	[HIERARCHY_1] =    "1",
	[HIERARCHY_2] =    "2",
	[HIERARCHY_4] =    "4",
	[HIERARCHY_AUTO] = "AUTO",
	[HIERARCHY_NONE] = "NONE",
};

static const char *channel_parse_polarization[] = {
	[POLARIZATION_OFF] = "-",
	[POLARIZATION_H] = "H",
	[POLARIZATION_V] = "V",
	[POLARIZATION_L] = "L",
	[POLARIZATION_R] = "R",
};

<<<<<<< HEAD
<<<<<<< HEAD
=======
static const struct parse_table sys_atsc_table[] = {
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
static const char *channel_parse_rolloff[] = {
	[ROLLOFF_20] = "20",
	[ROLLOFF_25] = "25",
	[ROLLOFF_35] = "35",
	[ROLLOFF_AUTO] = "AUTO",
};

static const struct dvb_parse_table sys_atsc_table[] = {
<<<<<<< HEAD
=======
static const struct parse_table sys_atsc_table[] = {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	{ DTV_FREQUENCY, NULL, 0 },
	{ DTV_MODULATION, PTABLE(channel_parse_modulation) },
};

<<<<<<< HEAD
<<<<<<< HEAD
static const struct dvb_parse_table sys_dvbc_table[] = {
=======
static const struct parse_table sys_dvbc_table[] = {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
static const struct parse_table sys_dvbc_table[] = {
=======
static const struct dvb_parse_table sys_dvbc_table[] = {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	{ DTV_FREQUENCY, NULL, 0 },
	{ DTV_SYMBOL_RATE, NULL, 0 },
	{ DTV_INNER_FEC, PTABLE(channel_parse_code_rate) },
	{ DTV_MODULATION, PTABLE(channel_parse_modulation) },
};

/* Note: On DVB-S, frequency is divided by 1000 */
<<<<<<< HEAD
<<<<<<< HEAD
static const struct dvb_parse_table sys_dvbs_table[] = {
=======
static const struct parse_table sys_dvbs_table[] = {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
static const struct parse_table sys_dvbs_table[] = {
=======
static const struct dvb_parse_table sys_dvbs_table[] = {
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	{ DTV_FREQUENCY, NULL, 0 },
	{ DTV_POLARIZATION, PTABLE(channel_parse_polarization) },
	{ DTV_SYMBOL_RATE, NULL, 0 },
	{ DTV_INNER_FEC, PTABLE(channel_parse_code_rate) },
};

<<<<<<< HEAD
<<<<<<< HEAD
=======
static const struct parse_table sys_dvbt_table[] = {
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
static const struct dvb_parse_table sys_dvbs2_table[] = {
	{ DTV_FREQUENCY, NULL, 0 },
	{ DTV_POLARIZATION, PTABLE(channel_parse_polarization) },
	{ DTV_SYMBOL_RATE, NULL, 0 },
	{ DTV_INNER_FEC, PTABLE(channel_parse_code_rate) },
	{ DTV_ROLLOFF, PTABLE(channel_parse_rolloff) },
	{ DTV_MODULATION, PTABLE(channel_parse_modulation) },
	{ DTV_STREAM_ID, NULL, 0, 0, 1, 0 },
	{ DTV_PLS_CODE, NULL, 0, 0, 1, -1 },
	{ DTV_PLS_MODE, NULL, 0, 0, 1, -1 },
};

static const struct dvb_parse_table sys_dvbt_table[] = {
	{ DTV_FREQUENCY, NULL, 0 },
	{ DTV_BANDWIDTH_HZ, PTABLE(channel_parse_bandwidth) },
	{ DTV_CODE_RATE_HP, PTABLE(channel_parse_code_rate) },
	{ DTV_CODE_RATE_LP, PTABLE(channel_parse_code_rate) },
	{ DTV_MODULATION, PTABLE(channel_parse_modulation) },
	{ DTV_TRANSMISSION_MODE, PTABLE(channel_parse_trans_mode) },
	{ DTV_GUARD_INTERVAL, PTABLE(channel_parse_guard_interval) },
	{ DTV_HIERARCHY, PTABLE(channel_parse_hierarchy) },
};

static const struct dvb_parse_table sys_dvbt2_table[] = {
<<<<<<< HEAD
=======
static const struct parse_table sys_dvbt_table[] = {
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	{ DTV_FREQUENCY, NULL, 0 },
	{ DTV_BANDWIDTH_HZ, PTABLE(channel_parse_bandwidth) },
	{ DTV_CODE_RATE_HP, PTABLE(channel_parse_code_rate) },
	{ DTV_CODE_RATE_LP, PTABLE(channel_parse_code_rate) },
	{ DTV_MODULATION, PTABLE(channel_parse_modulation) },
	{ DTV_TRANSMISSION_MODE, PTABLE(channel_parse_trans_mode) },
	{ DTV_GUARD_INTERVAL, PTABLE(channel_parse_guard_interval) },
	{ DTV_HIERARCHY, PTABLE(channel_parse_hierarchy) },
<<<<<<< HEAD
<<<<<<< HEAD
	{ DTV_STREAM_ID, NULL, 0, 0, 1, -1 },
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
};

const struct parse_file channel_file_format = {
	.has_delsys_id = 1,
	.delimiter = " \n",
=======
	{ DTV_STREAM_ID, NULL, 0, 0, 1, -1 },
};

const struct dvb_parse_file channel_file_format = {
	.has_delsys_id = 1,
<<<<<<< HEAD
	.delimiter = " \n",
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	.delimiter = " \n\t",
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	.formats = {
		{
			.id		= "A",
			.delsys		= SYS_ATSC,
			PTABLE(sys_atsc_table),
		}, {
			.id		= "C",
			.delsys		= SYS_DVBC_ANNEX_A,
			PTABLE(sys_dvbc_table),
		}, {
			.id		= "S",
			.delsys		= SYS_DVBS,
			PTABLE(sys_dvbs_table),
		}, {
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
			.id		= "S2",
			.delsys		= SYS_DVBS2,
			PTABLE(sys_dvbs2_table),
		}, {
<<<<<<< HEAD
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
			.id		= "T",
			.delsys		= SYS_DVBT,
			PTABLE(sys_dvbt_table),
		}, {
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
			.id		= "T2",
			.delsys		= SYS_DVBT2,
			PTABLE(sys_dvbt2_table),
		}, {
<<<<<<< HEAD
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
			NULL, 0, NULL, 0,
		}
	}
};
