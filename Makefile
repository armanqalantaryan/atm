
export ld := g++
export cc := g++
export base := $(PWD)
export bin := $(base)/bin
export obj := $(base)/obj
export src := $(base)/src

all : client server

client:
	@ mkdir -p $(bin) $(obj) $(obj)/client
	@ $(MAKE) -C $(src)/client

server:
	@ mkdir -p $(bin) $(obj) $(obj)/server
	@ $(MAKE) -C $(src)/server

.PHONY : all

.PHONY : clean
clean :
	@rm $(obj) $(bin) inc -rf
	@echo Cleaning...
