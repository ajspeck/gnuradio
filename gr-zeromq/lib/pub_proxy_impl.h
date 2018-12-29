/* -*- c++ -*- */
/*
 * Copyright 2013,2014 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_ZEROMQ_PUB_PROXY_IMPL_H
#define INCLUDED_ZEROMQ_PUB_PROXY_IMPL_H

#include <gnuradio/zeromq/pub_proxy.h>
#include <zmq.hpp>

#include <boost/thread.hpp>

namespace gr {
  namespace zeromq {

    class pub_proxy_impl : public pub_proxy 
    {
      private:
        zmq::socket_t   *d_socket_in;
        zmq::socket_t   *d_socket_out;
        zmq::context_t  *d_context;

        boost::thread   d_proxy_thread;

    public:
      pub_proxy_impl(char *address_in, char *address_out);
      virtual ~pub_proxy_impl();

      int work(int noutput_items,
               gr_vector_const_void_star &input_items,
               gr_vector_void_star &output_items) {return noutput_items;};
    };

  } // namespace zeromq
} // namespace gr

#endif /* INCLUDED_ZEROMQ_PUB_PROXY_IMPL_H */
