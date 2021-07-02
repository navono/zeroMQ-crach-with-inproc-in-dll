#pragma once

#include <folly/futures/Future.h>
#include <quill/Quill.h>

#include <future>
#include <zmq.hpp>
#include <zmq_addon.hpp>

#include "dynalo/symbol_helper.hpp"
#include "interface.h"

class foo : public IModule {
public:
  explicit foo(zmq::context_t *ctx);
  ~foo() override;

  void subscribe() override;

private:
  void subscriberThread1();

private:
  std::shared_ptr<quill::Logger> logger_;
  std::promise<void> exitSignal_;

  //  std::shared_ptr<zmq::context_t> ctx_;
  zmq::context_t *ctx_;
};
