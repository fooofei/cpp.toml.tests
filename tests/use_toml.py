#coding=utf-8
'''
pip install toml
# not pip install pytoml
'''

import os
import sys
import toml

curpath = os.path.realpath(__file__)
curpath = os.path.dirname(curpath)

def entry():

  sample_toml1 = os.path.join(curpath,'simple_toml.toml')

  with open(sample_toml1,'rb') as fr:
    parser = toml.load(fr)

    # exception on u'empty_key8=nil'
    # line 454 raise TomlDecodeError("Invalid date or number")
    import pdb
    pdb.set_trace()



if __name__ == '__main__':
    entry()
