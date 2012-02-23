package org.mapsforge.playground;

public class FooType {
	private int val;
	private int nativeObj;
	
	public FooType(int val) {
		System.out.println("[Java] FooType(" + val + ")");
		this.val = val;
		this.nativeObj = native_createFooType(val);
		System.out.println("[Java] Native FooType address: " + nativeObj);
	}
	
	//public native int getVal();
	
	public void printVal() {
		System.out.println("[Java] Val: " + val);
	}
	
	public native int getVal();
	public static native int native_createFooType(int val);
}
