/*
// Copyright (c) 2014 Intel Corporation
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
// This file is modified by Amlogic, Inc. 2017.01.17.
*/

#ifndef IPLATFORM_FACTORY_H_
#define IPLATFORM_FACTORY_H_


#include <IDisplayDevice.h>

namespace android {
namespace amlogic {


class IPlatFactory {

public:
    virtual ~IPlatFactory() {};
public:

    virtual IDisplayDevice* createDisplayDevice(int disp) = 0;
};
} // namespace amlogic
} // namespace android

#endif /* DATABUFFER_H__ */
