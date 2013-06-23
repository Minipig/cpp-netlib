// Copyright 2011 Dean Michael Berris <dberris@google.com>.
// Copyright 2011 Google, Inc.
// Copyright (c) Glyn Matthews 2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_CONCURRENCY_THREAD_POOL_IPP_20111021
#define NETWORK_CONCURRENCY_THREAD_POOL_IPP_20111021

#include <vector>
#include <thread>
#include <network/concurrency/thread_pool.hpp>
#include <boost/scope_exit.hpp>

namespace network {
  namespace concurrency {

    struct thread_pool::pimpl {
      pimpl(std::size_t threads = 1,
	    io_service_ptr io_service = io_service_ptr(),
	    std::vector<std::thread> worker_threads = std::vector<std::thread>())
	: threads_(threads),
	  io_service_(io_service),
	  worker_threads_(std::move(worker_threads)),
	  sentinel_() {
	bool commit = false;

	BOOST_SCOPE_EXIT((&commit)(&io_service_)(&worker_threads_)(&sentinel_)) {
	  if (!commit) {
	    sentinel_.reset();
	    io_service_.reset();
	    for (auto& thread : worker_threads_) {
	      if (thread.joinable()) {
		thread.join();
	      }
	    }
	    worker_threads_.clear();
	  }
	}
	BOOST_SCOPE_EXIT_END

	if (!io_service_.get()) {
	  io_service_.reset(new boost::asio::io_service);
	}

	if (!sentinel_.get()) {
	  sentinel_.reset(new boost::asio::io_service::work(*io_service_));
	}

	auto local_io_service = io_service_;
	for (std::size_t counter = 0; counter < threads_; ++counter) {
	  worker_threads_.emplace_back([local_io_service]() {
	      local_io_service->run();
	    });
	}

	commit = true;
      }

      ~pimpl() {
	sentinel_.reset();
	try {
	  for (auto& thread : worker_threads_)
	    thread.join();
	}
	catch (...) {
	  BOOST_ASSERT(false &&
		       "A handler was not supposed to throw, but one did.");
	  std::abort();
	}
      }

      std::size_t threads_;
      io_service_ptr io_service_;
      std::vector<std::thread> worker_threads_;
      sentinel_ptr sentinel_;

    };

  thread_pool::thread_pool(std::size_t threads,
			   io_service_ptr io_service,
			   std::vector<std::thread> worker_threads)
    : pimpl_(new (std::nothrow)
	     pimpl(threads, io_service, std::move(worker_threads))) {

  }

  std::size_t const thread_pool::thread_count() const {
    return pimpl_->threads_;
  }

  void thread_pool::post(std::function<void()> f) {
    pimpl_->io_service_->post(f);
  }

  void thread_pool::swap(thread_pool& other) {
    std::swap(other.pimpl_, this->pimpl_);
  }

  thread_pool::~thread_pool() {
    delete pimpl_;
  }
}  // namespace concurrency
}  // namespace network

#endif /* NETWORK_CONCURRENCY_THREAD_POOL_IPP_20111021 */
