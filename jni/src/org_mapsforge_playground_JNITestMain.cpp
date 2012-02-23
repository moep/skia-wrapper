#include "org_mapsforge_playground_JNITestMain.h"
#include <stdio.h>

JNIEXPORT void JNICALL Java_org_mapsforge_playground_JNITestMain_printHello
  (JNIEnv *env, jclass clazz)
{
  printf("[JNI] Hello\r\n");
}

JNIEXPORT jobject JNICALL Java_org_mapsforge_playground_JNITestMain_createObject
  (JNIEnv *env, jclass clazz, jint val)
{
  printf("[JNI] Creating Java object (val=%d)\r\n", val);
  jclass FooType_class = env->FindClass("org/mapsforge/playground/FooType");
  jmethodID FooType_defCtor = env->GetMethodID(FooType_class, "<init>", "(I)V");
  jobject instance = env->NewObject(FooType_class, FooType_defCtor, val);
  env->CallVoidMethod(instance, env->GetMethodID(FooType_class, "printVal", "()V"));
  return instance;
}


