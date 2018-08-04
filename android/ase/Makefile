EMPTY :=
SPACE := $(EMPTY) $(EMPTY)

MAKE_PATHS := etc/paths.mk
ifeq ($(wildcard $(MAKE_PATHS)),)

.DEFAULT_GOAL := do_configure
.PHONY: do_configure
do_configure:
	./configure
	$(MAKE)

else

include $(MAKE_PATHS)
include etc/configuration.mk

PACKAGE_PATH := $(subst .,/,$(PACKAGE))

ANDROID_SDK_PLATFORM_PATH       := $(ANDROID_SDK_PATH)/platforms/$(PLATFORM)

ANDROID_SDK_TOOLS_PATH          := $(ANDROID_SDK_PATH)/tools
ANDROID_SDK_PLATFORM_TOOLS_PATH := $(ANDROID_SDK_PATH)/platform-tools
ANDROID_SDK_BUILD_TOOLS_PATH    := $(subst $(SPACE),:,$(wildcard $(ANDROID_SDK_PATH)/build-tools/*))
PATH += :$(ANDROID_SDK_TOOLS_PATH):$(ANDROID_SDK_PLATFORM_TOOLS_PATH):$(ANDROID_SDK_BUILD_TOOLS_PATH):$(ANDROID_NDK_PATH):$(JAVA_SDK_PATH)/bin

JARS_FILES = $(wildcard jars/*)
JARS_FILES_CLASSPATH = $(if $(JARS_FILES),-classpath $(subst $(SPACE),:,$(JARS_FILES)),)

.DEFAULT_GOAL := debug
.PHONY: debug
debug: DEBUG_MODE := --debug-mode
debug: bin/$(NAME)-$(VERSION).apk

.PHONY: release
release: DEBUG_MODE :=
release: bin/$(NAME)-$(VERSION).apk

jars:
	mkdir $@
	$(MAKE) -C jars_src
	cp jars_src/jars/* $@
	touch $@

gen/$(PACKAGE_PATH)/R.java: AndroidManifest.xml res/*/*
	mkdir -p gen/$(PACKAGE_PATH)
	aapt p -m -M AndroidManifest.xml -S res -I $(ANDROID_SDK_PLATFORM_PATH)/android.jar -J gen

bin/classes: jars gen/$(PACKAGE_PATH)/R.java src/$(PACKAGE_PATH)/*
	mkdir -p $@
	javac -encoding ascii -source 1.6 -target 1.6 -d $@ -bootclasspath $(ANDROID_SDK_PLATFORM_PATH)/android.jar $(JARS_FILES_CLASSPATH) gen/$(PACKAGE_PATH)/R.java src/$(PACKAGE_PATH)/*
	touch $@

bin/classes.dex: bin/classes jars
	dx --dex --output=$@ $< $(JARS_FILES)

bin/$(NAME)-$(VERSION)-raw.apk: AndroidManifest.xml res/*/* bin/classes.dex
	aapt p -f -M AndroidManifest.xml $(DEBUG_MODE) -S res -I $(ANDROID_SDK_PLATFORM_PATH)/android.jar -F $@

libs:
	ndk-build
	touch libs

bin/$(NAME)-$(VERSION)-unzipalign.apk: bin/$(NAME)-$(VERSION)-raw.apk bin/classes.dex jars libs
#	apkbuilder $@ -u -z bin/$(NAME)-$(VERSION)-raw.apk -f bin/classes.dex -rf src -rj jars -nf libs
	java -Xmx128M -classpath $(ANDROID_SDK_PATH)/tools/lib/sdklib.jar com.android.sdklib.build.ApkBuilderMain $@ -u -z bin/$(NAME)-$(VERSION)-raw.apk -f bin/classes.dex -rf src -rj jars -nf libs

bin/$(NAME)-$(VERSION)-unsigned.apk: bin/$(NAME)-$(VERSION)-unzipalign.apk
	zipalign -f 4 $< $@

$(KEYSTORE_FILE):
	keytool -genkey -alias $(KEY_ALIAS) -keyalg RSA -dname $(KEY_DNAME) -keysize 2048 -validity 10000 -keypass $(KEY_PASSWORD) -keystore $@ -storepass $(KEY_STORE_PASSWORD)

bin/$(NAME)-$(VERSION).apk: bin/$(NAME)-$(VERSION)-unsigned.apk $(KEYSTORE_FILE)
#	jarsigner -sigalg MD5withRSA -digestalg SHA1 -keystore $(KEYSTORE_FILE) -keypass $(KEY_PASSWORD) -storepass $(KEY_STORE_PASSWORD) -signedjar $@ bin/$(NAME)-$(VERSION)-unsigned.apk $(KEY_ALIAS)
	apksigner sign --ks $(KEYSTORE_FILE) --ks-pass pass:$(KEY_PASSWORD) --key-pass pass:$(KEY_PASSWORD) --ks-key-alias $(KEY_ALIAS) --out $@ bin/$(NAME)-$(VERSION)-unsigned.apk

.PHONY: clean
clean:
	$(MAKE) -C jars_src clean
	rm -rf bin gen jars libs obj

.PHONY: purge
purge: clean
	rm -f etc/keystore.file etc/paths.mk

.PHONY: verify
verify: bin/$(NAME)-$(VERSION).apk $(KEYSTORE_FILE)
	zipalign -c -v 4 bin/$(NAME)-$(VERSION).apk
	keytool -list -keystore $(KEYSTORE_FILE) -storepass $(KEY_STORE_PASSWORD)
#	jarsigner -verbose -verify -certs bin/$(NAME)-$(VERSION).apk
	apksigner verify --verbose --print-certs bin/$(NAME)-$(VERSION).apk

.PHONY: emulator
emulator:
	emulator -no-snapshot-save -avd $(AVD) &

.PHONY: log
log:
	adb logcat

.PHONY: clear-log
clear-log:
	adb logcat -c

.PHONY: shell
shell:
	adb root
	adb shell

.PHONY: install
install: bin/$(NAME)-$(VERSION).apk
	adb install bin/$(NAME)-$(VERSION).apk

.PHONY: reinstall
reinstall: bin/$(NAME)-$(VERSION).apk
	adb install -r bin/$(NAME)-$(VERSION).apk

.PHONY: start
start:
	adb root
	adb shell am start -a android.intent.action.MAIN -n $(PACKAGE)/.$(ACTIVITY)

.PHONY: run
run: reinstall start

.PHONY: stop
stop:
	adb root
	adb shell kill -9 `adb shell ps | grep $(PACKAGE) | tr -s ' ' | cut -d ' ' -f 2`

.PHONY: uninstall
uninstall:
	adb uninstall $(PACKAGE)

endif
