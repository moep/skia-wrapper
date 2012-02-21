#include "org_mapsforge_playground_JNITestMain.h"
#include <stdio.h>

JNIEXPORT void JNICALL Java_org_mapsforge_playground_JNITestMain_printHello(JNIEnv *env, jobject obj)
{
  printf("JNIIIII\r\n");
}

