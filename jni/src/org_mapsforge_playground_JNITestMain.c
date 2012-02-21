#include "org_mapsforge_playground_JNITestMain.h"
#include <stdio.h>

JNIEXPORT void JNICALL Java_org_mapsforge_playground_JNITestMain_printHello(JNIEnv *, jobject)
{
  printf("JNIIIII\r\n");
}

int main() {
  printf("platzhalter\n")
  return 0;
}
