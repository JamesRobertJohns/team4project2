import sys
import random

random.seed(42)
NUM_EDGES = 250
MAX_VERTEX = 1000
INTERVAL = 100
START_VERTEX = 100
MAX_WEIGHT = 1000

file_index = 1
V = START_VERTEX
while (V <= MAX_VERTEX):
    try:
        file = open("fixed_edges_%i.txt" % file_index, 'w')
    except OSError:
        print("[-] Error in writing file 'fixed_edges_%i.txt'" % file_index)
        sys.exit()

    file.write(str(V)) 
    file.write("\n")
    for i in range(NUM_EDGES):
        source =  str(random.randint(0, V-1))
        destination = str(random.randint(0, V-1))
        weight = str(random.randint(1, MAX_WEIGHT))
        while source == destination:
            destination = str(random.randint(0, V-1))
        msg = source + " " + destination + " " + weight + "\n"
        file.write(msg)
    file.close()
    V += INTERVAL
    msg = "[+] fixed_edges_{0}.txt generated."  
    print(msg.format(file_index)) 
    file_index += 1
