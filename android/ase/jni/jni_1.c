#include <string.h>
#include <jni.h>

char* jni_1_util(void);

jstring Java_org_chupcko_ase_MainActivity_jni1Data(JNIEnv* env, jobject thiz)
{
  return (*env)->NewStringUTF(env, jni_1_util());
}
