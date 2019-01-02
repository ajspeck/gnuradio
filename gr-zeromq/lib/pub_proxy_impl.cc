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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "pub_proxy_impl.h"

namespace gr {
  namespace zeromq {

    pub_proxy::sptr
    pub_proxy::make(char *address_in, char *address_out)
    {
      return gnuradio::get_initial_sptr
        (new pub_proxy_impl(address_in, address_out));
    }

    pub_proxy_impl::pub_proxy_impl(char *address_in, char *address_out) 
      : gr::sync_block("pub_proxy", 
                      gr::io_signature::make(0, 0, 0),
                      gr::io_signature::make(0, 0, 0))
    {
  
      /*Create context & socket*/
      d_context = new zmq::context_t(1);
      d_socket_in = new zmq::socket_t(*d_context, ZMQ_SUB);
      d_socket_out = new zmq::socket_t(*d_context, ZMQ_PUB);

      /*Bind and subscribe*/
      d_socket_in->bind(address_in);
      d_socket_in->setsockopt(ZMQ_SUBSCRIBE, "", 0);

      d_socket_out->bind(address_out);

      /*Start proxy*/
      d_proxy_thread = boost::thread{zmq::proxy, (void*)*d_socket_in, (void*)*d_socket_out, nullptr};
    }

    pub_proxy_impl::~pub_proxy_impl(){
      delete d_context;
      delete d_socket_in;
      delete d_socket_out;
    }

  } /* namespace zeromq */
} /* namespace gr */

