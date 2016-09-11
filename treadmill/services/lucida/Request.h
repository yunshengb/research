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

#include <string>

#include "treadmill/Request.h"

namespace facebook {
namespace windtunnel {
namespace treadmill {

class Request;

class LucidaReply {
};

class LucidaRequest : public Request {
 public:
  enum Operation {
    GET,
    SET,
    DELETE
  };

  LucidaRequest(Operation type, std::string key)
    : type_(type),
      key_(std::move(key)) { }

  virtual ~LucidaRequest() {}

  std::string getRequestType() {
    return "LucidaRequest";
  }

  Operation which() {
    return type_;
  }

  void setValue(const std::string value) {
    value_ = value;
  }

  const std::string& key() const {
    return key_;
  }

  const std::string& value() const {
    return value_;
  }

 private:
  Operation type_;
  std::string key_;
  std::string value_;
};

}  // namespace treadmill
}  // namespace windtunnel
}  // namespace facebook
