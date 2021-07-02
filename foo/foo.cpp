#include "foo.h"

#include <folly/executors/CPUThreadPoolExecutor.h>

#include <iostream>

#include "interface.h"
#include "logger.h"

using namespace std;

foo::foo(zmq::context_t *ctx) : ctx_(ctx) { logger_ = initLogger("foo"); };

foo::~foo() = default;

void foo::subscribe() {
  LOG_INFO(logger_, "subscribe from foo.dll");

  subscriberThread1();
}

// void foo::stop() { exitSignal_.set_value(); }

void foo::subscriberThread1() {
  //  Prepare subscriber
  zmq::socket_t subscriber(*ctx_, zmq::socket_type::sub);
  subscriber.connect("inproc://#1");

  //  Thread2 opens "A" and "B" envelopes
  subscriber.set(zmq::sockopt::subscribe, "A");
  subscriber.set(zmq::sockopt::subscribe, "B");

  size_t nmsg = 5;
  size_t nrx = 0;

  while (1) {
    // Receive all parts of the message
    std::vector<zmq::message_t> recv_msgs;
    zmq::recv_result_t result =
        zmq::recv_multipart(subscriber, std::back_inserter(recv_msgs));
    assert(result && "recv failed");
    assert(*result == 2);

    std::cout << "Thread2: [" << recv_msgs[0].to_string() << "] "
              << recv_msgs[1].to_string() << std::endl;

    if (++nrx == nmsg) {
      std::cout << "exit" << std::endl;
      break;
    }
  }

  LOG_INFO(logger_, "exit subscriber thread");
}

IModule *DYNALO_CALL CreateFoo(zmq::context_t *ctx) { return new foo(ctx); }
