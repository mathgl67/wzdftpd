DATE_TAG:=$(shell date +"%Y%m%d")

SUBDIRS = src backends modules tools

debug:
	make recursive 'RECURSIVE_TARGET=debug'

all:
	make recursive 'RECURSIVE_TARGET=all'

release:
	make recursive 'RECURSIVE_TARGET=release'

clean:
	make recursive 'RECURSIVE_TARGET=clean'

distclean:
	make recursive 'RECURSIVE_TARGET=distclean'

deps:
	(cd src && make deps) || exit 1

check_symlinks:
	(cd src && make check_symlinks) || exit 1

recursive:
	@CWD=`pwd`; \
	for i in $(SUBDIRS); do \
		(cd $$CWD/$$i && $(MAKE) $(RECURSIVE_TARGET)) || exit 1; \
	done

tarball: distclean
	cd .. && tar czf wzd-$(DATE_TAG).tgz wzdFTPd