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

#include <folly/MoveWrapper.h>
#include <folly/fibers/EventBaseLoopController.h>
#include <folly/fibers/FiberManager.h>
#include <folly/futures/Future.h>
#include <folly/io/async/EventBase.h>
#include <folly/io/IOBuf.h>

#include "treadmill/Connection.h"
#include "treadmill/StatisticsManager.h"
#include "treadmill/Util.h"
#include "treadmill/services/lucida/LucidaService.h"

#include <curl/curl.h>

DECLARE_string(hostname);
DECLARE_int32(port);

using folly::fibers::EventBaseLoopController;
using folly::fibers::FiberManager;

namespace facebook {
namespace windtunnel {
namespace treadmill {

template <>
class Connection<LucidaService> {
 public:
  explicit Connection<LucidaService>(folly::EventBase& event_base) {

  }

  bool isReady() const { return true; }

  folly::Future<LucidaService::Reply>
  sendRequest(std::unique_ptr<typename LucidaService::Request> request) {
    folly::MoveWrapper<folly::Promise<LucidaService::Reply> > p;
    auto f = p->getFuture();
    sendGetRequest();
    p->setValue(LucidaService::Reply());
    return f;
  }

 private:
  void sendGetRequest() const {
    CURL *curl;
    CURLcode res;
   
    struct curl_httppost *formpost=NULL;
    struct curl_httppost *lastptr=NULL;
    struct curl_slist *headerlist=NULL;
    static const char buf[] = "Expect:";
   
    curl_global_init(CURL_GLOBAL_ALL);
   
    /* Fill in the file upload field */ 
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "file",
                 CURLFORM_FILE, "/home/yba/Documents/lucida/lucida/imagematching/opencv_imm/test/test_db/golden-gate.jpg",
                 CURLFORM_END);
   
    /* Fill in the filename field */ 
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "label",
                 CURLFORM_COPYCONTENTS, "postit2.cpp",
                 CURLFORM_END);

    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "op",
                 CURLFORM_COPYCONTENTS, "add_image",
                 CURLFORM_END);

    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "username",
                 CURLFORM_COPYCONTENTS, "yba",
                 CURLFORM_END);

    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "password",
                 CURLFORM_COPYCONTENTS, "cookies0",
                 CURLFORM_END);
   
   
    /* Fill in the submit field too, even if this is rarely needed */ 
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "submit",
                 CURLFORM_COPYCONTENTS, "send",
                 CURLFORM_END);
   
    curl = curl_easy_init();
    /* initialize custom header list (stating that Expect: 100-continue is not
       wanted */ 
    headerlist = curl_slist_append(headerlist, buf);
    if(curl) {
      /* what URL that receives this POST */ 
       curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/login");
       curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "/home/yba/Documents/lucida/tools/treadmill/try/AAAAA.txt");
       //curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt"); /* start cookie engine */ 
      curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
   
      /* Perform the request, res will get the return code */ 

      res = curl_easy_perform(curl);

      // curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/learn");
      // res = curl_easy_perform(curl);

      //print_cookies(curl);
      /* Check for errors */ 
      if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
      }
   
      /* always cleanup */ 
      curl_easy_cleanup(curl);
   
      /* then cleanup the formpost chain */ 
      curl_formfree(formpost);
      /* free slist */ 
      curl_slist_free_all(headerlist);
    }
  }
};

} // namespace treadmill
} // namespace windtunnel
} // namespace facebook
