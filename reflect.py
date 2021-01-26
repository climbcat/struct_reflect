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
    obj["list_d3"] = [12.3, 5.0, 666.1]
    obj["list_i3"] = [42, 99, 117]
    obj["list_s3"] = ["oktober", "november", "december"]
    
    jsons = json.dumps(obj, indent=2)
    print(jsons)

    text = json.dumps((obj))
    text = text.replace('"', '\\"')
    return text


def cogen_decode(obj, structname):

    lines = [];
    lines.append("%s decode_%s(string rjsons){" % (structname, structname.lower()))
    lines.append("  %s pack;" % structname)

    for key, value in obj.items():

        if value == "int":
            lines.append('  pack.%s = find_int("%s", rjsons);' % (key, key) )
        elif value == "double":
            lines.append('  pack.%s = find_double("%s", rjsons);' % (key, key) )
        elif value == "string":
            lines.append('  pack.%s = find_string("%s", rjsons);' % (key, key) )

        elif value == "vector<double>":
            lines.append('  pack.%s = find_double_array("%s", rjsons);' % (key, key) )
        elif value == "vector<int>":
            lines.append('  pack.%s = find_int_array("%s", rjsons);' % (key, key) )
        elif value == "vector<string>":
            lines.append('  pack.%s = find_string_array("%s", rjsons);' % (key, key) )

    lines.append("  return pack;")
    lines.append("}")
    
    return "\n".join(lines)

def cogen_encode(obj, structname):
    
    lines = []
    lines.append("string encode_%s(%s pack){" % (structname.lower(), structname))
    lines.append("  string res = \"{\";")
    
    key_lines = [] # do this to fix commas
    for key, value in obj.items():
        if value == "int":
            key_lines.append('  res += "\\"%s\\":" + to_string(pack.%s)' % (key, key) )
        elif value == "double":
            key_lines.append('  res += "\\"%s\\":" + to_string(pack.%s)' % (key, key) )
        elif value == "string":
            key_lines.append('  res += "\\"%s\\":" + pack.%s' % (key, key) )
        elif value == "vector<int>":
            key_lines.append('  res += "\\"%s\\":" + encode_int_list(%s)' % (key, key) )
        elif value == "vector<double>":
            key_lines.append('  res += "\\"%s\\":" + encode_double_list(%s)' % (key, key) )
        elif value == "vector<string>":
            key_lines.append('  res += "\\"%s\\":" + encode_string_list(%s)' % (key, key) )
    key_lines[-1] = key_lines[-1] + ";"
    lines.append(' + ", ";\n'.join(key_lines))
    
    lines.append('  res += "}";')
    lines.append('  return res;')
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

        m = re.match("((?!\d)\w[0-9\w]+)\s+((?!\d)\w[0-9\w]*)", line) # (?!\d) means non-digit
        tpe = None
        field = None
        try:
            tpe = m.group(1)
            field = m.group(2)
        except:
            # vector case
            m2 = re.match("(vector<\w+>)\s+((?!\d)\w[0-9\w]*)", line)
            if m2:
                tpe = m2.group(1)
                field = m2.group(2)
            else:
                print('could not parse expression "%s;"' % line)
                exit()

        # check for uniqueness
        if field in dataspec.keys():
            print('Error: field "%s" is a duplicate' % field)
            exit()
        
        if tpe not in ("int", "double", "string","vector<int>", "vector<double>", "vector<string>",):
            print('Error: field "%s" has type "%s". Supported types are int, double and string, and vector of int, double or string' % (field, tpe))
            exit()
        dataspec[field] = tpe

    return dataspec, struct_name, struct_decl

def get_header():
    head = []
    head.append('#include "keyfinder.cpp"')
    head.append('#include <string>')
    head.append('#include <vector>')
    head.append('using std::string;')
    return "\n".join(head)

def main(args):

    # print an examle json string 
    if args.test:
        print(_get_example())
        exit()

    # load the dataspec file
    filename = args.dataspecfile
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
    obj, structname, structdecl = parse_dataspec_cpp(text)

    # cogen
    encode_text = cogen_encode(obj, structname)
    decode_text = cogen_decode(obj, structname)
    header = get_header()
    
    print(header + "\n" + structdecl + ";" + "\n" + encode_text + "\n" + decode_text)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('dataspecfile', nargs='?', help='File containing only a data specification cpp struct.')
    parser.add_argument('--test', action="store_true", help='Test.')
    args = parser.parse_args()

    main(args)
