/*
 * Copyright (c) 2011-2012 - Mauro Carvalho Chehab
 *
<<<<<<< HEAD
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation version 2.1 of the License.
=======
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
<<<<<<< HEAD
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
=======
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * Or, point your browser to http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 */

<<<<<<< HEAD
#if HAVE_VISIBILITY
#pragma GCC visibility push(hidden)
#endif

struct dvb_v5_fe_parms;

void dvb_iconv_to_charset(struct dvb_v5_fe_parms *parms,
			  char *dest,
			  size_t destlen,
			  const unsigned char *src,
			  size_t len,
			  char *type, char *output_charset);

void dvb_parse_string(struct dvb_v5_fe_parms *parms, char **dest, char **emph,
		      const unsigned char *src, size_t len);

#if HAVE_VISIBILITY
#pragma GCC visibility pop
#endif
=======
struct dvb_v5_fe_parms;

void iconv_to_charset(struct dvb_v5_fe_parms *parms,
		      char *dest,
		      size_t destlen,
		      const unsigned char *src,
		      size_t len,
		      char *type, char *output_charset);

void parse_string(struct dvb_v5_fe_parms *parms, char **dest, char **emph,
		  const unsigned char *src, size_t len,
		  char *default_charset, char *output_charset);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
