/* gbp-sysprof-page.h
 *
 * Copyright 2022 Christian Hergert <chergert@redhat.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <sysprof.h>

#include <libide-gui.h>

G_BEGIN_DECLS

#define GBP_TYPE_SYSPROF_PAGE (gbp_sysprof_page_get_type())

G_DECLARE_FINAL_TYPE (GbpSysprofPage, gbp_sysprof_page, GBP, SYSPROF_PAGE, IdePage)

GbpSysprofPage *gbp_sysprof_page_new_for_file     (GFile           *file);
GbpSysprofPage *gbp_sysprof_page_new_for_profiler (SysprofProfiler *profiler);
GFile          *gbp_sysprof_page_get_file         (GbpSysprofPage  *self);

G_END_DECLS
