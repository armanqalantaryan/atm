
sources := $(wildcard *.cpp)
objects := $(patsubst %.cpp, $(obj)/client/%.o, $(sources))
depends := $(patsubst %.cpp, $(obj)/client/%.dep, $(sources))

$(bin)/client : $(objects)  
	@$(ld) $^ -g -o $@ 
	@ echo Linking ...

$(obj)/client/%.o : $(src)/client/%.cpp
	@$(cc) -c  $< -o $@  
	@ echo make object file ...

$(obj)/client/%.dep : $(src)/client/%.cpp
	$(cc) -MM $< -MT "$@ $(patsubst %.dep, %.o, $@)" -o $@
	@ echo make dipendence file ...

-include $(depends)

