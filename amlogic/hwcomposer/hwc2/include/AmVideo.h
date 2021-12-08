/*
// Copyright (c) 2017 Amlogic
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
*/
#ifndef AML_VIDEO_H_
#define AML_VIDEO_H_

#include <utils/Mutex.h>

namespace android {
class AmVideo {
public:
    static AmVideo* getInstance();
    int presentVideo(bool bPresent);
    bool isVideoPresent() {return mVideoPresent;}
    int getvideodisable(int* mode);
    int setvideodisable(int mode);
    int getOmxKeepLastFrame(unsigned int *keepLastFrame);

protected:
    AmVideo();
    ~AmVideo();

    int getVideoPresent(bool& output);

private:
    static AmVideo* mInstance;
    static Mutex mLock;

    int mDevFd;
    bool mVideoPresent;
};

}
#endif//AML_VIDEO_H_

