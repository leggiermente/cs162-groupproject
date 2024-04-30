import csv
import random

# Read the CSV file
with open('22CLC01.csv', 'r') as csv_file:
    csv_reader = csv.reader(csv_file)
    data = [row for row in csv_reader]

# Generate random scores
score_data = [[row[1], random.randint(1, 10), random.randint(1, 10), random.randint(1, 10), random.randint(1, 10)] for row in data]

# Write the results to a new CSV file
with open('score1.csv', 'w', newline='') as csv_file:
    csv_writer = csv.writer(csv_file)
    csv_writer.writerows(score_data)