/*
// Copyright (c) 2016 Amlogic
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

#ifndef ICOMPOSER_FACTORY_H_
#define ICOMPOSER_FACTORY_H_


#include <IComposer.h>

namespace android {
namespace amlogic {


class IComposerFactory {

public:
    virtual ~IComposerFactory() {};

public:
    virtual IComposer* createComposer(String8 key) = 0;
};
} // namespace amlogic
} // namespace android

#endif /* ICOMPOSER_FACTORY_H_ */
