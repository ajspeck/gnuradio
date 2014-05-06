/* -*- c++ -*- */
/*
 * Copyright 2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "pdu_filter_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/blocks/pdu.h>

namespace gr {
  namespace blocks {

    pdu_filter::sptr
    pdu_filter::make(pmt::pmt_t k, pmt::pmt_t v)
    {
      return gnuradio::get_initial_sptr(new pdu_filter_impl(k,v));
    }

    pdu_filter_impl::pdu_filter_impl(pmt::pmt_t k, pmt::pmt_t v)
      :	block("pdu_filter",
		 io_signature::make (0, 0, 0),
		 io_signature::make (0, 0, 0)),
    d_k(k), d_v(v)
    {
      message_port_register_out(pmt::mp("pdus"));
      message_port_register_in(pmt::mp("pdus"));
      set_msg_handler(pmt::mp("pdus"), boost::bind(&pdu_filter_impl::handle_msg, this, _1));
    }

    void 
    pdu_filter_impl::handle_msg(pmt::pmt_t pdu)
    {
      pmt::pmt_t meta = pmt::car(pdu);

      // discard if meta is not a dict
      if(!pmt::is_dict(meta))
        return;

      // make sure the dict has the target key
      if(!dict_has_key(meta, d_k))
        return;

      // validate the value matches
      if(!pmt::eqv(pmt::dict_ref(meta,d_k,pmt::PMT_NIL), d_v))
        return;

      // if all tests pass, propagate the pdu
      message_port_pub(pmt::mp("pdus"), pdu);
    }
      
  } /* namespace blocks */
}/* namespace gr */
