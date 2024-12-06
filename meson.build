project('jherrylib', 'cpp', 
    version: '0.4.2.0',
    license: 'MIT',
    meson_version: '>= 1.2.0',
    default_options: [
        'cpp_std=c++17',
        'buildtype=debugoptimized',
        'debug=true'
    ]
)

cc = meson.get_compiler('cpp')

deps = []
deps += dependency('vulkan')
deps += cc.find_library('SDL2', required: true)
deps += cc.find_library('SDL2_ttf', required: true)

args = []
args += ['-lm', '-msse3']

src = [
    'tahm/tahm/audio.cpp',
    'tahm/tahm/font.cpp',
    'tahm/tahm/graphics.cpp',
    'tahm/tahm/renderer.cpp',
    'tahm/tahm/sound.cpp',
    'tahm/tahm/tahm.cpp',
    'tahm/tahm/util.cpp',
    'tahm/tahm/window.cpp',
    'tahm/tahm/audio.cpp',
    'tahm/engine.cpp',
    'tahm/main.cpp'
]

executable(
    'tahm', 
    src,
    cpp_args: args,
    dependencies: deps
)