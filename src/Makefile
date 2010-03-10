# =============================================================================
# ======================      Project Specific Setup      =====================
# =============================================================================

PROJECT     := a.out
SUBDIRS     ?=
LIBS        ?=

TESTER      := rtests

TRASH       ?=

# =============================================================================
# =====================      Source Control Variables      ====================
# =============================================================================

gitm := .
GIT_REMOTE_URL :=
SYNC_REMOTE_PATH :=
SYNC_REMOTE_USER :=
SYNC_REMOTE_HOST :=

# =============================================================================
# ========================      Debug & Test Setup      =======================
# =============================================================================

ifneq ($(strip $(wildcard .debug)),)
DEBUG := -D__DEBUG__
else
DEBUG :=
endif

# =============================================================================
# =====================      Machine Dependent Setup      =====================
# =============================================================================

OSTYPE := $(shell uname)

ifeq ($(OSTYPE),Linux)
ARCH   := -D_LINUX_
ENDIAN := -D_LITTLE_ENDIAN_
endif

ifeq ($(OSTYPE),Darwin)
ARCH   := -D_DARWIN_
ENDIAN := -D_LITTLE_ENDIAN_
endif

ifeq ($(OSTYPE),SunOS)
ARCH   := -D_SOLARIS_
ENDIAN := -D_BIG_ENDIAN_
endif

# =============================================================================
# =====================      Compiler & Linker Setup      =====================
# =============================================================================
CPPFLAGS ?=
LDFLAGS ?=
.IGNORE ?=

ifneq ($(DEBUG),)
CXXFLAGS := -g -Wall $(ARCH) $(DEBUG)
else
CXXFLAGS := -O2
endif
# -gfull

CXX := g++
EXT := cpp

# =============================================================================
# ===================      Project Specific Build Setup      ==================
# =============================================================================
.DEFAULT_GOAL := all
SUBDIR_EXT    := submake

MK_EXT := $(wildcard *.make)
ifneq ($(MK_EXT),)
$(info -- including extension makefiles: $(MK_EXT))
include $(MK_EXT)
endif

