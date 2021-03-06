/*
 * Author: Yasunobu Chiba
 *
 * Copyright (C) 2012-2013 NEC Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H


#include <netinet/in.h>
#include <stdint.h>
#include "linked_list.h"


void *distributor_main( void *args );
bool add_tunnel_endpoint( uint32_t vni, struct in_addr ip_addr, uint16_t port );
bool set_tunnel_endpoint_port( uint32_t vni, struct in_addr ip_addr, uint16_t port );
list *lookup_tunnel_endpoints( uint32_t vni );
list *get_all_tunnel_endpoints();
bool delete_tunnel_endpoint( uint32_t vni, struct in_addr ip_addr );


#endif // DISTRIBUTOR_H


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */


