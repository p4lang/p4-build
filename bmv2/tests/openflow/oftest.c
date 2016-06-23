/* Copyright 2013-present Barefoot Networks, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <bm/pdfixed/pd_static.h>
#include <bm/pdfixed/pd_pre.h>
#include <bm/pdfixed/pd_mirroring.h>

#include <pd/pd_tables.h>
#include <pd/pd_meters.h>
#include <pd/pd_counters.h>
#include <pd/pd_registers.h>
#include <pd/pd.h>

#include <plugin/of/inc/openflow.h>

#define DEVICE_THRIFT_PORT 9090

extern int c_start_server();

int main() {
  c_start_server();

  p4_pd_init();

  p4_pd_dev_target_t dev_tgt = {0, 0xFF};
  p4_pd_entry_hdl_t entry_hdl;

  /* P4 dependent initialization */
  p4_pd_oftest_init();
  p4_pd_oftest_assign_device(dev_tgt.device_id, NULL, DEVICE_THRIFT_PORT);
  
  p4_pd_sess_hdl_t sess_hdl;
  p4_pd_client_init(&sess_hdl);
  
  // just a couple random calls into the library to make sure it works
  ofpat_pipeline_key_t junk_key;
  memset (&junk_key, 0, sizeof(junk_key));
  
  uint64_t junk_index = 4326;
  uint16_t junk_egr_port = 2;

  ofpat_pipeline_key_new(&junk_index, NULL, &junk_egr_port, &junk_key);

  return 0;
}
