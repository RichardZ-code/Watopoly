CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
OBJECTS = academic.o building.o coopfee.o dctimsline.o dice.o goosenesting.o gototims.o gym.o main.o needleshall.o nonproperty.o osap.o player.o property.o residence.o slc.o tuition.o Watopoly.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = watopoly

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
