import sys
import subprocess

SHELL_CMD = ('cmd', '/c',)
ENV_CMD   = '..\qt481msvc2010env.bat'

def call(cmd):
    #subprocess.check_call(('echo', str(cmd)),  stderr=subprocess.STDOUT, shell=False)
    subprocess.check_call(list(SHELL_CMD) + list(cmd), stderr=subprocess.STDOUT, shell=False)

def call_cmake(build_dir, build_type, arch):
    call((
        'cd', build_dir,
        '&&', ENV_CMD,
	    '&&', 'cmake', '../repo', '-DCMAKE_BUILD_TYPE=' + build_type, '-DARCH=' + arch, '-G', 'CodeBlocks - NMake Makefiles',
        ))
    #'&&', 'cmake', '../repo', '-DCMAKE_BUILD_TYPE=' + build_type, '-DARCH=' + arch, '-G', 'Visual Studio 10',
    #'&&', 'cmake', '../repo', '-DCMAKE_BUILD_TYPE=' + build_type, '-G', 'NMake Makefiles JOM',
    #'&&', 'cmake', '../repo', '-DCMAKE_BUILD_TYPE=' + build_type, '-G', 'NMake Makefiles',
	#'&&', 'cmake', '../repo', '-DCMAKE_BUILD_TYPE=' + build_type, '-DARCH=' + arch, '-G', 'CodeBlocks - NMake Makefiles',

def call_make(build_dir):
    call([
        'cd', build_dir,
        '&&', ENV_CMD,
        '&&', 'jom.exe', '-j', '3',
        ]
        + sys.argv[1:])
    #'&&', 'jom.exe', '-j', '3',
    #'&&', 'nmake.exe',
    #'&&', 'msbuild.exe', 'dicomv.sln',
