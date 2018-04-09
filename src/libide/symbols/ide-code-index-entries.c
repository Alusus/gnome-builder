/* ide-code-index-entries.c
 *
 * Copyright 2017 Anoop Chandu <anoopchandu96@gmail.com>
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
 */

#define G_LOG_DOMAIN "ide-code-index-entries"

#include "config.h"

#include "application/ide-application.h"
#include "symbols/ide-code-index-entries.h"
#include "threading/ide-task.h"
#include "util/ide-glib.h"

G_DEFINE_INTERFACE (IdeCodeIndexEntries, ide_code_index_entries, G_TYPE_OBJECT)

static void
ide_code_index_entries_real_next_entries_async (IdeCodeIndexEntries *self,
                                                GCancellable        *cancellable,
                                                GAsyncReadyCallback  callback,
                                                gpointer             user_data)
{
  g_autoptr(IdeTask) task = NULL;
  g_autoptr(GPtrArray) ret = NULL;
  IdeCodeIndexEntry *entry;

  g_assert (IDE_IS_MAIN_THREAD ());
  g_assert (IDE_IS_CODE_INDEX_ENTRIES (self));
  g_assert (!cancellable || G_IS_CANCELLABLE (cancellable));

  task = ide_task_new (self, cancellable, callback, user_data);
  ide_task_set_source_tag (task, ide_code_index_entries_real_next_entries_async);
  ide_task_set_priority (task, G_PRIORITY_LOW);
  ide_task_set_kind (task, IDE_TASK_KIND_INDEXER);

  ret = g_ptr_array_new_with_free_func ((GDestroyNotify)ide_code_index_entry_free);

  while ((entry = ide_code_index_entries_get_next_entry (self)))
    g_ptr_array_add (ret, g_steal_pointer (&entry));

  ide_task_return_pointer (task, g_steal_pointer (&ret), (GDestroyNotify)g_ptr_array_unref);
}

static GPtrArray *
ide_code_index_entries_real_next_entries_finish (IdeCodeIndexEntries  *self,
                                                 GAsyncResult         *result,
                                                 GError              **error)
{
  GPtrArray *ret;

  g_assert (IDE_IS_CODE_INDEX_ENTRIES (self));
  g_assert (IDE_IS_TASK (result));

  ret = ide_task_propagate_pointer (IDE_TASK (result), error);

  return IDE_PTR_ARRAY_STEAL_FULL (&ret);
}

static IdeCodeIndexEntry *
ide_code_index_entries_real_get_next_entry (IdeCodeIndexEntries *self)
{
  return NULL;
}

static void
ide_code_index_entries_default_init (IdeCodeIndexEntriesInterface *iface)
{
  iface->get_next_entry = ide_code_index_entries_real_get_next_entry;
  iface->next_entries_async = ide_code_index_entries_real_next_entries_async;
  iface->next_entries_finish = ide_code_index_entries_real_next_entries_finish;
}

/**
 * ide_code_index_entries_get_next_entry:
 * @self: An #IdeCodeIndexEntries instance.
 *
 * This will fetch next entry in index.
 *
 * When all of the entries have been exhausted, %NULL should be returned.
 *
 * Returns: (nullable) (transfer full): An #IdeCodeIndexEntry.
 *
 * Since: 3.26
 */
IdeCodeIndexEntry *
ide_code_index_entries_get_next_entry (IdeCodeIndexEntries *self)
{
  g_return_val_if_fail (IDE_IS_MAIN_THREAD (), NULL);
  g_return_val_if_fail (IDE_IS_CODE_INDEX_ENTRIES (self), NULL);

  return IDE_CODE_INDEX_ENTRIES_GET_IFACE (self)->get_next_entry (self);
}

/**
 * ide_code_index_entries_get_file:
 * @self: a #IdeCodeIndexEntries
 *
 * The file that was indexed.
 *
 * Returns: (transfer full): a #GFile
 */
GFile *
ide_code_index_entries_get_file (IdeCodeIndexEntries *self)
{
  g_return_val_if_fail (IDE_IS_MAIN_THREAD (), NULL);
  g_return_val_if_fail (IDE_IS_CODE_INDEX_ENTRIES (self), NULL);

  return IDE_CODE_INDEX_ENTRIES_GET_IFACE (self)->get_file (self);
}

/**
 * ide_code_index_entries_next_entries_async:
 * @self: a #IdeCodeIndexEntries
 * @cancellable: (nullable): a #GCancellable or %NULL
 * @callback: a callback to execute upon completion
 * @user_data: user data for @callback, or %NULL
 *
 * Requests the next set of results from the code index asynchronously.
 * This allows implementations to possibly process data off the main thread
 * without blocking the main loop.
 *
 * Since: 3.30
 */
void
ide_code_index_entries_next_entries_async (IdeCodeIndexEntries *self,
                                           GCancellable        *cancellable,
                                           GAsyncReadyCallback  callback,
                                           gpointer             user_data)
{
  g_return_if_fail (IDE_IS_MAIN_THREAD ());
  g_return_if_fail (IDE_IS_CODE_INDEX_ENTRIES (self));
  g_return_if_fail (!cancellable || G_IS_CANCELLABLE (cancellable));

  IDE_CODE_INDEX_ENTRIES_GET_IFACE (self)->next_entries_async (self, cancellable, callback, user_data);
}

/**
 * ide_code_index_entries_next_entries_finish:
 * @self: a #IdeCodeIndexEntries
 * @result: a #GAsyncResult provided to callback
 * @error: a location for a #GError, or %NULL
 *
 * Completes an asynchronous request for the next set of entries from the index.
 *
 * Returns: (transfer full) (element-type Ide.CodeIndexEntry): a #GPtrArray
 *   of #IdeCodeIndexEntry.
 *
 * Since: 3.30
 */
GPtrArray *
ide_code_index_entries_next_entries_finish (IdeCodeIndexEntries  *self,
                                            GAsyncResult         *result,
                                            GError              **error)
{
  g_return_val_if_fail (IDE_IS_MAIN_THREAD (), NULL);
  g_return_val_if_fail (IDE_IS_CODE_INDEX_ENTRIES (self), NULL);
  g_return_val_if_fail (G_IS_ASYNC_RESULT (result), NULL);

  return IDE_CODE_INDEX_ENTRIES_GET_IFACE (self)->next_entries_finish (self, result, error);
}
