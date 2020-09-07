#!/usr/bin/env python
"""read line following robot csv"""

import argparse
import csv
from matplotlib import pyplot as plt
from os import listdir
from os.path import isfile, join, basename, exists

mmdir = join("..", "into-cps", "Multi-models")

parser = argparse.ArgumentParser(description='Get line following robot path.')
parser.add_argument('-n', action='store_true', help='hide background.')
parser.add_argument('path', type=str, nargs='?', default=None, help='csv path in file system.')

args = parser.parse_args()

def showmenu(objname, entries):
	idx = 1
	if len(entries) == 0:
		print("No " + objname + " to display.")
		quit()
	if len(entries) == 1:
		print(objname + " '" + str(basename(entries[0])) + "' selected automatically (only one available).")
		return 0
	for entry in entries:
		print(str(idx) + ") " + str(basename(entry)))
		idx = idx + 1
	idx = int(input("Select " + objname + ": ")) - 1
	if idx < 0 or idx >= len(entries):
		print("Invalid selection.")
		return showmenu(objname, entries)
	return idx

csvfile = None
if args.path is None:
	print("Searching in '" + str(mmdir) + "'...")
	print()
	mms = [f for f in sorted(listdir(mmdir)) if not isfile(join(mmdir, f))]
	mmidx = showmenu("multi-model", mms)
	print()
	cosims = [f for f in sorted(listdir(join(mmdir, mms[mmidx]))) if not isfile(join(mmdir, mms[mmidx], f))]
	cosimidx = showmenu("co-sim", cosims)
	print()
	results = [f for f in sorted(listdir(join(mmdir, mms[mmidx], cosims[cosimidx]))) if not isfile(join(mmdir, mms[mmidx], cosims[cosimidx], f))]
	residx = showmenu("result", results)
	print()
	csvfile = join(mmdir, mms[mmidx], cosims[cosimidx], results[residx], "outputs.csv")
else:
	csvfile = args.path

if not exists(csvfile):
	print("File '" + csvfile + "' does not exists.")
	quit()

print("Reading csv file '" + csvfile + "'...")

with open(csvfile) as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
	titles = next(spamreader)
	xidx = 0
	yidx = 1
	idx = 0
	for title in titles:
		if (title.endswith("robot_x")):
			xidx = idx
		if (title.endswith("robot_y")):
			yidx = idx
		idx = idx + 1
	x = []
	y = []
	next(spamreader) # skip first line (always 0,0)
	for row in spamreader:
		x.append(float(row[xidx]))
		y.append(float(row[yidx]))
data = {titles[xidx]: x, titles[yidx]: y}

print("Plotting...")

plt.figure()
if not args.n:
	img = plt.imread("map.png")
	plt.imshow(img, extent=[-0.3, 0.3, -0.4, 0.4])
plt.scatter(data[titles[xidx]], data[titles[yidx]], c='b')
plt.xlabel(titles[xidx])
plt.ylabel(titles[yidx])
plt.show()
print("Exiting...")
