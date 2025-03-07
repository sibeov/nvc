//
//  Copyright (C) 2023  Nick Gasson
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "util.h"
#include "jit/jit.h"
#include "rt/model.h"

#include <stdlib.h>
#include <stdio.h>

static void verilog_printf(jit_scalar_t *args)
{
   const char *fmt = (*args++).pointer, *start = fmt, *p = fmt;

   for (; *p; p++) {
      if (*p == '%') {
         if (start < p)
            fwrite(start, 1, p - start, stdout);

         switch (*++p) {
         case 's':
            fputs((*args++).pointer, stdout);
            break;
         default:
            jit_msg(NULL, DIAG_FATAL, "unknown format specifier '%c'", *p);
         }

         start = p + 1;
      }
   }

   if (start < p)
      fwrite(start, 1, p - start, stdout);
}

DLLEXPORT
void __nvc_sys_finish(void)
{
   notef("$finish called");
   jit_abort(0);
}

DLLEXPORT
void __nvc_sys_display(jit_scalar_t *args)
{
   verilog_printf(args);
   fputc('\n', stdout);
   fflush(stdout);
}

DLLEXPORT
void __nvc_sys_write(jit_scalar_t *args)
{
   verilog_printf(args);
   fflush(stdout);
}

void _verilog_init(void)
{
   // Dummy function to force linking
}
