SRC = src/rgapi.cpp
OBJ = $(SRC:.cpp=.o)

TESTSRC = test-src/main.cpp
TESTOBJ = $(SRC:.cpp=.o)

#de compiler die gebruikt moet worden
CC = g++

#de bestanden van de librarys die geinclude moeten worden
INCLUDE_PATHS = -Iinclude
#de locar=tie van de library bestanden
LIBRARY_PATHS = -Llib

#flags die de compiler gebruikt (kan bijv. optimalisatie met -O2)
COMPILER_FLAGS = -std=c++20 -static-libstdc++ -static-libgcc -O2 -pthread

#de library bestanden die gebruikt moeten worden 
LINKER_FLAGS = -lrgapi -lcurl

#linker flags voor de library
LIB_LINKER = -lcurl

#de locatie van het output bestand
TEST_NAME = build/api-test

#de locatie van de library
LIB_NAME = build/ricardogames-api

all:${OBJ}
	ar crf lib/librgapi.a ${OBJ}
	${CC} ${OBJ} ${COMPILER_FLAGS} ${INCLUDE_PATHS} ${LIBRARY_PATHS} ${LIB_LINKER} -shared -o ${LIB_NAME}.dll
	$(CC) $(TESTSRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(TEST_NAME)

lib:${OBJ}
	ar crf lib/librgapi.a ${OBJ}
	${CC} ${OBJ} ${COMPILER_FLAGS} ${INCLUDE_PATHS} ${LIBRARY_PATHS} ${LIB_LINKER} -shared -o ${LIB_NAME}.dll

test : $(TESTSRC)
	$(CC) $(TESTSRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(TEST_NAME)

.cpp.o:
	${CC} ${COMPILER_FLAGS} ${INCLUDE_PATHS} -c $*.cpp -o $@

clean:
	-rm -f src/*.o test-src/*.o

linux:
	make -f makefile.linux