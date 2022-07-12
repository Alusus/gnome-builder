/* ide-webkit-page.h
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

#include <libide-gui.h>

#include "ide-html-generator.h"

G_BEGIN_DECLS

#define IDE_TYPE_WEBKIT_PAGE (ide_webkit_page_get_type())

IDE_AVAILABLE_IN_ALL
G_DECLARE_DERIVABLE_TYPE (IdeWebkitPage, ide_webkit_page, IDE, WEBKIT_PAGE, IdePage)

struct _IdeWebkitPageClass
{
  IdePageClass parent_class;
};

IDE_AVAILABLE_IN_ALL
IdeWebkitPage *ide_webkit_page_new                   (void);
IDE_AVAILABLE_IN_ALL
IdeWebkitPage *ide_webkit_page_new_for_generator     (IdeHtmlGenerator     *generator);
IDE_AVAILABLE_IN_ALL
void           ide_webkit_page_load_uri              (IdeWebkitPage        *self,
                                                      const char           *uri);
IDE_AVAILABLE_IN_ALL
gboolean       ide_webkit_page_focus_address         (IdeWebkitPage        *self);
IDE_AVAILABLE_IN_ALL
gboolean       ide_webkit_page_get_show_toolbar      (IdeWebkitPage        *self);
IDE_AVAILABLE_IN_ALL
void           ide_webkit_page_set_show_toolbar      (IdeWebkitPage        *self,
                                                      gboolean              show_toolbar);
IDE_AVAILABLE_IN_ALL
void           ide_webkit_page_go_back               (IdeWebkitPage        *self);
IDE_AVAILABLE_IN_ALL
void           ide_webkit_page_go_forward            (IdeWebkitPage        *self);
IDE_AVAILABLE_IN_ALL
void           ide_webkit_page_reload                (IdeWebkitPage        *self);
IDE_AVAILABLE_IN_ALL
void           ide_webkit_page_reload_ignoring_cache (IdeWebkitPage        *self);

G_END_DECLS