.PHONY:	all clean

MAKE	= make    
DIRS	= $(shell ls -1d */)

all :
	for dir in $(DIRS) ; do \
		$(MAKE) -C $$dir all ; \
		$(MAKE) -C $$dir ALL ; \
	done

clean:
	for dir in $(DIRS) ; do \
		$(MAKE) -C $$dir clean ; \
	done

