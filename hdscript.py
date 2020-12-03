import sys
import os
import re

resultsDir = "./method2results"
outputFile = "newresults2.csv"

outfile = open(outputFile, "w");
outfile.write("Benchmark,Critical Cycles,Parallel Cycles,Heuristic Cycles,overlap cycles,Max CNOTS\n")

for filename in os.listdir(resultsDir):
    benchmark = filename.replace(".qasm.txt",".qasm");
    critical = "";
    parallel = "";
    heuristic = "";
    overlap = "";
    cnots = "";
    resfile = open(resultsDir + "/" + filename,"r");
    for line in resfile:
        line = line.rstrip();
        if("number of CNOT" in line):
            numbers = re.findall(r'\d+',line)
            cnots= numbers[0];
        elif("CriticalCycles" in line):
            numbers = re.findall(r'\d+', line)
            critical = numbers[0];
            parallel = numbers[1];
        elif("Heur" in line):
            numbers = re.findall(r'\d+',line)
            heuristic = numbers[0];
        elif("over" in line):
            numbers = re.findall(r'\d+',line)
            overlap = numbers[0];
    resfile.close();
    outfile.write(benchmark+",");
    outfile.write(critical + ",");
    outfile.write(parallel+",");
    outfile.write(heuristic+",");
    outfile.write(overlap+",")
    outfile.write(cnots+"\n");
outfile.close();
