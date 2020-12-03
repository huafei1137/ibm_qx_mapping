import sys
import os
import re

resultsDir = "./results";
outputFile = "results.csv";

outfile = open(outputFile, "w");
outfile.write("Benchmark,Critical Cycles,Parallel Cycles,Max CNOTS\n");

for filename in os.listdir(resultsDir):
	benchmark = filename.replace(".qasm.txt", ".qasm");
	critical = "";
	parallel = "";
        heuristic ="";
	cnots = "";	
	
	resfile = open(resultsDir + "/" + filename, "r");
	for line in resfile:
		line = line.rstrip();#remove newline
		if("number of CNOT" in line):
			numbers = re.findall(r'\d+', line)
			cnots = numbers[0];
		elif("CriticalCycles" in line):
			numbers = re.findall(r'\d+', line)
			critical = numbers[0];
			parallel = numbers[1];
	resfile.close();
	outfile.write(benchmark + ",");
	outfile.write(critical + ",");
	outfile.write(parallel + ",");
	outfile.write(cnots + "\n");

outfile.close();
