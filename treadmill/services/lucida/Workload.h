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

#include <vector>

#include "treadmill/services/lucida/LucidaService.h"

#include "treadmill/Workload.h"

DECLARE_int64(number_of_keys);

using folly::Future;
using folly::Promise;

namespace facebook {
namespace windtunnel {
namespace treadmill {

template <>
class Workload<LucidaService> {
 public:
  enum State {
    WARMUP,
    GET
  };

  Workload<LucidaService>(folly::dynamic config)
    : state_(State::WARMUP),
      index_(0) { }

  std::tuple<std::unique_ptr<LucidaService::Request>,
             Promise<LucidaService::Reply>,
             Future<LucidaService::Reply>>
  getNextRequest() {
    if (index_ == FLAGS_number_of_keys) {
      index_ = 0;
    }

    std::string key = std::to_string(index_);

    std::unique_ptr<LucidaService::Request> request;
    if (state_ == State::WARMUP) {
      request = folly::make_unique<LucidaRequest>(LucidaRequest::SET,
                                                     std::move(key));
      request->setValue(std::to_string(index_));
      if (index_ == FLAGS_number_of_keys - 1) {
        LOG(INFO) << "WARMUP complete";
        state_ = State::GET;
      }
    } else if (state_ == State::GET) {
      request = folly::make_unique<LucidaRequest>(LucidaRequest::GET,
                                                     std::move(key));
    }
    Promise<LucidaService::Reply> p;
    auto f = p.getFuture();
    ++index_;
    return std::make_tuple(std::move(request), std::move(p), std::move(f));
  }

  folly::dynamic makeConfigOutputs(
                  std::vector<Workload<LucidaService>*> workloads) {
    return folly::dynamic::object;
  }

 private:
  State state_;
  int index_;
};

}  // namespace treadmill
}  // namespace windtunnel
}  // namespace facebook
