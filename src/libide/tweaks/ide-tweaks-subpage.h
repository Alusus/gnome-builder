/* ide-tweaks-subpage.h
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

#include "ide-tweaks-item.h"

G_BEGIN_DECLS

#define IDE_TYPE_TWEAKS_SUBPAGE (ide_tweaks_subpage_get_type())

IDE_AVAILABLE_IN_ALL
G_DECLARE_FINAL_TYPE (IdeTweaksSubpage, ide_tweaks_subpage, IDE, TWEAKS_SUBPAGE, IdeTweaksItem)

IDE_AVAILABLE_IN_ALL
IdeTweaksSubpage *ide_tweaks_subpage_new       (void);
IDE_AVAILABLE_IN_ALL
const char       *ide_tweaks_subpage_get_title (IdeTweaksSubpage *self);
IDE_AVAILABLE_IN_ALL
void              ide_tweaks_subpage_set_title (IdeTweaksSubpage *self,
                                                const char       *title);

G_END_DECLS
