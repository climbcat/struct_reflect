#!/usr/bin/env python
# -*- coding: utf-8 -*-
import logging
import argparse
import json
import re
from _codecs import decode

'''
This code is meant to be used with the python middleware interface functions:

def publish(obj, topic): pass
def listen() -> dict:

'''

def _get_example():

    obj = {}
    obj["count"] = 17
    obj["temp"] = 19.2
    obj["info"] = "fredag"
    
    jsons = json.dumps(obj, indent=2)
    print(jsons)

    return obj


def cogen_decode(obj, structname):

    lines = [];
    lines.append("%s decode_%s(string rjsons){" % (structname, structname.lower()))
    lines.append("  %s pack;" % structname)

    for key, value in obj.items():

        if type(value) == int:
            lines.append('  pack.%s = find_int("%s");' % (key, key) )
        elif type(value) == float:
            lines.append('  pack.%s = find_double("%s");' % (key, key) )
        elif type(value) == str:
            lines.append('  pack.%s = find_string("%s");' % (key, key) )
        elif type(value) == list:
            # TODO: impl single-typed list handling
            pass
        
    lines.append("  return pack;")
    lines.append("}")
    
    return "\n".join(lines)

def cogen_encode(obj, structname):
    
    lines = []
    lines.append("string encode_%s(%s pack){" % (structname.lower(), structname))
    lines.append("  return \"{\"")
    
    for key, value in obj.items():
        if value == "int":
            lines.append('    + "%s:" + to_string(pack.%s)' % (key, key) )
        elif value == "double":
            lines.append('    + "%s:" + to_string(pack.%s)' % (key, key) )
        elif value == "string":
            lines.append('    + "%s:" + pack.%s' % (key, key) )
        elif type(value) == list:
            # TODO: impl single-typed list handling
            pass

    lines[-1] = lines[-1] + ";"
    lines.append('};')

    return "\n".join(lines)


def parse_dataspec_cpp(text):
    '''
    The .cpp file must contain a simple struct at the beginning of the file.
    '''
    # extract the first struct from the input file
    dataspec_struct_pat = "(?s)struct\s+(\w[0-9\w]*)\s*\{.*?\}" # .*? means non-greedy
    m = re.search(dataspec_struct_pat, text) # (?s) will make dot match newlines, too
    if m == None:
        print("file did not contain a dataspec struct (matcning pattern: %s)" % dataspec_struct_pat)
        exit()
    struct_decl = m.group()
    struct_name = m.group(1)

    # separate struct name and declaration lines
    m = re.match("(?s)struct\s+%s\s+\{(.*)\}" % struct_name, struct_decl)
    if m == None:
        print("could not parse dataspec struct")
        exit()
    struct_lines = m.group(1).strip()
    
    # extract type, field info from declaration lines
    dataspec = {}
    for line in struct_lines.split(';'): # \n based splitting is not robust
        line = line.strip('\n').strip() # clean the segment for less matching ambiguity
        if re.match("\s*$", line): # skip empty lines
            continue

        if re.match("\/\/", line):
            continue

        m = re.match("((?!\d)\w[0-9\w]+)\s+((?!\d)\w[0-9\w]*)", line); # (?!\d) means non-digit
        tpe = None
        field = None
        try:
            tpe = m.group(1)
            field = m.group(2)
        except:
            
            # TODO: create the list/* branch here
            
            print('could or would not parse expression "%s;"' % line)
            exit()

        # check for uniqueness
        if field in dataspec.keys():
            print('Error: field "%s" is a duplicate' % field)
            exit()
        
        if tpe not in ("int", "double", "string",):
            print('Error: field "%s" has type "%s". Supported types are int, double and string, and pointers to an int, double or string' % (field, tpe))
            exit()
        dataspec[field] = tpe

    return dataspec, struct_name

def main(args):

    # load the dataspec file
    filename = args.dataspecfile[0]
    if not re.search("\.cpp$", filename):
        print("please input a cpp file containing only a data specification script")
        exit()

    text = ""
    try:
        text = open(filename).read()
    except:
        print("could not open file %s" % filename)
        exit()

    # parse the dataspec
    obj, structname = parse_dataspec_cpp(text)

    # cogen
    encode_text = cogen_encode(obj, structname)
    decode_text = cogen_decode(obj, structname)

    print(encode_text)
    print(decode_text)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('dataspecfile', nargs=1, help='File containing only a data specification cpp struct.')
    args = parser.parse_args()

    main(args)