#include "jni.h"
#include "FooType.h"
#include <stdio.h>

#define SIZEOF(array) sizeof(array)/sizeof(array[0])

// http://source-android.frandroid.com/dalvik/libnativehelper/JNIHelp.cpp

/////////////////////////////////////////////////////////////

void
printHello()
{
  printf("[Native] Hello\r\n");
}

int
getVal(JNIEnv* env, jclass* clazz, jobject* ft)
{
  printf("[Native] getVal()\r\n");
  FooType *ftt = (FooType*)ft;
  ftt->getVal();
  return 11;
}

FooType* createFooType(JNIEnv *env, jclass clazz, int val) {
  printf("[Native] createFooType(%d)\r\n", val);
  FooType *ft = new FooType(val);
  return ft;
}

/////////////////////////////////////////////////////////////

jclass
getClassByName(JNIEnv *env, const char* className)
{
  jclass clazz = env->FindClass(className);
  if (clazz == NULL)
    {
      printf("[Native] ERROR: Could not find Java class: %s\r\n", className);
    }

  return clazz;
}

void
registerMethodsForClass(JNIEnv* env, const char* className,
    JNINativeMethod methods[], int numberOfMethods)
{
  printf("[Native] Registering %d method(s) for class '%s'\r\n", numberOfMethods, className);
  jclass clazz = getClassByName(env, className);

//  JNINativeMethod method;
//  method.name = (char*)&"native_printHello";
//  method.signature = (char*)&"()V";
//  method.fnPtr = (void*)printHello;
//  env->RegisterNatives(clazz, &method, 1);

  //env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0]));
  env->RegisterNatives(clazz, methods, numberOfMethods);
}

/////////////////////////////////////////////////////////////

// JNITestMain.java
static JNINativeMethod JNITestMain_methods[] =
  {
    { (char*) &"native_printHello", (char*) &"()V", (void*) printHello }
  };

static JNINativeMethod FooType_methods[] = {
    { (char*) &"getVal", (char*) &"()I", (void*) getVal},
    { (char*) &"native_createFooType", (char*) &"(I)I", (void*) createFooType}
};
// Export methods on load
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved)
{
  printf("[Native] Loading JNI library. Wish us luck...\r\n");
  JNIEnv *env;

  if (jvm->GetEnv((void **) &env, JNI_VERSION_1_2))
    {
      return JNI_ERR; /* JNI version not supported */
    }

  registerMethodsForClass(env, "org/mapsforge/playground/JNITestMain", JNITestMain_methods, SIZEOF(JNITestMain_methods));
  registerMethodsForClass(env, "org/mapsforge/playground/FooType", FooType_methods, SIZEOF(FooType_methods));

  return JNI_VERSION_1_2;
}
