//
// Copyright (c) 2022 ZettaScale Technology
//
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// http://www.eclipse.org/legal/epl-2.0, or the Apache License, Version 2.0
// which is available at https://www.apache.org/licenses/LICENSE-2.0.
//
// SPDX-License-Identifier: EPL-2.0 OR Apache-2.0
//
// Contributors:
//   ZettaScale Zenoh Team, <zenoh@zettascale.tech>
//

#include "zenoh-pico/transport/common/lease.h"

#include <stddef.h>

#include "zenoh-pico/transport/multicast/lease.h"
#include "zenoh-pico/transport/unicast/lease.h"

int8_t _z_send_keep_alive(_z_transport_t *zt) {
    int8_t ret = _Z_RES_OK;
    switch (zt->_type) {
        case _Z_TRANSPORT_UNICAST_TYPE:
            ret = _zp_unicast_send_keep_alive(&zt->_transport._unicast);
            break;
        case _Z_TRANSPORT_MULTICAST_TYPE:
            ret = _zp_multicast_send_keep_alive(&zt->_transport._multicast);
            break;
        default:
            ret = _Z_ERR_TRANSPORT_NOT_AVAILABLE;
            break;
    }
    return ret;
}

void *_zp_lease_task(void *zt_arg) {
    void *ret = NULL;
    _z_transport_t *zt = (_z_transport_t *)zt_arg;
    switch (zt->_type) {
        case _Z_TRANSPORT_UNICAST_TYPE:
            ret = _zp_unicast_lease_task(&zt->_transport._unicast);
            break;
        case _Z_TRANSPORT_MULTICAST_TYPE:
            ret = _zp_multicast_lease_task(&zt->_transport._multicast);
            break;
        default:
            ret = NULL;
            break;
    }
    return ret;
}
