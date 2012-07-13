import common
import os

def main():
    pwd = os.path.dirname(os.path.realpath(__file__))
    common.call_make(os.path.join(pwd, 'release32'))


if __name__=='__main__':
    main()
