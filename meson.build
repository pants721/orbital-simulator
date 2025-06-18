project('orbit-sim', 'cpp')

incdir = include_directories('include')

sfml_dep = dependency('sfml')
entt_dep = dependency('entt')

src_files = files(
  'src/main.cpp',
  'src/systems/physics_system.cpp',
  'src/systems/render_system.cpp',
  'src/systems/camera_system.cpp',
)

executable('orbit-sim', src_files,
  dependencies: [sfml_dep, entt_dep],
  include_directories: incdir)
