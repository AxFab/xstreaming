# Makefile

# S E T T I N G S -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
topdir = .
gendir = .
srcdir = $(topdir)/src
outdir = $(gendir)/obj
libdir = $(gendir)/lib
bindir = $(gendir)/bin
prefix = ./usr/local

ARCH = x86
NAME = xstreaming
# Hard-coded version
MAJOR_VERSION := 0
MINOR_VERSION := 1
SUBLEVEL_VERS := 1

VERSION := $(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL_VERS)


S = @
V = @
Q = @ echo


# Most people will set this stuff on the command line, i.e.
#        make CROSS_COMPILE=arm-linux-
# will build for 'arm'.
# CROSS is still supported for backward compatibily only
CROSS_COMPILE ?= $(CROSS)
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)g++
NM = $(CROSS_COMPILE)nm
ASM = nasm -f elf32

INSTALL = install

CFLAGS = -Wall -Wextra -pedantic -I include -I src -ggdb3 -Dnkit=xstm -Wno-unused-parameter
CXFLAGS = $(CFLAGS)
LDFLAGS = 




# Auto listing of deliveries
DV_LIBS  = libxstm
DV_UTILS = main

define objs
  $(patsubst $(srcdir)/%.c,$(outdir)/%.o,    \
  $(patsubst $(srcdir)/%.cpp,$(outdir)/%.o,  \
  $(patsubst $(srcdir)/%.asm,$(outdir)/%.o,  \
  $(1)                                       \
  )))
endef

define dlvs
  $(patsubst %.c,$(libdir)/%.so, $(DV_LIBS))   \
  $(patsubst %.c,$(libdir)/%.a, $(DV_LIBS))    \
  $(patsubst %.c,$(bindir)/%, $(DV_UTILS))    \
  $(patsubst %.c,$(libdir)/crts/%.a, $(DV_CRTS))
endef


# C O M M O N   T A R G E T S -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
all: runtime libs utils

runtime: $(DV_CRTS)

libs: $(DV_LIBS)

utils: $(DV_UTILS)

install: install_dev install_runtime install_utils

unistall:
# TODO -- rm $(prefix)/XX (without messing with others libs)

clean: 
	$(V) rm -rf $(outdir)

distclean: clean
	$(V) rm -rf $(libdir)
	$(V) rm -rf $(bindir)

config:
# TODO -- Create/update configuration headers

check:
# TODO -- Launch unit tests

.PHONY: all runtime libs utils install unistall clean distclean config check

# I N S T A L L A T I O N -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

install_dev: install_headers install_libs

install_runtime: $(patsubst %,$(prefix)/lib/crts/%.o,$(DV_CRTS))

install_libs: $(patsubst %,$(prefix)/lib/%.so,$(DV_LIBS))

install_utils: $(patsubst %,$(prefix)/bin/%,$(DV_UTILS))

install_headers: $(prefix)/include

$(prefix)/lib/crts/%.o: $(libdir)/crts/%.o
	$(Q) "  CP    $@"
	$(S) mkdir -p $(dir $@)
	$(V) cp $< $@

$(prefix)/lib/lib%.so: $(libdir)/lib%.so
	$(Q) "  INST. $@"
	$(S) mkdir -p $(dir $@)
	$(V) $(INSTALL) $< $@

$(prefix)/bin/%: $(bindir)/%
	$(Q) "  INST. $@"
	$(S) mkdir -p $(dir $@)
	$(V) $(INSTALL) $< $@

$(prefix)/include: $(topdir)/include
	$(Q) "  INST. $@"
	$(S) mkdir -p $(dir $@)
	$(V) cp -r $< $@

# S O U R C E S   C O M P I L A T I O N -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
$(outdir)/%.o: $(srcdir)/%.asm
	$(Q) "  ASM   $@"
	$(S) mkdir -p $(dir $@)
	$(V) $(ASM) -o $@ $<

$(outdir)/%.o: $(srcdir)/%.c
	$(Q) "  CC    $@"
	$(S) mkdir -p $(dir $@)
	$(V) $(CC) -c -o $@ $< $(CFLAGS)

$(outdir)/%.o: $(srcdir)/%.cpp
	$(Q) "  CXX   $@"
	$(S) mkdir -p $(dir $@)
	$(V) $(CXX) -c -o $@ $< $(CXFLAGS)


# P A C K A G I N G -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
release: $(gendir)/$(NAME)-$(ARCH)-$(VERSION).tar.bz2

$(gendir)/$(NAME)-$(ARCH)-$(VERSION).tar.bz2: $(call dlvs)
	$(Q)  "  TAR   $@"
	$(V) tar cjf $@  -C $(topdir) $(topdir)/include -C $(gendir) $^


# L I S T   S O U R C E S   F I L E S -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
wild_libxstm  = $(wildcard $(srcdir)/core/*.cpp) \
							  $(wildcard $(srcdir)/dom/*.cpp) \
							  $(wildcard $(srcdir)/stream/*.cpp) 


wild_main = $(wildcard $(srcdir)/*/*.cpp)


# D E L I V E R I E S -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
define CRT
$1:$(libdir)/crts/$1.a
$(libdir)/crts/$1.a: $(call objs, $(filter-out $(omit_$1-y),$(wild_$1)))
	$(Q) "  AR    $$@"
	$(S) mkdir -p $$(dir $$@)
	$(V) $(AR) rc $$@ $$^
endef

define UTILS
$1:$(bindir)/$1
$(bindir)/$1: $(call objs, $(filter-out $(omit_$1-y),$(wild_$1)))
	$(Q) "  LD    $$@ "
	$(S) mkdir -p $$(dir $$@)
	$(V) $(LD) $(LDFLAGS) -o $$@ $$^ $(lflgs_$1)
endef

define SHARED
$1: spInclude = $2
$1: spDefine = $3
$1:$(libdir)/$1.so
$(libdir)/$1.so: $(call objs, $(filter-out $(omit_$1-y),$(wild_$1)))
	$(Q) "  LD    $$@"
	$(S) mkdir -p $$(dir $$@)
	$(V) $(LD) -shared $(LDFLAGS) -o $$@ $$^ $(lflgs_$1)
endef

define STATIC
s$1: $(libdir)/$1.a
$(libdir)/$1.a: $(call objs, $(srcs_$1))
endef

$(libdir)%.a:
	$(Q) "  AR    $@"
	$(S) mkdir -p $(dir $@)
	$(V) $(AR) rc $@ $^


$(foreach d,$(DV_LIBS),$(eval $(call SHARED,$d)))
$(foreach d,$(DV_UTILS),$(eval $(call UTILS,$d)))
$(foreach d,$(DV_CRTS),$(eval $(call CRT,$d)))

# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

