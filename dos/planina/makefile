CFLAGS = -zW -oaxt -d1 -w4
CC = wcc386p
NAME = planina
LNK = $(name).lnk
OBJS = $(name).obj
$(name).exe : $(OBJS) $(name).res $(LNK)
		wlink @$(LNK)
		wbind $(name) -R $(name).res
$(name).res : $(name).rc $(name).ico
		rc -r $(name).rc
$(LNK) : makefile ..\build.mif
		%create $(LNK)
		@%append $(LNK) debug all
		@%append $(LNK) sys win386
		@%append $(LNK) option mindata=100K
		@%append $(LNK) option maxdata=100K
		@%append $(LNK) option stack=7k
		@%append $(LNK) name $(name)
		@for %i in ($(OBJS)) do @%append $(LNK) file %i
$(name).obj : $(name).c $(name).h
	$(CC) $(CFLAGS) $[*
