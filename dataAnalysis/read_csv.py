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
        x.append(float(row[5]))
        y.append(float(row[6]))
data = {titles[5]:x,titles[6]:y}
plt.figure()
plt.scatter(data[titles[5]],data[titles[6]])
plt.xlabel(titles[5])
plt.ylabel(titles[6])
plt.show()
