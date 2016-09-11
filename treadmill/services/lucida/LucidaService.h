/*
 *  Copyright (c) 2014, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#pragma once

#include "treadmill/services/lucida/Request.h"

namespace facebook {
namespace windtunnel {
namespace treadmill {

class LucidaService {
 public:
  typedef LucidaRequest Request;
  typedef LucidaReply Reply;
};

} // namespace treadmill
} // namespace windtunnel
} // namespace facebook
