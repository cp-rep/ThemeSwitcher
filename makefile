BINDIR=./bin
SRCDIR=./src
BUILDDIR=./build
MKDIR_P=mkdir -p
GTESTDIR=./gtest
LOGDIR=./log
LDIR=./lib
ODIR=obj
CC=g++
CPPFLAGS=-I$(IDIR)
LIBS=-lm
BINNAME=themeswitcher
_DEPS = log.hpp cursesFunctions.hpp cursesWindow.hpp _cursesWinConsts.hpp\
typeConversions.hpp testingInterface.hpp fileOperations.hpp programStates.hpp\
ncursesTextEditor.hpp
_OBJ = main.o log.o cursesFunctions.o cursesWindow.o typeConversions.o\
testingInterface.o fileOperations.o programStates.o ncursesTextEditor.o

DEPS = $(patsubst %,$(LDIR)/%,$(_DEPS))

OBJ = $(patsubst %,$(SRCDIR)/$(ODIR)/%,$(_OBJ))

$(SRCDIR)/$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< -I$(LDIR)

$(BINDIR)/$(BINNAME): $(OBJ)
	$(CC) -std=c++98 -Wall -Wextra -o $@ $^ -l ncurses -I$(LDIR) $(LIBS)

.PHONY: clean dirs

clean:
	rm -f $(SRCDIR)/$(ODIR)/*.o
	rm -f $(SRCDIR)/$(ODIR)/*~
	rm -f $(SRCDIR)/*~
	rm -f $(LDIR)/*~
	rm -f $(OPDIR)/*~
	rm -rf $(BINDIR)/themeswitcher
	rm -rf $(BUILDDIR)/
	rm -rf $(GTESTDIR)/*~
	rm -rf $(LOGDIR)/*.log
	rm -f ./*~

dirs: ${BINDIR} ${LOGDIR} ${SRCDIR}/${ODIR}

${BINDIR}:
	${MKDIR_P} ${BINDIR}

${LOGDIR}:
	${MKDIR_P} ${LOGDIR}

${SRCDIR}/${ODIR}:
	${MKDIR_P} ${SRCDIR}/${ODIR}
