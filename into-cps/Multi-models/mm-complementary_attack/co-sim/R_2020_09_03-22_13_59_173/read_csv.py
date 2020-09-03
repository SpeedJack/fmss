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
        x.append(float(row[7]))
        y.append(float(row[8]))
data = {titles[7]:x,titles[8]:y}
plt.figure()
plt.scatter(data[titles[7]],data[titles[8]])
plt.xlabel(titles[7])
plt.ylabel(titles[8])
plt.show()
