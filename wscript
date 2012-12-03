#! /usr/bin/env python

# the following two variables are used by the target "waf dist"
VERSION='0.0'
APPNAME='w30disk'

# these variables are mandatory ('/' are converted automatically)
top = '.'
out = 'build'

def options(opt):
    opt.tool_options('compiler_cc')

def configure(conf):
    conf.check_tool('compiler_cc')
    conf.check(header_name='stdlib.h')
    conf.check(header_name='math.h')
    
    # set for debugging
    conf.env.CCFLAGS = ['-O0', '-g3']

    conf.check_cfg(package = 'sndfile', uselib_store='SNDFILE', atleast_version = '1.0', mandatory=True, args = '--cflags --libs')
    
def build(bld):
    # the main program
    bld(
        features = 'c cprogram',
        source = ['s50tool.c', 'roland.c', ],
        target = 's50tool',
        uselib = "SNDFILE",
        includes = '. /usr/include')

