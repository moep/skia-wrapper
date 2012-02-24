package org.mapsforge.skia;

public class Canvas {
	private int nativeObj;
	private Bitmap bmp;
	
	public Canvas(Bitmap bmp) {
		this.bmp = bmp;
		this.nativeObj = createCanvas(this.bmp);
	}
	
	private static native int createCanvas(Bitmap bmp);
}
