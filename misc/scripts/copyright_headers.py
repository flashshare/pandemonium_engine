#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

header = """\
/*************************************************************************/
/*  $filename                                                            */
/*************************************************************************/
/*                         This file is part of:                         */
/*                          PANDEMONIUM ENGINE                           */
/*             https://github.com/Relintai/pandemonium_engine            */
/*************************************************************************/
/* Copyright (c) 2022-present Péter Magyar.                              */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
"""

fname = sys.argv[1]

# Handle replacing $filename with actual filename and keep alignment
fsingle = fname.strip()
if fsingle.find("/") != -1:
    fsingle = fsingle[fsingle.rfind("/") + 1 :]
rep_fl = "$filename"
rep_fi = fsingle
len_fl = len(rep_fl)
len_fi = len(rep_fi)
# Pad with spaces to keep alignment
if len_fi < len_fl:
    for x in range(len_fl - len_fi):
        rep_fi += " "
elif len_fl < len_fi:
    for x in range(len_fi - len_fl):
        rep_fl += " "
if header.find(rep_fl) != -1:
    text = header.replace(rep_fl, rep_fi)
else:
    text = header.replace("$filename", fsingle)
text += "\n"

# We now have the proper header, so we want to ignore the one in the original file
# and potentially empty lines and badly formatted lines, while keeping comments that
# come after the header, and then keep everything non-header unchanged.
# To do so, we skip empty lines that may be at the top in a first pass.
# In a second pass, we skip all consecutive comment lines starting with "/*",
# then we can append the rest (step 2).

fileread = open(fname.strip(), "r")
line = fileread.readline().strip()
header_done = False

orig_lines = ""

while line == "" or line.startswith("#ifndef") or line.startswith("#define"):  # Skip empty lines at the top, and include guards
    if line != "":
        orig_lines += line + "\n"

    line = fileread.readline()
    line = line.strip()

line += "\n"

if orig_lines != "":
    text = orig_lines + "\n" + text

if line.find("/**********") == -1:  # Pandemonium header starts this way
    # Maybe starting with a non-Pandemonium comment, abort header magic
    header_done = True

while not header_done:  # Handle header now
    if line.find("/*") != 0:  # No more starting with a comment
        header_done = True
        if line.strip() != "":
            text += line
    line = fileread.readline()

while line != "":  # Dump everything until EOF
    text += line
    line = fileread.readline()

fileread.close()

# Write
filewrite = open(fname.strip(), "w")
filewrite.write(text)
filewrite.close()
