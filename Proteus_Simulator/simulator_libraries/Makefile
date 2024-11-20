CC = g++
CPPFLAGS = -MMD -MP -Os -DOBJC_OLD_DISPATCH_PROTOTYPES -g
IGNORED_WARNINGS = -w
INC_DIRS = -I. -I..
#if new libraries are added, add them here
OBJS = FEHLCD.o FEHRandom.o FEHSD.o tigr.o FEHUtility.o FEHImages.o

ifeq ($(OS),Windows_NT)
	LDFLAGS = -lopengl32 -lgdi32
	EXEC = game.exe
else
	UNAME := $(shell uname)
	ifeq ($(UNAME),Darwin)
		LDFLAGS = -framework OpenGL -framework Cocoa
	else
		LDFLAGS = `pkg-config --libs --cflags opengl x11 glx`
	endif
	EXEC = game.out
endif

# This is a recursive implementation of the wildcard function provided by gnu.
# We use it to allow students to have an arbitrary source file structure, with multiple source files and folders
# https://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make/18258352#18258352
recursiveWildcard=$(foreach d,$(wildcard $(1:=/*)),$(call recursiveWildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Gets all of the source files (.cpp) in the parent directory and its children folders, 
# excluding the files we have in here, as those get built in the libraries target.
STUDENT_CPP_FILES := $(filter-out ../simulator_libraries/%, $(call recursiveWildcard, .., *.cpp))

# When we compile student .cpp files in the studentFiles target, the .o object files are placed in this directory.
# So this list, used in linking in the all target below, replaces the .cpp extension from the source files, and then strips the 
# directory information (since the object files are all built into this directory)
STUDENT_COMPILED_OBJECT_FILES := $(notdir $(patsubst %.cpp, %.o,$(STUDENT_CPP_FILES)))

all: libraries studentFiles
	$(CC) $(CPPFLAGS) $(OBJS) $(STUDENT_COMPILED_OBJECT_FILES) -o ../$(EXEC) $(LDFLAGS) $(IGNORED_WARNINGS)

studentFiles: $(STUDENT_CPP_FILES)
	$(CC) $(IGNORED_WARNINGS) $(INC_DIRS) -c $^ 

libraries: ${OBJS}

FEHLCD.o: FEHLCD.cpp FEHLCD.h FEHUtility.o
	$(CC) $(IGNORED_WARNINGS) $(INC_DIRS) -c FEHLCD.cpp

FEHUtility.o: FEHUtility.cpp FEHUtility.h
	$(CC) $(IGNORED_WARNINGS) $(INC_DIRS) -c FEHUtility.cpp

FEHRandom.o: FEHRandom.cpp FEHRandom.h
	$(CC) $(IGNORED_WARNINGS) $(INC_DIRS) -c FEHRandom.cpp

FEHSD.o: FEHSD.cpp FEHSD.h
	$(CC) $(IGNORED_WARNINGS) $(INC_DIRS) -c FEHSD.cpp

FEHImages.o: FEHImages.cpp FEHImages.h
	$(CC) $(IGNORED_WARNINGS) $(INC_DIRS) -c FEHImages.cpp

tigr.o: tigr.c tigr.h
	$(CC) $(IGNORED_WARNINGS) $(INC_DIRS) -c tigr.c

clean:
	@rm -f *.o ../$(EXEC)
