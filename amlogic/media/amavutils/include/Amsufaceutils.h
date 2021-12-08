/*
 * Copyright (c) 2014 Amlogic, Inc. All rights reserved.
 *
 * This source code is subject to the terms and conditions defined in the
 * file 'LICENSE' which is part of this source code package.
 *
 * Description:
 */


#ifndef AMSURFACE_UTILS_HEADER_SS
#define AMSURFACE_UTILS_HEADER_SS

#include <gui/Surface.h>


namespace android
{

int InitVideoSurfaceTexture(const sp<IGraphicBufferProducer>& bufferProducer);
}
#endif
