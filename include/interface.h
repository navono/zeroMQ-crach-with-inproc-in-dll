#pragma once

#include <folly/concurrency/DynamicBoundedQueue.h>
#include <folly/futures/Future.h>

#include <zmq.hpp>

#include "dynalo/symbol_helper.hpp"

class IModule {
public:
  virtual ~IModule() = default;
  virtual void subscribe() = 0;
};

DYNALO_EXPORT IModule *DYNALO_CALL CreateFoo(zmq::context_t *ctx);
