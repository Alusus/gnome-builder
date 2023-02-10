/* gbp-sublime-preferences-addin.c
 *
 * Copyright 2018-2019 Christian Hergert <chergert@redhat.com>
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

#define G_LOG_DOMAIN "gbp-sublime-preferences-addin"

#include "config.h"

#include <glib/gi18n.h>
#include <libide-gui.h>

#include "gbp-sublime-preferences-addin.h"

struct _GbpSublimePreferencesAddin
{
  GObject parent_instance;
  guint   keybinding_id;
};

static void
gbp_sublime_preferences_addin_load (IdePreferencesAddin *addin,
                                    DzlPreferences      *preferences)
{
  GbpSublimePreferencesAddin *self = (GbpSublimePreferencesAddin *)addin;

  g_assert (GBP_IS_SUBLIME_PREFERENCES_ADDIN (self));
  g_assert (DZL_IS_PREFERENCES (preferences));

  self->keybinding_id = dzl_preferences_add_radio (preferences,
                                                   "keyboard",
                                                   "mode",
                                                   "org.alusus.alwarsha.editor",
                                                   "keybindings",
                                                   NULL,
                                                   "\"sublime\"",
                                                   _("Sublime Text"),
                                                   _("Emulates the Sublime Text editor"),
                                                   NULL,
                                                   20);
}

static void
gbp_sublime_preferences_addin_unload (IdePreferencesAddin *addin,
                                      DzlPreferences      *preferences)
{
  GbpSublimePreferencesAddin *self = (GbpSublimePreferencesAddin *)addin;

  g_assert (GBP_IS_SUBLIME_PREFERENCES_ADDIN (self));
  g_assert (DZL_IS_PREFERENCES (preferences));

  dzl_preferences_remove_id (preferences, self->keybinding_id);
}

static void
preferences_addin_iface_init (IdePreferencesAddinInterface *iface)
{
  iface->load = gbp_sublime_preferences_addin_load;
  iface->unload = gbp_sublime_preferences_addin_unload;
}

G_DEFINE_FINAL_TYPE_WITH_CODE (GbpSublimePreferencesAddin, gbp_sublime_preferences_addin, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (IDE_TYPE_PREFERENCES_ADDIN,
                                                preferences_addin_iface_init))

static void
gbp_sublime_preferences_addin_class_init (GbpSublimePreferencesAddinClass *klass)
{
}

static void
gbp_sublime_preferences_addin_init (GbpSublimePreferencesAddin *self)
{
}
