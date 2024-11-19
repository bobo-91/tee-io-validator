/**
 *  Copyright Notice:
 *  Copyright 2023-2024 Intel. All rights reserved.
 *  License: BSD 3-Clause License.
 **/

#include <stdlib.h>
#include <ctype.h>

#include "hal/base.h"
#include "hal/library/debuglib.h"

#include "ide_test.h"
#include "helperlib.h"
#include "teeio_debug.h"
#include "cxl_tsp_test_common.h"

bool cxl_tsp_test_config_common_enable(void *test_context)
{
  return true;
}

bool cxl_tsp_test_config_common_disable(void *test_context)
{
  return true;
}

bool cxl_tsp_test_config_common_support(void *test_context)
{
  ide_common_test_config_context_t *config_context = (ide_common_test_config_context_t *)test_context;
  TEEIO_ASSERT(config_context->signature == CONFIG_CONTEXT_SIGNATURE);

  cxl_tsp_test_group_context_t *group_context = (cxl_tsp_test_group_context_t *)config_context->group_context;
  TEEIO_ASSERT(group_context->common.signature == GROUP_CONTEXT_SIGNATURE);

  CXL_PRIV_DATA* rp_cxl_data = &group_context->common.upper_port.cxl_data;
  CXL_PRIV_DATA* ep_cxl_data = &group_context->common.lower_port.cxl_data;

  bool supported = rp_cxl_data->memcache.ide_cap.cxl_ide_capable == 1 && ep_cxl_data->memcache.ide_cap.cxl_ide_capable == 1
                  && ep_cxl_data->ecap.cap.mem_capable == 1
                  && rp_cxl_data->ecap.cap.tsp_capable == 1 && ep_cxl_data->ecap.cap.tsp_capable == 1;

  TEEIO_DEBUG((TEEIO_DEBUG_INFO, "rootport cxl_ide_capable = %d\n", rp_cxl_data->memcache.ide_cap.cxl_ide_capable));
  TEEIO_DEBUG((TEEIO_DEBUG_INFO, "         tsp_capable     = %d\n", rp_cxl_data->ecap.cap.tsp_capable));
  TEEIO_DEBUG((TEEIO_DEBUG_INFO, "endpoint cxl_ide_capable = %d\n", ep_cxl_data->memcache.ide_cap.cxl_ide_capable));
  TEEIO_DEBUG((TEEIO_DEBUG_INFO, "         mem_capable     = %d\n", ep_cxl_data->ecap.cap.mem_capable));
  TEEIO_DEBUG((TEEIO_DEBUG_INFO, "         tsp_capable     = %d\n", ep_cxl_data->ecap.cap.tsp_capable));
  TEEIO_DEBUG((TEEIO_DEBUG_INFO, "cxl_ide_test_config_support_common supported=%d\n", supported));

  teeio_record_config_item_result(IDE_TEST_CONFIGURATION_TYPE_DEFAULT, TEEIO_TEST_CONFIG_FUNC_SUPPORT, supported ? TEEIO_TEST_RESULT_PASS : TEEIO_TEST_RESULT_FAILED); 

  return supported;
}

bool cxl_tsp_test_config_common_check(void *test_context)
{
  return true;
}

