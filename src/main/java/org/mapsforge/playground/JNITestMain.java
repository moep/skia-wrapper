package org.mapsforge.playground;

public class JNITestMain {
	private static native void native_printHello();
	private static native int native_createFooType();

	private static void printLibraryPaths(String paths) {
		for (String path : paths.split(":")) {
			System.out.println("  " + path);
		}
	}

	public static void main(String[] args) {
		final String workingDirectory = System.getProperty("user.dir");
		final String customLibraryPath = workingDirectory + "/jni/";
		final String javaLibraryPath = System.getProperty("java.library.path");

		// Set library directory for our created libraries
		// System.setProperty("java.library.path", javaLibraryPath + ":" +
		// customLibraryPath);
		// System.out.println("Java library path: ");
		// printLibraryPaths(System.getProperty("java.library.path"));

		// Load libraries
		System.load(customLibraryPath + "libtest.so");
		native_printHello();
		FooType ft = new FooType(42);
		FooType ft2 = new FooType(88);
		System.out.println("Val1: " + ft.getVal());
		System.out.println("Val2: " + ft2.getVal());
		// Perform tests
	}

}