SUB_MK   := $(foreach subdir,$(SUBDIRS),$(wildcard $(subdir)/*.$(SUBDIR_EXT)))
ifneq ($(SUB_MK),)
$(info -- including subdirectory makefiles ($(PROJECT)): $(SUB_MK))
include $(SUB_MK)
endif

# =============================================================================
# ======================      Source & Header Setup      ======================
# =============================================================================

SRCS += $(wildcard *.$(EXT))
OBJS += $(patsubst %.$(EXT),%.o,$(SRCS))
DEPS := $(patsubst %.$(EXT),%.d,$(SRCS))

EXTERNAL_OBJS ?=

TEST_SRCS ?=
TEST_OBJS += $(patsubst %.$(EXT),%.o,$(TEST_SRCS))
TEST_DEPS := $(patsubst %.$(EXT),%.d,$(TEST_SRCS))

# =============================================================================
# =======================      Generic Build Setup      =======================
# =============================================================================
.PHONY: all run test nolink

all: $(PROJECT)

test: $(TESTER)

$(OBJS): $(EXTERNAL_OBJS)
$(OBJS): %.o: %.$(EXT)
	@$(CXX) $(CPPFLAGS) -MM -MP -MF $(basename $<).d -MT $(basename $<).o $<
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(PROJECT): $(OBJS) | .gitignore
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(PROJECT) $(OBJS) $(EXTERNAL_OBJS) $(LIBS)


$(TEST_OBJS): %.o: %.$(EXT)
	@$(CXX) $(CPPFLAGS) -MM -MP -MF $(basename $<).d -MT $(basename $<).o $<
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(TESTER): $(OBJS) $(TEST_OBJS) | .gitignore
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TESTER) $(OBJS) $(EXTERNAL_OBJS) $(TEST_OBJS) $(LIBS)

nolink: $(OBJS) $(EXTERNAL_OBJS) | .gitignore

# =============================================================================
# =========================      Dependency Setup      ========================
# =============================================================================
# http://bit.ly/42KS62

include $(wildcard $(DEPS))
include $(wildcard $(TEST_DEPS))

# Alternatives (instead of dependency generation in rule for $(OBJS)):

# $(DEPS): %.d: %.$(EXT)
# 	$(CXX) $(CPPFLAGS) -MM -MP -MF $@ -MT $(basename $<).o $<
# include $(wildcard $(DEPS))

# $(DEPS): %.d: %.$(EXT)
# 	@set -e; rm -f $@; \
# 	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
# 	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
# 	rm -f $@.$$$$
# include $(wildcard $(DEPS))

# .%.d: %.$(_EXT)
# 	@set -e; rm -f $@; \
# 	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
# 	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
# 	rm -f $@.$$$$
# include $(patsubst %.$(_EXT),.%.d,$(SRCS))

# =============================================================================
# ==========================      Source Control      =========================
# =============================================================================
.PHONY: git-init commit push pull sync

# todo: put in some script
.gitignore:
	@echo $(PROJECT)   >  $@
	@echo 'sync.make'  >> $@
	@echo 'xcode/'     >> $@
	@echo '.DS_Store'  >> $@
	@echo '*.REMOTE'   >> $@
	@echo '*.LOCAL'    >> $@
	@echo '*.bak'      >> $@
	@echo '*.obj'      >> $@
	@echo '*.pbd'      >> $@
	@echo '*.cd'       >> $@
	@echo '*.orig'     >> $@
	@echo '*.sln'      >> $@
	@echo '*.suo'      >> $@
	@echo '*.o'        >> $@
	@echo '*.d'        >> $@
	@echo '*.d.*'      >> $@
	@echo '.*.d'       >> $@
	@echo '.*.d.*'     >> $@
	@echo '*.a'        >> $@
	@echo '*.so'       >> $@
	@echo '*~'         >> $@
	@echo '._*'        >> $@

git-init: .gitignore
	git init ..
	git config receive.denyCurrentBranch refuse
	git config push.default matching
	$(MAKE) commit
ifneq ($(GIT_REMOTE_URL),)
	-git remote add origin $(GIT_REMOTE_URL)
	git config remote.origin.url $(GIT_REMOTE_URL)
	git config branch.master.remote origin
	git config branch.master.merge refs/heads/master
	git push origin master
endif

#git config remote.origin.mirror true

commit: $(OBJS) .gitignore
	$(info -- commiting local --)
	@git add .
	-@git commit -a -m "$(gitm)"

pull: commit
	$(info -- fetching remote --)
	@git pull

push: pull
	$(info -- updating remote --)
	@git push

sync: $(OBJS) .gitignore
ifneq ($(SYNC_REMOTE_PATH),)
ifneq ($(SYNC_REMOTE_HOST),)
ifneq ($(SYNC_REMOTE_USER),)
	async --exclude-from=.gitignore \
	      $(shell pwd) $(SYNC_REMOTE_USER)@$(SYNC_REMOTE_HOST):$(SYNC_REMOTE_PATH)
else
	async --exclude-from=.gitignore \
	      $(shell pwd) $(SYNC_REMOTE_HOST):$(SYNC_REMOTE_PATH)
endif
else
	async --exclude-from=.gitignore $(shell pwd) $(SYNC_REMOTE_PATH)
endif
else
	$(error remote path unspecified)
endif

# =============================================================================
# =============================      Cleanup      =============================
# =============================================================================
.PHONY: clean clean-deps clean-all

clean:
	rm -f $(OBJS)
	rm -f $(EXTERNAL_OBJS)
	rm -f $(TEST_OBJS)
	rm -f $(TRASH)
	rm -f $(PROJECT).tar.gz
	rm -f $(PROJECT)
	rm -f $(TESTER)
	rm -f *.o *~ ._* .DS_Store

clean-deps:
	rm -f $(DEPS)
	rm -f $(TEST_DEPS)
	rm -f *.d
	rm -f *.d.*
	rm -f .*.d
	rm -f .*.d.*

clean-all: clean clean-deps

# =============================================================================
# =============================      Release      =============================
# =============================================================================
.PHONY: release

release: clean-all
ifeq ($(DEBUG),)
	tar -czf ../$(PROJECT).tar.gz -C.. $(shell basename `pwd`)
else
	$(info Error: attempting to release in debug mode)
endif
