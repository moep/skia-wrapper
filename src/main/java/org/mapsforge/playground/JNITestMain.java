package org.mapsforge.playground;

public class JNITestMain {
	private static native void printHello();
	
	public static void main(String[] args) {
		System.out.println("Loading library: ");
		System.loadLibrary("test");
		System.out.println("Calling JNITest: " );
		printHello();
	}
}
