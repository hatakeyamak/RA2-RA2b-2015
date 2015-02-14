DIR = $(shell pwd)

CXX           = g++
CCFLAGS       = $(shell root-config --cflags) -I$(DIR) -std=c++0x
CXXFLAGS      = $(shell root-config --cflags) -I$(DIR)  
LDFLAGS       = 
LD            = g++

LIBS          = $(shell root-config --glibs) -I$(DIR) 

OBJS          = lostlepEff.o $(DIR)/Events.o
PROGRAM       = run
HEADERS       = $(DIR)/Events.h 

%.o : %.C $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

%.o : %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CCFLAGS) -c $<

%.o : %.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

$(PROGRAM): $(OBJS)
	@echo "Linking $(PROGRAM) ..."
	@$(LD) $(OBJS) $(LIBS) -o $(PROGRAM)
	@echo "done"

