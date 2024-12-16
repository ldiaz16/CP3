COURSE = cs310
SEMESTER = fall2024
CP_NUMBER = 3
LASTNAME = Diaz
GITUSERID = ldiaz16
USER = ldiaz16
REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = ../CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET = firell_test
SRCS = driver.cpp Voter.cpp
OBJS = $(SRCS:.cpp = .o)

firell_test : driver.cpp FireLL.h Voter.cpp
	$(CXX) $(CXXFLAGS) -o firell_test driver.cpp Voter.cpp

clean:
	rm -f firell_test

run: firell_test
	./firell_test

valgrind: firell_test
	valgrind --leak-check=full --track-origins=yes ./firell_test

tar: clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)
	@echo "Tarred and gzipped file is in the directory one level up"
	@echo $(TARFILE)".gz"

.PHONY: clean run valgrind