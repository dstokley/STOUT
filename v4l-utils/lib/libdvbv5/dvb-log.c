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

#include <libdvbv5/dvb-log.h>

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
#include <config.h>

#ifdef ENABLE_NLS
# include "gettext.h"
# include <libintl.h>
# define _(string) dgettext(LIBDVBV5_DOMAIN, string)

#else
# define _(string) string
#endif

# define N_(string) string


<<<<<<< HEAD
=======
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
static const struct loglevel {
	const char *name;
	const char *color;
	int fd;
} loglevels[9] = {
<<<<<<< HEAD
<<<<<<< HEAD
	{N_("EMERG    "), "\033[31m", STDERR_FILENO },
	{N_("ALERT    "), "\033[31m", STDERR_FILENO },
	{N_("CRITICAL "), "\033[31m", STDERR_FILENO },
	{N_("ERROR    "), "\033[31m", STDERR_FILENO },
	{N_("WARNING  "), "\033[33m", STDOUT_FILENO },
	{NULL,            "\033[36m", STDOUT_FILENO }, /* NOTICE */
	{NULL,            NULL,       STDOUT_FILENO }, /* INFO */
	{N_("DEBUG    "), "\033[32m", STDOUT_FILENO },
	{NULL,            "\033[0m",  STDOUT_FILENO }, /* reset*/
=======
=======
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	{"EMERG    ", "\033[31m", STDERR_FILENO },
	{"ALERT    ", "\033[31m", STDERR_FILENO },
	{"CRITICAL ", "\033[31m", STDERR_FILENO },
	{"ERROR    ", "\033[31m", STDERR_FILENO },
	{"WARNING  ", "\033[33m", STDOUT_FILENO },
	{"",          "\033[36m", STDOUT_FILENO }, /* NOTICE */
	{"",          NULL,       STDOUT_FILENO }, /* INFO */
	{"DEBUG    ", "\033[32m", STDOUT_FILENO },
	{"",          "\033[0m",  STDOUT_FILENO }, /* reset*/
<<<<<<< HEAD
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
=======
	{N_("EMERG    "), "\033[31m", STDERR_FILENO },
	{N_("ALERT    "), "\033[31m", STDERR_FILENO },
	{N_("CRITICAL "), "\033[31m", STDERR_FILENO },
	{N_("ERROR    "), "\033[31m", STDERR_FILENO },
	{N_("WARNING  "), "\033[33m", STDOUT_FILENO },
	{NULL,            "\033[36m", STDOUT_FILENO }, /* NOTICE */
	{NULL,            NULL,       STDOUT_FILENO }, /* INFO */
	{N_("DEBUG    "), "\033[32m", STDOUT_FILENO },
	{NULL,            "\033[0m",  STDOUT_FILENO }, /* reset*/
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
};
#define LOG_COLOROFF 8

void dvb_default_log(int level, const char *fmt, ...)
{
	if(level > sizeof(loglevels) / sizeof(struct loglevel) - 2) // ignore LOG_COLOROFF as well
		level = LOG_INFO;
	va_list ap;
	va_start(ap, fmt);
	FILE *out = stdout;
	if (STDERR_FILENO == loglevels[level].fd)
		out = stderr;
	if (loglevels[level].color && isatty(loglevels[level].fd))
		fputs(loglevels[level].color, out);
<<<<<<< HEAD
<<<<<<< HEAD
	if (loglevels[level].name)
		fprintf(out, "%s", _(loglevels[level].name));
=======
	fprintf(out, "%s", loglevels[level].name);
>>>>>>> b1f14ac63b12fb60bbbe4b94bce6651a12e5d2f2
=======
	fprintf(out, "%s", loglevels[level].name);
=======
	if (loglevels[level].name)
		fprintf(out, "%s", _(loglevels[level].name));
>>>>>>> e31bcf40f130f2350c9b88436caf5a7d1c1dfc5d
>>>>>>> 77342727cd17097e98fd40bc9ff338753144b1e0
	vfprintf(out, fmt, ap);
	fprintf(out, "\n");
	if(loglevels[level].color && isatty(loglevels[level].fd))
		fputs(loglevels[LOG_COLOROFF].color, out);
	va_end(ap);
}

