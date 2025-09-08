project('orbit-sim', 'cpp')

incdir = include_directories('include')

sfml_dep = dependency('sfml')
entt_dep = dependency('entt')
json_dep = dependency('nlohmann_json')

src_files = files(
  'src/main.cpp',
  'src/systems/physics_system.cpp',
  'src/systems/render_system.cpp',
  'src/systems/camera_system.cpp',
  'src/utils/camera_utils.cpp',
  'src/components/body.cpp',
  'src/components/pos.cpp',
  'src/components/vel.cpp',
  'src/systems/save_load_system.cpp',
)

executable('orbit-sim', src_files,
  dependencies: [sfml_dep, entt_dep, json_dep],
  include_directories: incdir)
