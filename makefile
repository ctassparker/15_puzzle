ida: main.o output.o helpers.o heuristic.o initialise.o idafuncs.o
	@echo "\x1b[36m"Building IDA executable... "\x1b[0m"
	gcc -o ida main.o output.o helpers.o heuristic.o initialise.o idafuncs.o 
	@echo "\x1b[36m"IDA build complete "\x1b[0m"

wida: main.o output.o helpers.o w_heuristic.o initialise.o idafuncs.o
	@echo "\x1b[36m"Building WIDA executable... "\x1b[0m"
	gcc -o wida main.o output.o helpers.o w_heuristic.o initialise.o idafuncs.o 
	@echo "\x1b[36m"WIDA build complete "\x1b[0m"

output.o: output.c
	gcc -c -Wall output.c

helpers.o: helpers.c
	gcc -c -Wall helpers.c

heuristic.o: heuristic.c
	gcc -c -Wall heuristic.c

w_heuristic.o: w_heuristic.c
	gcc -c -Wall w_heuristic.c

initialise.o: initialise.c
	gcc -c -Wall initialise.c

idafuncs.o: idafuncs.c
	gcc -c -Wall idafuncs.c 

main.o: main.c main.h
	gcc -c -Wall main.c

# Chris Tass-Parker
#   
#
# Marker note: making 
# ida will use heursitic.c and 
# wida will use w_heuristic.c 
# all other components remain identical. 