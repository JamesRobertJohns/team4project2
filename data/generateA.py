import sys
import random

random.seed(42)
NUM_VERTEX = 250
MAX_EDGES = 500
INTERVAL = 100
START_EDGES = 100
MAX_WEIGHT = 1000

file_index = 1
E = START_EDGES
while (E <= MAX_EDGES):
    try:
        file = open("fixed_vertex_%i.txt" % file_index, 'w')
    except OSError:
        print("[-] Error in writing file 'fixed_vertex_%i.txt'" % file_index)
        sys.exit()

    file.write(str(NUM_VERTEX)) 
    file.write("\n")
    for i in range(E):
        source =  str(random.randint(0, NUM_VERTEX-1))
        destination = str(random.randint(0, NUM_VERTEX-1))
        weight = str(random.randint(1, MAX_WEIGHT))
        while source == destination:
            destination = str(random.randint(0, NUM_VERTEX - 1))
        msg = source + " " + destination + " " + weight + "\n"
        file.write(msg)
    file.close()
    E += INTERVAL
    msg = "[+] fixed_vertex_{0}.txt generated."  
    print(msg.format(file_index)) 
    file_index += 1
