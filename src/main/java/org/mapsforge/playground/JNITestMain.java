package org.mapsforge.playground;

public class JNITestMain {
	private native void printHello();
	
	public static void main(String[] args) {
		System.out.println("Calling JNITest: " );
	}
}
