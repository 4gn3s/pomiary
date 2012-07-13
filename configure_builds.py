import common
import os
import subprocess

def create_dir(dir):
    if not os.path.exists(dir):
        os.makedirs(dir)

def main():
    pwd = os.path.dirname(os.path.realpath(__file__))
    create_dir(os.path.join(pwd, 'debug32'))
    create_dir(os.path.join(pwd, 'release32'))
    create_dir(os.path.join(pwd, 'debug64'))
    create_dir(os.path.join(pwd, 'release64'))
    common.call_cmake(os.path.join(pwd, 'debug32'), 'Debug', '32bits')
    common.call_cmake(os.path.join(pwd, 'release32'), 'Release', '32bits')
    common.call_cmake(os.path.join(pwd, 'debug64'), 'Debug', '64bits')
    common.call_cmake(os.path.join(pwd, 'release64'), 'Release', '64bits')


if __name__=='__main__':
    main()
