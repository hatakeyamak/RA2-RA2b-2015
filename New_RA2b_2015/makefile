DIR = $(shell pwd)

CXX           = g++
CCFLAGS       = $(shell root-config --cflags) -I$(DIR) -std=c++0x
CXXFLAGS      = $(shell root-config --cflags) -I$(DIR)  
LDFLAGS       = 
LD            = g++

LIBS          = $(shell root-config --glibs)   

OBJS          = main.o $(DIR)/Events.o Selection.o
PROGRAM       = run

OBJS2	      = tauhad_template.o Events.o Selection.o utils.o
PROGRAM2      = run_tauHad

OBJS3         = lostLepton.o Events.o Selection.o utils.o 
PROGRAM3      = run_lostlepton

OBJS4         = tauhad_template2.o Events.o Selection.o utils.o
PROGRAM4      = run_tauHad2


HEADERS       = $(DIR)/Events.h Selection.h utils.h utils2.h Lepton_Selection.h LeptonEfficiency.h LeptonAcceptance.h HistReader.h

%.o : %.C $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

%.o : %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CCFLAGS) -c $<

#%.o : %.cc $(HEADERS)
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

%.o : %.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

all : $(PROGRAM) $(PROGRAM 2)

.PHONY : all 

$(PROGRAM): $(OBJS)
	@echo "Linking $(PROGRAM) ..."
	@$(LD) $(OBJS) $(LIBS) -o $(PROGRAM)
	@echo "done"

$(PROGRAM2): $(OBJS2)
	@echo "Linking $(PROGRAM2) ..."
	@$(LD) $(OBJS2) $(LIBS) -o $(PROGRAM2)
	@echo "done"

$(PROGRAM3): $(OBJS3)
	@echo "Linking $(PROGRAM3) ..."
	@$(LD) $(OBJS3) $(LIBS) -o $(PROGRAM3)
	@echo "done"

$(PROGRAM4): $(OBJS4)
	@echo "Linking $(PROGRAM4) ..."
	@$(LD) $(OBJS4) $(LIBS) -o $(PROGRAM4)
	@echo "done"

