/*
 * Copyright (c) 2011-2012 - Mauro Carvalho Chehab
 * Copyright (c) 2012 - Andre Roth <neolynx@gmail.com>
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
 */

#include <libdvbv5/desc_network_name.h>
#include <libdvbv5/dvb-fe.h>
<<<<<<< HEAD
#include "parse_string.h"
=======
#include <parse_string.h>
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d

int dvb_desc_network_name_init(struct dvb_v5_fe_parms *parms, const uint8_t *buf, struct dvb_desc *desc)
{
	struct dvb_desc_network_name *net = (struct dvb_desc_network_name *) desc;
	uint8_t len;  /* the length of the string in the input data */
	uint8_t len1; /* the lenght of the output strings */

	len = desc->length;
	len1 = len;
	net->network_name = NULL;
	net->network_name_emph = NULL;
<<<<<<< HEAD
	parse_string(parms, &net->network_name, &net->network_name_emph, buf, len1, default_charset, output_charset);
=======
	dvb_parse_string(parms, &net->network_name, &net->network_name_emph, buf, len1);
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
	buf += len;
	return 0;
}

void dvb_desc_network_name_print(struct dvb_v5_fe_parms *parms, const struct dvb_desc *desc)
{
	const struct dvb_desc_network_name *net = (const struct dvb_desc_network_name *) desc;

	dvb_loginfo("|           network name: '%s'", net->network_name);
}

void dvb_desc_network_name_free(struct dvb_desc *desc)
{
	const struct dvb_desc_network_name *net = (const struct dvb_desc_network_name *) desc;

	free(net->network_name);
	free(net->network_name_emph);
}
