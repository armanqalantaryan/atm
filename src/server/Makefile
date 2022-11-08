
sources := $(wildcard *.cpp)
objects := $(patsubst %.cpp, $(obj)/server/%.o, $(sources))
depends := $(patsubst %.cpp, $(obj)/server/%.dep, $(sources))

$(bin)/server : $(objects)
	@$(ld) $^ -g -o $@ -lsqlite3
	@ echo Linking ...

$(obj)/server/%.o : $(src)/server/%.cpp
	@$(cc) -c  $< -o $@
	@ echo make object file ...

$(obj)/server/%.dep : $(src)/server/%.cpp
	$(cc) -MM $< -MT "$@ $(patsubst %.dep, %.o, $@)" -o $@
	@ echo make dipendence file ...

-include $(depends)
