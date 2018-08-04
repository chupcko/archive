DIRS =           \
	library  \
	programs \

.DEFAULT_GOAL := all
.PHONY: all
all: $(DIRS)

.PHONY: debug
debug: MTARGET = debug
debug: $(DIRS)

.PHONY: clean
clean: MTARGET = clean
clean: $(DIRS)

.PHONY: $(DIRS)
$(DIRS):
	$(MAKE) -C $@ $(MFLAGS) $(MTARGET)
