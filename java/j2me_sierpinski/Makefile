NAME=sierpinski
JAVA_DIR=/usr/lib/java
J2ME_DIR=/home/chupcko/wrk/j2me/WTK2.2

PASSWORD=pacific1234
CERTIFICATE=certpti

all:
	mkdir -p tmpclasses classes
	${JAVA_DIR}/bin/javac \
	  -bootclasspath ${J2ME_DIR}/lib/cldcapi11.jar:${J2ME_DIR}/lib/midpapi20.jar \
	  -source 1.3 \
	  -target 1.3 \
	  -d tmpclasses \
	  -classpath tmpclasses \
	  source/*.java
	${J2ME_DIR}/bin/preverify \
	  -classpath ${J2ME_DIR}/lib/cldcapi11.jar:${J2ME_DIR}/lib/midpapi20.jar:tmpclasses \
	  -d classes \
	  tmpclasses
	${JAVA_DIR}/bin/jar cmf \
	  MANIFEST.MF \
	  ${NAME}.jar \
	  -C classes .
	echo -n "MIDlet-Jar-Size: " > ${NAME}.jad
	stat -t ${NAME}.jar | cut -d " " -f 2 >> ${NAME}.jad
	echo "MIDlet-Jar-URL: ${NAME}.jar" >> ${NAME}.jad
	cat MANIFEST.MF >> ${NAME}.jad

sign:
	mkdir -p tmpclasses classes
	${JAVA_DIR}/bin/javac \
	  -bootclasspath ${J2ME_DIR}/lib/cldcapi11.jar:${J2ME_DIR}/lib/midpapi20.jar \
	  -source 1.3 \
	  -target 1.3 \
	  -d tmpclasses \
	  -classpath tmpclasses \
	  source/*.java
	${J2ME_DIR}/bin/preverify \
	  -classpath ${J2ME_DIR}/lib/cldcapi11.jar:${J2ME_DIR}/lib/midpapi20.jar:tmpclasses \
	  -d classes \
	  tmpclasses
	${JAVA_DIR}/bin/jar cmf \
	  MANIFEST.MF \
	  ${NAME}.jar \
	  -C classes .
	cat MANIFEST.MF > ${NAME}.jad.0
	${JAVA_DIR}/bin/jarsigner -storepass ${PASSWORD} ${NAME}.jar ${CERTIFICATE}
	echo ${JAVA_DIR}/bin/keytool -list -rfc -storepass ${PASSWORD}
	${JAVA_DIR}/bin/java -jar ${J2ME_DIR}/bin/JadTool.jar \
	  -addcert \
	  -alias ${CERTIFICATE} \
	  -inputjad ${NAME}.jad.0 \
	  -outputjad ${NAME}.jad.1 \
	  -chainnum 1 \
	  -certnum 1
	${JAVA_DIR}/bin/java -jar ${J2ME_DIR}/bin/JadTool.jar \
	  -addcert \
	  -alias ${CERTIFICATE} \
	  -inputjad ${NAME}.jad.1 \
	  -outputjad ${NAME}.jad.2 \
	  -chainnum 1 \
	  -certnum 2
	${JAVA_DIR}/bin/java -jar ${J2ME_DIR}/bin/JadTool.jar \
	  -addcert \
	  -alias ${CERTIFICATE} \
	  -inputjad ${NAME}.jad.2 \
	  -outputjad ${NAME}.jad.3 \
	  -chainnum 1 \
	  -certnum 3
	${JAVA_DIR}/bin/java -jar ${J2ME_DIR}/bin/JadTool.jar \
	  -addjarsig \
	  -alias ${CERTIFICATE} \
	  -keypass ${PASSWORD} \
	  -inputjad ${NAME}.jad.3 \
	  -outputjad ${NAME}.jad.4 \
	  -jarfile ${NAME}.jar
	echo -n "MIDlet-Jar-Size: " > ${NAME}.jad
	stat -t ${NAME}.jar | cut -d " " -f 2 >> ${NAME}.jad
	echo "MIDlet-Jar-URL: ${NAME}.jar" >> ${NAME}.jad
	cat ${NAME}.jad.4 >> ${NAME}.jad

run:
	${J2ME_DIR}/bin/emulator -Xdescriptor:${NAME}.jad

clean:
	rm -rf tmpclasses classes ${NAME}.jar ${NAME}.jad ${NAME}.jad.*
