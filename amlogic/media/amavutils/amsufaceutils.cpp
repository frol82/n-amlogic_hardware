/*
 * Copyright (c) 2014 Amlogic, Inc. All rights reserved.
 *
 * This source code is subject to the terms and conditions defined in the
 * file 'LICENSE' which is part of this source code package.
 *
 * Description:
 */


#include "utils/Log.h"
#include <android/native_window.h>
#include "Amsufaceutils.h"

namespace android
{


int InitVideoSurfaceTexture(const sp<IGraphicBufferProducer>& bufferProducer)
{
    sp<ANativeWindow> mNativeWindow = NULL;
	if (bufferProducer == NULL) 
		return -1;
	mNativeWindow = new Surface(bufferProducer);
	///native_window_set_usage(mNativeWindow.get(), GRALLOC_USAGE_HW_TEXTURE | GRALLOC_USAGE_EXTERNAL_DISP | GRALLOC_USAGE_AML_VIDEO_OVERLAY);
	native_window_set_buffers_format(mNativeWindow.get(), WINDOW_FORMAT_RGBA_8888);
	native_window_set_scaling_mode(mNativeWindow.get(), NATIVE_WINDOW_SCALING_MODE_FREEZE);
	return 0;
}

}
