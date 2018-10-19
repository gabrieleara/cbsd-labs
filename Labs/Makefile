TOPTARGETS := all clean

SUBDIRS := $(shell find */. -maxdepth 0 | sed 's/ /\\ /g')

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	($(MAKE) -C "$@" $(MAKECMDGOALS)) || true

.PHONY: $(TOPTARGETS) $(SUBDIRS)
