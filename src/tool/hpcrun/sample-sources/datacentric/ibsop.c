// -*-Mode: C++;-*- // technically C99

// * BeginRiceCopyright *****************************************************
//
// $HeadURL$
// $Id$
//
// --------------------------------------------------------------------------
// Part of HPCToolkit (hpctoolkit.org)
//
// Information about sources of support for research and development of
// HPCToolkit is at 'hpctoolkit.org' and in 'README.Acknowledgments'.
// --------------------------------------------------------------------------
//
// Copyright ((c)) 2002-2017, Rice University
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
//
// * Neither the name of Rice University (RICE) nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// This software is provided by RICE and contributors "as is" and any
// express or implied warranties, including, but not limited to, the
// implied warranties of merchantability and fitness for a particular
// purpose are disclaimed. In no event shall RICE or contributors be
// liable for any direct, indirect, incidental, special, exemplary, or
// consequential damages (including, but not limited to, procurement of
// substitute goods or services; loss of use, data, or profits; or
// business interruption) however caused and on any theory of liability,
// whether in contract, strict liability, or tort (including negligence
// or otherwise) arising in any way out of the use of this software, even
// if advised of the possibility of such damage.
//
// ******************************************************* EndRiceCopyright *

#include <stdio.h>

#include <hpcrun/messages/messages.h>
#include "sample-sources/perf/perf-util.h"

#include "datacentric.h"

#define IBS_OP_TYPE_FILE "/sys/bus/event_source/devices/ibs_op/type"

int
datacentric_hw_register(event_info_t *event_desc, struct event_threshold_s *period)
{
  // get the type of ibs op

  FILE *ibs_file = fopen(IBS_OP_TYPE_FILE, "r");
  u32 type;

  if (!ibs_file) {
    EMSG("Cannot open file: %s", IBS_OP_TYPE_FILE);
    return 0;
  }
  fscanf(ibs_file, "%d", &type);

  event_desc->attr.config = (1ULL<<19);
  event_desc->attr.type   = type;
  event_desc->attr.sample_period  = period->threshold_num;
  event_desc->attr.freq           = period->threshold_type == FREQUENCY ? 1 : 0;

  event_desc->attr.sample_type    = PERF_SAMPLE_RAW
                                    | PERF_SAMPLE_PERIOD | PERF_SAMPLE_TIME
                                    | PERF_SAMPLE_IP     | PERF_SAMPLE_ADDR
                                    | PERF_SAMPLE_CPU    | PERF_SAMPLE_TID;
  event_desc->attr.disabled       = 1;
  event_desc->attr.exclude_kernel = 0;
  event_desc->attr.exclude_user   = 0;
  event_desc->attr.exclude_hv     = 0;
  event_desc->attr.exclude_guest  = 0;
  event_desc->attr.exclude_idle   = 0;
  event_desc->attr.exclude_host   = 0;
  event_desc->attr.pinned         = 0;
  event_desc->attr.precise_ip     = 1;
  event_desc->attr.mmap           = 1;

  event_desc->attr.sample_id_all = 1;
  event_desc->attr.read_format = 0;

  return 1;
}
