#include <string.h>
#include <jni.h>

char* jni_2_util(void);

jstring Java_org_chupcko_ase_MainActivity_jni2Data(JNIEnv* env, jobject thiz)
{
  return (*env)->NewStringUTF(env, jni_2_util());
}
