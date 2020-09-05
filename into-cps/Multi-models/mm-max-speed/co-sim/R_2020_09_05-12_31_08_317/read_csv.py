import argparse
import csv
from matplotlib import pyplot as plt


parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('path', type=str, help='csv path in file sysetm')

args = parser.parse_args()

with open(args.path) as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
    titles = next(spamreader)
    x = []
    y = []
    for row in spamreader:
        x.append(float(row[8]))
        y.append(float(row[9]))
data = {titles[8]:x,titles[9]:y}
plt.figure()
plt.scatter(data[titles[8]],data[titles[9]])
plt.xlabel(titles[8])
plt.ylabel(titles[9])
plt.show()
