#include "jni.h"

#ifndef JNIHELPER_H
#define JNIHELPER_H

class JNIHelper {
public:
	static void init(JNIEnv *env);
	static jclass getClassByName(const char*);
	static void* getNativeObject(JNIEnv* env, jobject obj);
	static void
	registerMethodsForClass(const char* className,
			JNINativeMethod methods[], int numberOfMethods);
	static JNIEnv *env;
};

#endif
