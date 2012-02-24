#include "jni.h"
#include <stdio.h>

#include "JNIHelper.h"
#include "MinimalisticGlue.h"

jclass JNIHelper::getClassByName(const char* className) {
	jclass clazz = JNIHelper::env->FindClass(className);
	if (clazz == NULL) {
		printf("[Native] ERROR: Could not find Java class: %s\r\n", className);
	}

	return clazz;
}

void* JNIHelper::getNativeObject(JNIEnv* env, jobject obj) {
	jclass clazz = env->GetObjectClass(obj);
	jfieldID fID = env->GetFieldID(clazz, "nativeObj", "I");
	if (fID == 0) {
		printf("[Native] ERROR: Could not get the native objects address from the corresponding Java object.\r\n");
	}

	return (void*) env->GetIntField(obj, fID);
}

void JNIHelper::registerMethodsForClass(const char* className,
		JNINativeMethod methods[], int numberOfMethods) {
	printf("[Native] Registering %d method(s) for class '%s'\r\n",
			numberOfMethods, className);
	jclass clazz = JNIHelper::getClassByName(className);
	JNIHelper::env->RegisterNatives(clazz, methods, numberOfMethods);
}

void JNIHelper::init(JNIEnv *env) {
	printf("[Native] JNIHelper::init() \r\n");
	printf("[Native]   env @ 0x%x \r\n", (int) env);
	JNIHelper::env = env;
}

JNIEnv* JNIHelper::env;
////////////////////////////////////////////////////

// Entry point
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved) {
	printf("[Native] Loading JNI library. Wish us luck...\r\n");
	JNIEnv *env;

	if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6)) {
		return JNI_ERR; /* JNI version not supported */
	}

	// Initialize JNI helper
	JNIHelper::init(env);

	// Register methods (call register function for each glue class)
	Bitmap_registerMethods();
	Canvas_registerMethods();
	return JNI_VERSION_1_6;
}
