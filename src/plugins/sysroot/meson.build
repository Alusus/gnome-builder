if get_option('plugin_sysroot')

plugins_sources += files([
  'sysroot-plugin.c',
  'gbp-sysroot-manager.c',
  'gbp-sysroot-runtime.c',
  'gbp-sysroot-runtime-provider.c',
  'gbp-sysroot-toolchain-provider.c',
])

plugin_sysroot_resources = gnome.compile_resources(
  'sysroot-resources',
  'sysroot.gresource.xml',
  c_name: 'gbp_sysroot',
)

plugins_sources += plugin_sysroot_resources

endif
