include settings.mk

all:
	cd gpio && $(MAKE)
	cd memory && $(MAKE)

lib:
	echo $(MAKEFLAGS)
	echo $(blob)

ab:
	echo "ab"

clean:
	rm -rf ./build
