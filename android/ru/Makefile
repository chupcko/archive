EMPTY :=
SPACE := $(EMPTY) $(EMPTY)

MAKE_PATHS := etc/paths.mk
ifeq ($(wildcard $(MAKE_PATHS)),)
  $(error First do ./configure)
endif
include $(MAKE_PATHS)
include etc/configuration.mk

PACKAGE_PATH := $(subst .,/,$(PACKAGE))

ANDROID_SDK_PLATFORM_PATH       := $(ANDROID_SDK_PATH)/platforms/$(PLATFORM)

ANDROID_SDK_TOOLS_PATH          := $(ANDROID_SDK_PATH)/tools
ANDROID_SDK_PLATFORM_TOOLS_PATH := $(ANDROID_SDK_PATH)/platform-tools
ANDROID_SDK_BUILD_TOOLS_PATH    := $(subst $(SPACE),:,$(wildcard $(ANDROID_SDK_PATH)/build-tools/*))
PATH += :$(ANDROID_SDK_TOOLS_PATH):$(ANDROID_SDK_PLATFORM_TOOLS_PATH):$(ANDROID_SDK_BUILD_TOOLS_PATH):$(ANDROID_NDK_PATH):$(JAVA_SDK_PATH)/bin

.DEFAULT_GOAL := debug
.PHONY: debug
debug: DEBUG_MODE := --debug-mode
debug: bin/$(NAME)-$(VERSION).apk

.PHONY: release
release: DEBUG_MODE :=
release: bin/$(NAME)-$(VERSION).apk

gen/$(PACKAGE_PATH)/R.java: AndroidManifest.xml res/*/*
	mkdir -p gen/$(PACKAGE_PATH)
	aapt p -m -M AndroidManifest.xml -A assets -S res -I $(ANDROID_SDK_PLATFORM_PATH)/android.jar -J gen

bin/classes: gen/$(PACKAGE_PATH)/R.java src/$(PACKAGE_PATH)/*
	mkdir -p bin/classes
	javac -encoding ascii -source 1.5 -target 1.5 -d bin/classes -bootclasspath $(ANDROID_SDK_PLATFORM_PATH)/android.jar gen/$(PACKAGE_PATH)/R.java src/$(PACKAGE_PATH)/*
	touch bin/classes

bin/classes.dex: bin/classes
	dx --dex --output=bin/classes.dex bin/classes

bin/$(NAME)-$(VERSION)-raw.apk: AndroidManifest.xml res/*/* bin/classes.dex
	aapt p -f -M AndroidManifest.xml $(DEBUG_MODE) -A assets -S res -I $(ANDROID_SDK_PLATFORM_PATH)/android.jar -F bin/$(NAME)-$(VERSION)-raw.apk

bin/$(NAME)-$(VERSION)-unsigned.apk: bin/$(NAME)-$(VERSION)-raw.apk bin/classes.dex
	java -Xmx128M -classpath $(ANDROID_SDK_PATH)/tools/lib/sdklib.jar com.android.sdklib.build.ApkBuilderMain bin/$(NAME)-$(VERSION)-unsigned.apk -u -z bin/$(NAME)-$(VERSION)-raw.apk -f bin/classes.dex -rf src -nf libs

$(KEYSTORE_FILE):
	keytool -genkey -alias $(KEY_ALIAS) -keyalg RSA -dname $(KEY_DNAME) -keysize 2048 -validity 10000 -keypass $(KEY_PASSWORD) -keystore $(KEYSTORE_FILE) -storepass $(KEY_STORE_PASSWORD)

bin/$(NAME)-$(VERSION)-unzipalign.apk: $(KEYSTORE_FILE) bin/$(NAME)-$(VERSION)-unsigned.apk
	jarsigner -sigalg MD5withRSA -digestalg SHA1 -keystore $(KEYSTORE_FILE) -keypass $(KEY_PASSWORD) -storepass $(KEY_STORE_PASSWORD) -signedjar bin/$(NAME)-$(VERSION)-unzipalign.apk bin/$(NAME)-$(VERSION)-unsigned.apk $(KEY_ALIAS)

bin/$(NAME)-$(VERSION).apk: bin/$(NAME)-$(VERSION)-unzipalign.apk
	zipalign -f 4 bin/$(NAME)-$(VERSION)-unzipalign.apk bin/$(NAME)-$(VERSION).apk

.PHONY: clean
clean:
	rm -rf bin gen obj

.PHONY: purge
purge: clean
	rm -f etc/keystore.file etc/paths.mk

.PHONY: verify
verify: $(KEYSTORE_FILE) bin/$(NAME)-$(VERSION).apk
	zipalign -c -v 4 bin/$(NAME)-$(VERSION).apk
	keytool -list -keystore $(KEYSTORE_FILE) -storepass $(KEY_STORE_PASSWORD)
	jarsigner -verbose -verify -certs -keystore $(KEYSTORE_FILE) bin/$(NAME)-$(VERSION).apk

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
	adb shell

.PHONY: install
install: bin/$(NAME)-$(VERSION).apk
	adb install bin/$(NAME)-$(VERSION).apk

.PHONY: reinstall
reinstall: bin/$(NAME)-$(VERSION).apk
	adb install -r bin/$(NAME)-$(VERSION).apk

.PHONY: start
start:
	adb shell am start -a android.intent.action.MAIN -n $(PACKAGE)/.$(ACTIVITY)

.PHONY: run
run: reinstall start

.PHONY: stop
stop:
	adb shell kill -9 `adb shell ps | grep $(PACKAGE) | tr -s ' ' | cut -d ' ' -f 2`

.PHONY: uninstall
uninstall:
	adb uninstall $(PACKAGE)
