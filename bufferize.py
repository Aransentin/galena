#!/usr/bin/env python3
import sys

data = sys.stdin.read()

sys.stdout.write( "static const char kernel_src_str[%d]={" % (len(data),) );
for c in data:
	sys.stdout.write( str(ord(c)) )
	sys.stdout.write( "," )
	
sys.stdout.write( "};\n" );
