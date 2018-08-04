DIR = source

.PHONY: all debug clean $(DIR)

all: $(DIR)

debug: MTARGET = debug
debug: $(DIR)

clean: MTARGET = clean
clean: $(DIR)

$(DIR):
	$(MAKE) -C $@ $(MFLAGS) $(MTARGET)
