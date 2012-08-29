from __future__ import print_function
import csv
import codecs
import sys
# This script filters a Google contacts CSV file keeping only the names listed on stdin

import argparse

parser = argparse.ArgumentParser(description='Filters a Google contacts CSV file keeping only the names listed on stdin.')
parser.add_argument('filename',
                   help='a Google contacts CSV file')

args = parser.parse_args()
sys.stderr.write('Enter the contact names to keep, one per line\n')
names = sys.stdin.readlines()
sys.stderr.write("Read %d names from stdin\n" % (len(names),))
with codecs.open(args.filename, 'r', encoding='utf_16') as inputfile:
    creader = csv.reader(inputfile, delimiter=',')
    contacts = []
    for c in creader:
        contacts.append(c)
sys.stderr.write("Read %d contacts from %s\n" % (len(contacts), args.filename))

outputs = [contacts[0]] # first line is a header line
for n in names:
    #~ inames = [x[0] for x in contacts]
    #~ print(repr(inames[10]))
    #~ print(repr(n.strip()))
    outputs.extend([x for x in contacts if x[0] == n.strip()])

sys.stderr.write("%d matches\n" % (len(outputs),))
#~ print(repr(outputs))

cwriter = csv.writer(sys.stdout, delimiter=',')
cwriter.writerows(outputs)
