package android.graphics;

/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

public class Bitmap {

	/**
	 * Note: mNativeBitmap is used by FaceDetector_jni.cpp Don't change/rename
	 * without updating FaceDetector_jni.cpp
	 * 
	 * @hide
	 */
	public final int mNativeBitmap;

	/**
	 * Backing buffer for the Bitmap. Made public for quick access from drawing
	 * methods -- do NOT modify from outside this class.
	 * 
	 * @hide
	 */
	public byte[] mBuffer;

	// Keep to finalize native resources
	// TODO uncomment
	private final BitmapFinalizer mFinalizer;
	private final boolean mIsMutable;
	private byte[] mNinePatchChunk; // may be null
	private int mWidth = -1;
	private int mHeight = -1;
	private boolean mRecycled;

	// TODO uncomment
	// private static volatile Matrix sScaleMatrix;

	/**
	 * @noinspection UnusedDeclaration
	 */
	/*
	 * Private constructor that must received an already allocated native bitmap
	 * int (pointer).
	 * 
	 * This can be called from JNI code.
	 */
	/* package */Bitmap(int nativeBitmap, byte[] buffer, boolean isMutable,
			byte[] ninePatchChunk, int density) {
		if (nativeBitmap == 0) {
			throw new RuntimeException("internal error: native bitmap is 0");
		}

		mBuffer = buffer;
		// we delete this in our finalizer
		mNativeBitmap = nativeBitmap;
		mFinalizer = new BitmapFinalizer(nativeBitmap);

		mIsMutable = isMutable;
		mNinePatchChunk = ninePatchChunk;
	}

	/**
	 * Returns a mutable bitmap with the specified width and height. Its initial
	 * density is as per {@link #getDensity}.
	 * 
	 * @param width
	 *            The width of the bitmap
	 * @param height
	 *            The height of the bitmap
	 * @param config
	 *            The bitmap config to create.
	 * @throws IllegalArgumentException
	 *             if the width or height are <= 0
	 */
	public static Bitmap createBitmap(int width, int height, Config config) {
		return createBitmap(width, height, config, true);
	}

	/**
	 * Returns a mutable bitmap with the specified width and height. Its initial
	 * density is as per {@link #getDensity}.
	 * 
	 * @param width
	 *            The width of the bitmap
	 * @param height
	 *            The height of the bitmap
	 * @param config
	 *            The bitmap config to create.
	 * @param hasAlpha
	 *            If the bitmap is ARGB_8888 this flag can be used to mark the
	 *            bitmap as opaque. Doing so will clear the bitmap in black
	 *            instead of transparent.
	 * 
	 * @throws IllegalArgumentException
	 *             if the width or height are <= 0
	 */
	private static Bitmap createBitmap(int width, int height, Config config,
			boolean hasAlpha) {
		if (width <= 0 || height <= 0) {
			throw new IllegalArgumentException("width and height must be > 0");
		}
		Bitmap bm = nativeCreate(null, 0, width, width, height,
				config.nativeInt, true);
		if (config == Config.ARGB_8888 && !hasAlpha) {
			nativeErase(bm.mNativeBitmap, 0xff000000);
			nativeSetHasAlpha(bm.mNativeBitmap, hasAlpha);
		} else {
			// No need to initialize it to zeroes; it is backed by a VM byte
			// array
			// which is by definition preinitialized to all zeroes.
			//
			// nativeErase(bm.mNativeBitmap, 0);
		}
		return bm;
	}

	/**
	 * Possible bitmap configurations. A bitmap configuration describes how
	 * pixels are stored. This affects the quality (color depth) as well as the
	 * ability to display transparent/translucent colors.
	 */
	public enum Config {
		// these native values must match up with the enum in SkBitmap.h

		/**
		 * Each pixel is stored as a single translucency (alpha) channel. This
		 * is very useful to efficiently store masks for instance. No color
		 * information is stored. With this configuration, each pixel requires 1
		 * byte of memory.
		 */
		ALPHA_8(2),

		/**
		 * Each pixel is stored on 2 bytes and only the RGB channels are
		 * encoded: red is stored with 5 bits of precision (32 possible values),
		 * green is stored with 6 bits of precision (64 possible values) and
		 * blue is stored with 5 bits of precision.
		 * 
		 * This configuration can produce slight visual artifacts depending on
		 * the configuration of the source. For instance, without dithering, the
		 * result might show a greenish tint. To get better results dithering
		 * should be applied.
		 * 
		 * This configuration may be useful when using opaque bitmaps that do
		 * not require high color fidelity.
		 */
		RGB_565(4),

		/**
		 * Each pixel is stored on 2 bytes. The three RGB color channels and the
		 * alpha channel (translucency) are stored with a 4 bits precision (16
		 * possible values.)
		 * 
		 * This configuration is mostly useful if the application needs to store
		 * translucency information but also needs to save memory.
		 * 
		 * It is recommended to use {@link #ARGB_8888} instead of this
		 * configuration.
		 * 
		 * @deprecated Because of the poor quality of this configuration, it is
		 *             advised to use {@link #ARGB_8888} instead.
		 */
		@Deprecated
		ARGB_4444(5),

		/**
		 * Each pixel is stored on 4 bytes. Each channel (RGB and alpha for
		 * translucency) is stored with 8 bits of precision (256 possible
		 * values.)
		 * 
		 * This configuration is very flexible and offers the best quality. It
		 * should be used whenever possible.
		 */
		ARGB_8888(6);

		final int nativeInt;

		private static Config sConfigs[] = { null, null, ALPHA_8, null,
				RGB_565, ARGB_4444, ARGB_8888 };

		Config(int ni) {
			this.nativeInt = ni;
		}

		static Config nativeToConfig(int ni) {
			return sConfigs[ni];
		}
	}

	private static class BitmapFinalizer {
		private final int mNativeBitmap;

		BitmapFinalizer(int nativeBitmap) {
			mNativeBitmap = nativeBitmap;
		}

		@Override
		public void finalize() {
			try {
				super.finalize();
			} catch (Throwable t) {
				// Ignore
			} finally {
				nativeDestructor(mNativeBitmap);
			}
		}
	}

	// /////////////////////////

	private static native Bitmap nativeCreate(int[] colors, int offset,
			int stride, int width, int height, int nativeConfig, boolean mutable);

	private static native void nativeDestructor(int nativeBitmap);

	private static native void nativeErase(int nativeBitmap, int color);

	private static native boolean nativeHasAlpha(int nativeBitmap);

	private static native void nativeSetHasAlpha(int nBitmap, boolean hasAlpha);
}
