/* gbp-noop-runtime.c
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

#define G_LOG_DOMAIN "gbp-noop-runtime"

#include "config.h"

#include <libide-foundry.h>

#include "ide-run-context-private.h"

#include "gbp-host-runtime.h"
#include "gbp-noop-runtime.h"

struct _GbpNoopRuntime
{
  IdeRuntime parent_instance;
};

G_DEFINE_FINAL_TYPE (GbpNoopRuntime, gbp_noop_runtime, IDE_TYPE_RUNTIME)

static gboolean
gbp_noop_runtime_contains_program_in_path (IdeRuntime   *runtime,
                                           const char   *program,
                                           GCancellable *cancellable)
{
  return g_find_program_in_path (program) != NULL;
}

static void
gbp_noop_runtime_prepare_to_build (IdeRuntime    *runtime,
                                   IdePipeline   *pipeline,
                                   IdeRunContext *run_context)
{
  IDE_ENTRY;

  g_assert (GBP_IS_NOOP_RUNTIME (runtime));
  g_assert (IDE_IS_PIPELINE (pipeline));
  g_assert (IDE_IS_RUN_CONTEXT (run_context));

  ide_run_context_add_minimal_environment (run_context);
  _ide_run_context_push_user_shell (run_context, TRUE);

  IDE_EXIT;
}

static void
gbp_noop_runtime_prepare_to_run (IdeRuntime    *runtime,
                                 IdePipeline   *pipeline,
                                 IdeRunContext *run_context)
{
  _gbp_host_runtime_prepare_to_run (pipeline, run_context);
}


static void
gbp_noop_runtime_class_init (GbpNoopRuntimeClass *klass)
{
  IdeRuntimeClass *runtime_class = IDE_RUNTIME_CLASS (klass);

  runtime_class->contains_program_in_path = gbp_noop_runtime_contains_program_in_path;
  runtime_class->prepare_to_run = gbp_noop_runtime_prepare_to_run;
  runtime_class->prepare_to_build = gbp_noop_runtime_prepare_to_build;
}

static void
gbp_noop_runtime_init (GbpNoopRuntime *self)
{
  ide_runtime_set_icon_name (IDE_RUNTIME (self), "container-terminal-symbolic");
}