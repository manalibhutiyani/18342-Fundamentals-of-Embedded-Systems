PROGS_PROG1_OBJS := prog1.o
PROGS_PROG1_OBJS := $(PROGS_PROG1_OBJS:%=$(TDIR)/prog1/%)
ALL_OBJS += $(PROGS_PROG1_OBJS)

$(TDIR)/bin/prog1 : $(TSTART) $(PROGS_PROG1_OBJS) $(TLIBC)
