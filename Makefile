object := build/Agenda.o build/Date.o build/Meeting.o build/Storage.o\
	build/User.o build/AgendaUI.o build/AgendaService.o
FLAGS := -std=c++11 -w
INCLUDE := -I./include
bin/Agenda: $(object)
	g++ $(FLAGS) $(INCLUDE) $(object) -o bin/Agenda

build/Agenda.o: src/Agenda.cpp include/AgendaUI.hpp
	g++ $(FLAGS) $(INCLUDE) -c src/Agenda.cpp -o $@

build/Date.o: include/Date.hpp src/Date.cpp
	g++ $(FLAGS) $(INCLUDE) -c src/Date.cpp -o $@

build/Meeting.o: include/Meeting.hpp src/Meeting.cpp include/Date.hpp
	g++ $(FLAGS) $(INCLUDE) -c src/Meeting.cpp -o $@

build/Storage.o: include/Storage.hpp src/Storage.cpp\
	include/Meeting.hpp include/User.hpp
	g++ $(FLAGS) $(INCLUDE) -c src/Storage.cpp -o $@

build/User.o: include/User.hpp src/User.cpp
	g++ $(FLAGS) $(INCLUDE) -c src/User.cpp -o $@

build/AgendaUI.o: include/AgendaUI.hpp src/AgendaUI.cpp\
	include/AgendaService.hpp
	g++ $(FLAGS) $(INCLUDE) -c src/AgendaUI.cpp -o $@

build/AgendaService.o: include/AgendaService.hpp src/AgendaService.cpp\
	include/Storage.hpp
	g++ $(FLAGS) $(INCLUDE) -c src/AgendaService.cpp -o $@

.PHONY: clean
clean:
	@rm -rf build/*.o
	@rm -rf bin/Agenda
