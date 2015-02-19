DIR = $(shell pwd)

#CXX           = ~/.vim/bundle/ClangComplete/bin/cc_args.py g++
CXX           = g++
#CXXFLAGS      = -Wno-deprecated $(shell root-config --cflags) -I../$(DEL)/external/ -I../$(DEL) -std=c++0x 
CCFLAGS       = $(shell root-config --cflags) -std=c++0x
CXXFLAGS      = $(shell root-config --cflags) 
LDFLAGS       = 
LD            = g++

LIBS = $(shell root-config --glibs)

OBJS          = lostLepton.o
OBJS2          = lostLepton2.o
PROGRAM       = run
PROGRAM2       = run2

HEADERS       = interface/utils.h interface/Selection.h interface/HistReader.h  interface/LeptonAcceptance.h  interface/LeptonEfficiency.h interface/utils2.h

%.o : %.C $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

%.o : %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CCFLAGS) -c $<

%.o : %.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<


all : $(PROGRAM) $(PROGRAM2)

.PHONY : all

$(PROGRAM): $(OBJS)
	@echo "Linking $(PROGRAM) ..."
	@$(LD) $(OBJS) $(LIBS) -o $(PROGRAM)
	@echo "done"

$(PROGRAM2): $(OBJS2)
	@echo "Linking $(PROGRAM2) ..."
	@$(LD) $(OBJS2) $(LIBS) -o $(PROGRAM2)
	@echo "done"
