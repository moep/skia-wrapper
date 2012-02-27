# This target is just a wrapper
{
  'includes': [ 
    'gyp/config.gypi'
  ],
  'targets': [
    # Meta target for building everything
    {
      'target_name': 'all',
      'type': 'none',
      'dependencies': [
#        'helloWorld'
      ]
    },

    # This target builds the hello world Skia app
    {
      'target_name': 'helloWorld',
      'type': 'executable',
      'sources' : [
        'src/helloWorld.cpp'
      ],
      'dependencies' : [],
      'cflags': [
			'-Wall',
			'-Wextra',
			'-fPIC'
		],
		'include_dirs': [
			'<(skia_root)/out/Debug/obj.target/core',
			'<(skia_root)/out/Debug/obj.target/config',
			'<(skia_root)/out/Debug/obj.target/images',
			'<(skia_root)/out/Debug/obj.target/ports',
			'<(skia_root)/out/Debug/obj.target/utils',
		],
		'libraries': [
			'-freetype', 
			'-lpthread',
			'-lpng',
			'-lGL',
			'-lGLU',
			'-lcore',
			'-limages',
			'-lports',
			'-lutils'
		],
		'linkflags': []
    }
  ] # End of targets


}

# vim: set expandtab tabstop=2 shiftwidth=2:
