/* find-other-file-plugin.c
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

#define G_LOG_DOMAIN "find-other-file-plugin"

#include "config.h"

#include <libpeas/peas.h>

#include <libide-gui.h>
#include <libide-projects.h>

#include "gbp-simple-similar-file-locator.h"
#include "gbp-find-other-file-workspace-addin.h"

_IDE_EXTERN void
_gbp_find_other_file_register_types (PeasObjectModule *module)
{
  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_SIMILAR_FILE_LOCATOR,
                                              GBP_TYPE_SIMPLE_SIMILAR_FILE_LOCATOR);
  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_WORKSPACE_ADDIN,
                                              GBP_TYPE_FIND_OTHER_FILE_WORKSPACE_ADDIN);
}
