include etc/configuration.mk

KEYSTORE_FILE = etc/keystore.file
ANDROID_PLATFORM_PATH = $(ANDROID_PATH)/platforms/$(PLATFORM)
PACKAGE_PATH = $(subst .,/,$(PACKAGE))
ifeq ($(LIBS), )
  LIBS_CLASSPATH =
else
  LIBS_CLASSPATH = -classpath $(LIBS)
endif
PATH += :$(ANDROID_PATH)/tools:$(ANDROID_PATH)/platform-tools:$(ANDROID_PLATFORM_PATH)/tools

.PHONY: all clean verify emulator log clear-log shell install reinstall start run stop uninstall

all: bin/$(NAME)-$(VERSION).apk

$(KEYSTORE_FILE):
	keytool -genkey -alias $(KEY_ALIAS) -keyalg RSA -dname $(KEY_DNAME) -keysize 2048 -validity 10000 -keypass $(KEY_PASSWORD) -keystore $(KEYSTORE_FILE) -storepass $(KEY_STORE_PASSWORD)

gen/$(PACKAGE_PATH)/R.java: res/*/*
	mkdir -p gen/$(PACKAGE_PATH)
	aapt p -m -M AndroidManifest.xml -S res -I $(ANDROID_PLATFORM_PATH)/android.jar -J gen

bin/classes: gen/$(PACKAGE_PATH)/R.java src/$(PACKAGE_PATH)/*
	mkdir -p bin/classes
	javac -encoding ascii -source 1.5 -target 1.5 -d bin/classes -bootclasspath $(ANDROID_PLATFORM_PATH)/android.jar $(LIBS_CLASEPATH) gen/$(PACKAGE_PATH)/R.java src/$(PACKAGE_PATH)/*
	touch bin/classes

bin/classes.dex: bin/classes
	dx --dex --output=bin/classes.dex bin/classes $(LIBS)

bin/$(NAME)-$(VERSION)-raw.apk: bin/classes.dex
	aapt p -f -M AndroidManifest.xml -S res -I $(ANDROID_PLATFORM_PATH)/android.jar -F bin/$(NAME)-$(VERSION)-raw.apk

bin/$(NAME)-$(VERSION)-unsigned.apk: bin/$(NAME)-$(VERSION)-raw.apk
	apkbuilder bin/$(NAME)-$(VERSION)-unsigned.apk -u -z bin/$(NAME)-$(VERSION)-raw.apk -f bin/classes.dex -rf src -rj libs

bin/$(NAME)-$(VERSION)-unzipalign.apk: $(KEYSTORE_FILE) bin/$(NAME)-$(VERSION)-unsigned.apk
	jarsigner -keystore $(KEYSTORE_FILE) -keypass $(KEY_PASSWORD) -storepass $(KEY_STORE_PASSWORD) -signedjar bin/$(NAME)-$(VERSION)-unzipalign.apk bin/$(NAME)-$(VERSION)-unsigned.apk $(KEY_ALIAS)

bin/$(NAME)-$(VERSION).apk: bin/$(NAME)-$(VERSION)-unzipalign.apk
	zipalign -f 4 bin/$(NAME)-$(VERSION)-unzipalign.apk bin/$(NAME)-$(VERSION).apk

clean:
	rm -rf gen bin

verify: $(KEYSTORE_FILE) bin/$(NAME)-$(VERSION).apk
	zipalign -c -v 4 bin/$(NAME)-$(VERSION).apk
	keytool -list -keystore $(KEYSTORE_FILE) -storepass $(KEY_STORE_PASSWORD)
	jarsigner -verbose -verify -certs -keystore $(KEYSTORE_FILE) bin/$(NAME)-$(VERSION).apk

emulator:
	emulator -no-snapshot-save -avd $(AVD) &

log:
	adb logcat

clear-log:
	adb logcat -c

shell:
	adb shell

install: bin/$(NAME)-$(VERSION).apk
	adb install bin/$(NAME)-$(VERSION).apk

reinstall: bin/$(NAME)-$(VERSION).apk
	adb install -r bin/$(NAME)-$(VERSION).apk

start:
	adb shell am start -a android.intent.action.MAIN -n $(PACKAGE)/.$(ACTIVITY)

run: reinstall start

stop:
	adb shell kill -9 `adb shell ps | grep $(PACKAGE) | tr -s ' ' | cut -d ' ' -f 2`

uninstall:
	adb uninstall $(PACKAGE)
