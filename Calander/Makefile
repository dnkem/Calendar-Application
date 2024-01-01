all:	main.o Date.o Event.o PlannerDate.o Planner.o
	g++ -o a1 main.o Date.o Event.o PlannerDate.o Planner.o

main.o:	main.cc Tester.h Date.h Event.h PlannerDate.h Planner.h
	g++ -c main.cc

Date.o:	Date.cc Date.h defs.h
	g++ -c Date.cc

Event.o:	Event.cc Event.h 
	g++ -c Event.cc

PlannerDate.o: PlannerDate.cc PlannerDate.h
	g++ -c PlannerDate.cc

Planner.o: Planner.cc Planner.h
	g++ -c Planner.cc

clean:
	rm -f *.o a1