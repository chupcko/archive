include ../../etc/paths.mk
include ../../etc/configuration.mk

PACKAGE_PATH := $(subst .,/,$(PACKAGE))

ANDROID_SDK_PLATFORM_PATH       := $(ANDROID_SDK_PATH)/platforms/$(PLATFORM)

ANDROID_SDK_TOOLS_PATH          := $(ANDROID_SDK_PATH)/tools
ANDROID_SDK_PLATFORM_TOOLS_PATH := $(ANDROID_SDK_PATH)/platform-tools
ANDROID_SDK_BUILD_TOOLS_PATH    := $(subst $(SPACE),:,$(wildcard $(ANDROID_SDK_PATH)/build-tools/*))
PATH += :$(ANDROID_SDK_TOOLS_PATH):$(ANDROID_SDK_PLATFORM_TOOLS_PATH):$(ANDROID_SDK_BUILD_TOOLS_PATH):$(ANDROID_NDK_PATH):$(JAVA_SDK_PATH)/bin

.DEFAULT_GOAL := all
.PHONY: all
all: ../jars/ase_1.jar

bin/classes:
	mkdir -p $@
	javac -encoding ascii -source 1.6 -target 1.6 -d $@ -bootclasspath $(ANDROID_SDK_PLATFORM_PATH)/android.jar src/$(PACKAGE_PATH)/jar_1/*
	touch $@

../jars:
	mkdir -p $@

../jars/ase_1.jar: bin/classes ../jars
	jar cf $@ -C $< .

.PHONY: clean
clean:
	rm -rf bin
