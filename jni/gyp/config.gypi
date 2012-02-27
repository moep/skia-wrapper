{
#
# Variables
#
	'variables': {
		'target_os%': '<(OS)',
		'skia_root%': 'skia_src'
	},	
	'target_os': '<(target_os)',
	'skia_root': '<(skia_root)',

#
# OS dependent conditions
#
	'conditions': [
		
		# POSIX settings
		#['target_os in ["linux", "freebsd", "openbsd", "solaris"]', 
		['OS == "linux"', 
			{
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
					'lpng',
					'lGL',
					'lGLU',
					'lcore',
					'limages',
					'lports',
					'lutils'
				],
				'linkflags': []
			}
		], # POSIX

		['OS != "linux"', {'error': '<!(blubb)'}]

	] # End of conditions

}

# vim: set expandtab tabstop=2 shiftwidth=2:
