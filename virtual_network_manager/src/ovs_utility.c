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


#include <arpa/inet.h>
#include <assert.h>
#include <inttypes.h>
#include "ovs_utility.h"
#include "trema.h"


static bool
ovs_match_8_to_hex_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint8_t *value = ( const uint8_t * ) header + sizeof( ovs_match_header );
  int ret = snprintf( str, length, "%s = %#x", key, *value );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_8w_to_hex_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint8_t *value = ( const uint8_t * ) header + sizeof( ovs_match_header );
  const uint8_t *mask = value + sizeof( uint8_t );
  int ret = snprintf( str, length, "%s = %#x/%#x", key, *value, *mask );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_16_to_dec_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint16_t *value = ( const uint16_t * ) ( ( const char * ) header + sizeof( ovs_match_header ) );
  int ret = snprintf( str, length, "%s = %u", key, *value );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}

#if OVS_VERSION_CODE >= OVS_VERSION( 1, 6, 0 )
static bool
ovs_match_16w_to_dec_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint16_t *value = ( const uint16_t * ) ( ( const char * ) header + sizeof( ovs_match_header ) );
  const uint16_t *mask = ( const uint16_t * ) ( ( const char * ) value + sizeof( uint16_t ) );
  int ret = snprintf( str, length, "%s = %u/%u", key, *value, *mask );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}
#endif

static bool
ovs_match_16_to_hex_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint16_t *value = ( const uint16_t * ) ( ( const char * ) header + sizeof( ovs_match_header ) );
  int ret = snprintf( str, length, "%s = %#x", key, *value );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_16w_to_hex_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint16_t *value = ( const uint16_t * ) ( ( const char * ) header + sizeof( ovs_match_header ) );
  const uint16_t *mask = ( const uint16_t * ) ( ( const char * ) value + sizeof( uint16_t ) );
  int ret = snprintf( str, length, "%s = %#x/%#x", key, *value, *mask );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_32_to_hex_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint32_t *value = ( const uint32_t * ) ( ( const char * ) header + sizeof( ovs_match_header ) );
  int ret = snprintf( str, length, "%s = %#x", key, *value );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}

#if OVS_VERSION_CODE >= OVS_VERSION( 2, 0, 0 )
static bool
ovs_match_32w_to_hex_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint32_t *value = ( const uint32_t * ) ( ( const char * ) header + sizeof( ovs_match_header ) );
  const uint32_t *mask = ( const uint32_t * ) ( ( const char * ) value + sizeof( uint32_t ) );
  int ret = snprintf( str, length, "%s = %#x/%#x", key, *value, *mask );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}
#endif

static bool
ovs_match_64_to_hex_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint64_t *value = ( const uint64_t * ) ( ( const char * ) header + sizeof( ovs_match_header ) );
  int ret = snprintf( str, length, "%s = %#" PRIx64, key, *value );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_64w_to_hex_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint64_t *value = ( const uint64_t * ) ( ( const char * ) header + sizeof( ovs_match_header ) );
  const uint64_t *mask = ( const uint64_t * ) ( ( const char * ) value + sizeof( uint64_t ) );
  int ret = snprintf( str, length, "%s = %#" PRIx64 "/%#" PRIx64, key, *value, *mask );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_eth_addr_to_hex_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint8_t *addr = ( const uint8_t * ) header + sizeof( ovs_match_header );
  int ret = snprintf( str, length, "%s = %02x:%02x:%02x:%02x:%02x:%02x",
                      key, addr[ 0 ], addr[ 1 ], addr[ 2 ], addr[ 3 ], addr[ 4 ], addr[ 5 ] );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_eth_addr_w_to_hex_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint8_t *addr = ( const uint8_t * ) header + sizeof( ovs_match_header );
  const uint8_t *mask = addr + ( sizeof( uint8_t ) * OFP_ETH_ALEN );
  int ret = snprintf( str, length, "%s = %02x:%02x:%02x:%02x:%02x:%02x/%02x:%02x:%02x:%02x:%02x:%02x",
                      key, addr[ 0 ], addr[ 1 ], addr[ 2 ], addr[ 3 ], addr[ 4 ], addr[ 5 ],
                      mask[ 0 ], mask[ 1 ], mask[ 2 ], mask[ 3 ], mask[ 4 ], mask[ 5 ] );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_ip_addr_to_dec_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint32_t *addr = ( const uint32_t * ) ( ( const uint8_t * ) header + sizeof( ovs_match_header ) );
  int ret = snprintf( str, length, "%s = %u.%u.%u.%u",
                      key, ( *addr >> 24 ) & 0xff, ( *addr >> 16 ) & 0xff, ( *addr >> 8 ) & 0xff, *addr & 0xff );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_ip_addr_w_to_dec_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const uint32_t *addr = ( const uint32_t * ) ( ( const uint8_t * ) header + sizeof( ovs_match_header ) );
  const uint32_t *mask = ( const uint32_t * ) ( ( const uint8_t * ) addr + sizeof( uint32_t ) );

  int ret = snprintf( str, length, "%s = %u.%u.%u.%u/%u.%u.%u.%u",
                      key,
                      ( *addr >> 24 ) & 0xff, ( *addr >> 16 ) & 0xff, ( *addr >> 8 ) & 0xff, *addr & 0xff,
                      ( *mask >> 24 ) & 0xff, ( *mask >> 16 ) & 0xff, ( *mask >> 8 ) & 0xff, *mask & 0xff );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_ipv6_addr_to_hex_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const struct in6_addr *addr = ( const struct in6_addr * ) ( ( const char * ) header + sizeof( ovs_match_header ) );
  char addr_str[ INET6_ADDRSTRLEN ];
  inet_ntop( AF_INET6, addr, addr_str, sizeof( addr_str ) );

  int ret = snprintf( str, length, "%s = %s", key, addr_str );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_ipv6_addr_w_to_hex_string( const ovs_match_header *header, char *str, size_t length, const char *key ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( key != NULL );

  const struct in6_addr *addr = ( const struct in6_addr * ) ( ( const char * ) header + sizeof( ovs_match_header ) );
  const struct in6_addr *mask = ( const struct in6_addr * ) ( ( const char * ) addr + sizeof( struct in6_addr ) );
  char addr_str[ INET6_ADDRSTRLEN ];
  inet_ntop( AF_INET6, addr, addr_str, sizeof( addr_str ) );
  char mask_str[ INET6_ADDRSTRLEN ];
  inet_ntop( AF_INET6, mask, mask_str, sizeof( mask_str ) );

  int ret = snprintf( str, length, "%s = %s/%s", key, addr_str, mask_str );
  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_in_port_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( *header == OVSM_OF_IN_PORT );

  return ovs_match_16_to_dec_string( header, str, length, "in_port" );
}


static bool
ovs_match_eth_addr_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OF_ETH_DST:
      return ovs_match_eth_addr_to_hex_string( header, str, length, "eth_dst" );

    case OVSM_OF_ETH_DST_W:
      return ovs_match_eth_addr_w_to_hex_string( header, str, length, "eth_dst" );

    case OVSM_OF_ETH_SRC:
      return ovs_match_eth_addr_to_hex_string( header, str, length, "eth_src" );

#if OVS_VERSION_CODE >= OVS_VERSION( 1, 8, 0 )
    case OVSM_OF_ETH_SRC_W:
      return ovs_match_eth_addr_w_to_hex_string( header, str, length, "eth_src" );
#endif

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_eth_type_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( *header == OVSM_OF_ETH_TYPE );

  return ovs_match_16_to_hex_string( header, str, length, "eth_type" );
}


static bool
ovs_match_vlan_tci_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OF_VLAN_TCI:
      return ovs_match_16_to_hex_string( header, str, length, "vlan_tci" );

    case OVSM_OF_VLAN_TCI_W:
      return ovs_match_16w_to_hex_string( header, str, length, "vlan_tci" );
      break;

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_ip_tos_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( *header == OVSM_OF_IP_TOS );

  return ovs_match_8_to_hex_string( header, str, length, "ip_tos" );
}


static bool
ovs_match_ip_proto_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( *header == OVSM_OF_IP_PROTO );

  return ovs_match_8_to_hex_string( header, str, length, "ip_proto" );
}


static bool
ovs_match_ip_addr_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OF_IP_SRC:
      return ovs_match_ip_addr_to_dec_string( header, str, length, "ip_src" );

    case OVSM_OF_IP_SRC_W:
      return ovs_match_ip_addr_w_to_dec_string( header, str, length, "ip_src" );

    case OVSM_OF_IP_DST:
      return ovs_match_ip_addr_to_dec_string( header, str, length, "ip_dst" );

    case OVSM_OF_IP_DST_W:
      return ovs_match_ip_addr_w_to_dec_string( header, str, length, "ip_dst" );

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_tcp_port_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OF_TCP_SRC:
      return ovs_match_16_to_dec_string( header, str, length, "tcp_src" );

    case OVSM_OF_TCP_DST:
      return ovs_match_16_to_dec_string( header, str, length, "tcp_dst" );

#if OVS_VERSION_CODE >= OVS_VERSION( 1, 6, 0 )
    case OVSM_OF_TCP_SRC_W:
      return ovs_match_16w_to_dec_string( header, str, length, "tcp_src" );

    case OVSM_OF_TCP_DST_W:
      return ovs_match_16w_to_dec_string( header, str, length, "tcp_dst" );
#endif

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_udp_port_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OF_UDP_SRC:
      return ovs_match_16_to_dec_string( header, str, length, "udp_src" );

    case OVSM_OF_UDP_DST:
      return ovs_match_16_to_dec_string( header, str, length, "udp_dst" );

#if OVS_VERSION_CODE >= OVS_VERSION( 1, 6, 0 )
    case OVSM_OF_UDP_SRC_W:
      return ovs_match_16w_to_dec_string( header, str, length, "udp_src" );

    case OVSM_OF_UDP_DST_W:
      return ovs_match_16w_to_dec_string( header, str, length, "udp_dst" );
#endif

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_icmp_type_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( *header == OVSM_OF_ICMP_TYPE );

  return ovs_match_8_to_hex_string( header, str, length, "icmp_type" );
}


static bool
ovs_match_icmp_code_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( *header == OVSM_OF_ICMP_CODE );

  return ovs_match_8_to_hex_string( header, str, length, "icmp_code" );
}


static bool
ovs_match_arp_op_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( *header == OVSM_OF_ARP_OP );

  return ovs_match_16_to_hex_string( header, str, length, "arp_op" );
}


static bool
ovs_match_arp_pa_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OF_ARP_SPA:
      return ovs_match_ip_addr_to_dec_string( header, str, length, "arp_spa" );

    case OVSM_OF_ARP_SPA_W:
      return ovs_match_ip_addr_w_to_dec_string( header, str, length, "arp_spa" );

    case OVSM_OF_ARP_TPA:
      return ovs_match_ip_addr_to_dec_string( header, str, length, "arp_tpa" );

    case OVSM_OF_ARP_TPA_W:
      return ovs_match_ip_addr_w_to_dec_string( header, str, length, "arp_tpa" );

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_reg_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  int ret = -1;
  const uint32_t *value = ( const uint32_t * ) ( ( const char * ) header + sizeof( ovs_match_header ) );
  const uint32_t *mask = ( const uint32_t * ) ( ( const char * ) value + sizeof( uint32_t ) );
  uint8_t index = get_ovs_match_reg_index( *header );

  switch ( *header ) {
    case OVSM_OVS_REG0:
    case OVSM_OVS_REG1:
    case OVSM_OVS_REG2:
    case OVSM_OVS_REG3:
    case OVSM_OVS_REG4:
#if OVS_VERSION_CODE >= OVS_VERSION( 1, 7, 0 )
    case OVSM_OVS_REG5:
    case OVSM_OVS_REG6:
    case OVSM_OVS_REG7:
#endif
      ret = snprintf( str, length, "reg%u = %#x", index, *value );
      break;

    case OVSM_OVS_REG0_W:
    case OVSM_OVS_REG1_W:
    case OVSM_OVS_REG2_W:
    case OVSM_OVS_REG3_W:
    case OVSM_OVS_REG4_W:
#if OVS_VERSION_CODE >= OVS_VERSION( 1, 7, 0 )
    case OVSM_OVS_REG5_W:
    case OVSM_OVS_REG6_W:
    case OVSM_OVS_REG7_W:
#endif
      ret = snprintf( str, length, "reg%u = %#x/%#x", index, *value, *mask );
      break;

    default:
      assert( 0 );
      break;
  }

  if ( ( ret >= ( int ) length ) || ( ret < 0 ) ) {
    return false;
  }

  return true;
}


static bool
ovs_match_tun_id_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OVS_TUN_ID:
      return ovs_match_64_to_hex_string( header, str, length, "tun_id" );

    case OVSM_OVS_TUN_ID_W:
      return ovs_match_64w_to_hex_string( header, str, length, "tun_id" );

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_arp_ha_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OVS_ARP_SHA:
      return ovs_match_eth_addr_to_hex_string( header, str, length, "arp_sha" );

    case OVSM_OVS_ARP_THA:
      return ovs_match_eth_addr_to_hex_string( header, str, length, "arp_tha" );

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_ipv6_addr_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OVS_IPV6_SRC:
      return ovs_match_ipv6_addr_to_hex_string( header, str, length, "ipv6_src" );

    case OVSM_OVS_IPV6_DST:
      return ovs_match_ipv6_addr_to_hex_string( header, str, length, "ipv6_dst" );

    case OVSM_OVS_IPV6_SRC_W:
      return ovs_match_ipv6_addr_w_to_hex_string( header, str, length, "ipv6_src" );

    case OVSM_OVS_IPV6_DST_W:
      return ovs_match_ipv6_addr_w_to_hex_string( header, str, length, "ipv6_dst" );

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_icmpv6_type_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( *header == OVSM_OVS_ICMPV6_TYPE );

  return ovs_match_8_to_hex_string( header, str, length, "icmpv6_type" );
}


static bool
ovs_match_icmpv6_code_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( *header == OVSM_OVS_ICMPV6_CODE );

  return ovs_match_8_to_hex_string( header, str, length, "icmpv6_code" );
}


static bool
ovs_match_nd_target_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OVS_ND_TARGET:
      return ovs_match_ipv6_addr_to_hex_string( header, str, length, "nd_target" );

#if OVS_VERSION_CODE >= OVS_VERSION( 1, 7, 0 )
    case OVSM_OVS_ND_TARGET_W:
      return ovs_match_ipv6_addr_w_to_hex_string( header, str, length, "nd_target" );
#endif

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_nd_ll_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OVS_ND_SLL:
      return ovs_match_eth_addr_to_hex_string( header, str, length, "nd_sll" );

    case OVSM_OVS_ND_TLL:
      return ovs_match_eth_addr_to_hex_string( header, str, length, "nd_tll" );

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_ip_frag_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OVS_IP_FRAG:
      return ovs_match_8_to_hex_string( header, str, length, "ip_frag" );

    case OVSM_OVS_IP_FRAG_W:
      return ovs_match_8w_to_hex_string( header, str, length, "ip_frag" );

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_ipv6_label_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( *header == OVSM_OVS_IPV6_LABEL );

  switch( *header ) {
    case OVSM_OVS_IPV6_LABEL:
      return ovs_match_32_to_hex_string( header, str, length, "ipv6_label" );

#if OVS_VERSION_CODE >= OVS_VERSION( 2, 1, 0 )
    case OVSM_OVS_IPV6_LABEL_W:
      return ovs_match_32w_to_hex_string( header, str, length, "ipv6_label" );
#endif

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_ip_ecn_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( *header == OVSM_OVS_IP_ECN );

  return ovs_match_8_to_hex_string( header, str, length, "ip_ecn" );
}


static bool
ovs_match_ip_ttl_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );
  assert( *header == OVSM_OVS_IP_TTL );

  return ovs_match_8_to_hex_string( header, str, length, "ip_ttl" );
}


#if OVS_VERSION_CODE >= OVS_VERSION( 1, 5, 0 )
static bool
ovs_match_cookie_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OVS_COOKIE:
      return ovs_match_64_to_hex_string( header, str, length, "cookie" );

    case OVSM_OVS_COOKIE_W:
      return ovs_match_64w_to_hex_string( header, str, length, "cookie" );

    default:
      assert( 0 );
      break;
  }

  return false;
}
#endif

#if OVS_VERSION_CODE >= OVS_VERSION( 2, 0, 0 )
static bool
ovs_match_tun_ipv4_addr_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OVS_TUN_IPV4_SRC:
      return ovs_match_ip_addr_to_dec_string( header, str, length, "tun_ipv4_src" );

    case OVSM_OVS_TUN_IPV4_SRC_W:
      return ovs_match_ip_addr_w_to_dec_string( header, str, length, "tun_ipv4_src" );

    case OVSM_OVS_TUN_IPV4_DST:
      return ovs_match_ip_addr_to_dec_string( header, str, length, "tun_ipv4_dst" );

    case OVSM_OVS_TUN_IPV4_DST_W:
      return ovs_match_ip_addr_w_to_dec_string( header, str, length, "tun_ipv4_dst" );

    default:
      assert( 0 );
      break;
  }

  return false;
}


static bool
ovs_match_pkt_mark_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OVS_PKT_MARK:
      return ovs_match_32_to_hex_string( header, str, length, "pkt_mark" );

    case OVSM_OVS_PKT_MARK_W:
      return ovs_match_32w_to_hex_string( header, str, length, "pkt_mark" );

    default:
      assert( 0 );
      break;
  }

  return false;
}
#endif

#if OVS_VERSION_CODE >= OVS_VERSION( 2, 1, 0 )
static bool
ovs_match_tcp_flags_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  switch ( *header ) {
    case OVSM_OVS_TCP_FLAGS:
      return ovs_match_16_to_hex_string( header, str, length, "tcp_flags" );

    case OVSM_OVS_TCP_FLAGS_W:
      return ovs_match_16w_to_hex_string( header, str, length, "tcp_flags" );

    default:
      assert( 0 );
      break;
  }

  return false;
}
#endif

static bool
ovs_match_to_string( const ovs_match_header *header, char *str, size_t length ) {
  assert( header != NULL );
  assert( str != NULL );
  assert( length > 0 );

  bool ret = true;

  switch ( *header ) {
    case OVSM_OF_IN_PORT:
      ret = ovs_match_in_port_to_string( header, str, length );
      break;

    case OVSM_OF_ETH_DST:
    case OVSM_OF_ETH_DST_W:
    case OVSM_OF_ETH_SRC:
#if OVS_VERSION_CODE >= OVS_VERSION( 1, 8, 0 )
    case OVSM_OF_ETH_SRC_W:
#endif
      ret = ovs_match_eth_addr_to_string( header, str, length );
      break;

    case OVSM_OF_ETH_TYPE:
      ret = ovs_match_eth_type_to_string( header, str, length );
      break;

    case OVSM_OF_VLAN_TCI:
    case OVSM_OF_VLAN_TCI_W:
      ret = ovs_match_vlan_tci_to_string( header, str, length );
      break;

    case OVSM_OF_IP_TOS:
      ret = ovs_match_ip_tos_to_string( header, str, length );
      break;

    case OVSM_OF_IP_PROTO:
      ret = ovs_match_ip_proto_to_string( header, str, length );
      break;

    case OVSM_OF_IP_SRC:
    case OVSM_OF_IP_SRC_W:
    case OVSM_OF_IP_DST:
    case OVSM_OF_IP_DST_W:
      ret = ovs_match_ip_addr_to_string( header, str, length );
      break;

    case OVSM_OF_TCP_SRC:
    case OVSM_OF_TCP_DST:
#if OVS_VERSION_CODE >= OVS_VERSION( 1, 6, 0 )
    case OVSM_OF_TCP_SRC_W:
    case OVSM_OF_TCP_DST_W:
#endif
      ret = ovs_match_tcp_port_to_string( header, str, length );
      break;

    case OVSM_OF_UDP_SRC:
    case OVSM_OF_UDP_DST:
#if OVS_VERSION_CODE >= OVS_VERSION( 1, 6, 0 )
    case OVSM_OF_UDP_SRC_W:
    case OVSM_OF_UDP_DST_W:
#endif
      ret = ovs_match_udp_port_to_string( header, str, length );
      break;

    case OVSM_OF_ICMP_TYPE:
      ret = ovs_match_icmp_type_to_string( header, str, length );
      break;

    case OVSM_OF_ICMP_CODE:
      ret = ovs_match_icmp_code_to_string( header, str, length );
      break;

    case OVSM_OF_ARP_OP:
      ret = ovs_match_arp_op_to_string( header, str, length );
      break;

    case OVSM_OF_ARP_SPA:
    case OVSM_OF_ARP_SPA_W:
    case OVSM_OF_ARP_TPA:
    case OVSM_OF_ARP_TPA_W:
      ret = ovs_match_arp_pa_to_string( header, str, length );
      break;

    case OVSM_OVS_REG0:
    case OVSM_OVS_REG0_W:
    case OVSM_OVS_REG1:
    case OVSM_OVS_REG1_W:
    case OVSM_OVS_REG2:
    case OVSM_OVS_REG2_W:
    case OVSM_OVS_REG3:
    case OVSM_OVS_REG3_W:
    case OVSM_OVS_REG4:
    case OVSM_OVS_REG4_W:
#if OVS_VERSION_CODE >= OVS_VERSION( 1, 7, 0 )
    case OVSM_OVS_REG5:
    case OVSM_OVS_REG5_W:
    case OVSM_OVS_REG6:
    case OVSM_OVS_REG6_W:
    case OVSM_OVS_REG7:
    case OVSM_OVS_REG7_W:
#endif
      ret = ovs_match_reg_to_string( header, str, length );
      break;

    case OVSM_OVS_TUN_ID:
    case OVSM_OVS_TUN_ID_W:
      ret = ovs_match_tun_id_to_string( header, str, length );
      break;

    case OVSM_OVS_ARP_SHA:
    case OVSM_OVS_ARP_THA:
      ret = ovs_match_arp_ha_to_string( header, str, length );
      break;

    case OVSM_OVS_IPV6_SRC:
    case OVSM_OVS_IPV6_SRC_W:
    case OVSM_OVS_IPV6_DST:
    case OVSM_OVS_IPV6_DST_W:
      ret = ovs_match_ipv6_addr_to_string( header, str, length );
      break;

    case OVSM_OVS_ICMPV6_TYPE:
      ret = ovs_match_icmpv6_type_to_string( header, str, length );
      break;

    case OVSM_OVS_ICMPV6_CODE:
      ret = ovs_match_icmpv6_code_to_string( header, str, length );
      break;

    case OVSM_OVS_ND_TARGET:
#if OVS_VERSION_CODE >= OVS_VERSION( 1, 7, 0 )
    case OVSM_OVS_ND_TARGET_W:
#endif
      ret = ovs_match_nd_target_to_string( header, str, length );
      break;

    case OVSM_OVS_ND_SLL:
    case OVSM_OVS_ND_TLL:
      ret = ovs_match_nd_ll_to_string( header, str, length );
      break;

    case OVSM_OVS_IP_FRAG:
    case OVSM_OVS_IP_FRAG_W:
      ret = ovs_match_ip_frag_to_string( header, str, length );
      break;

    case OVSM_OVS_IPV6_LABEL:
#if OVS_VERSION_CODE >= OVS_VERSION( 2, 1, 0 )
    case OVSM_OVS_IPV6_LABEL_W:
#endif
      ret = ovs_match_ipv6_label_to_string( header, str, length );
      break;

    case OVSM_OVS_IP_ECN:
      ret = ovs_match_ip_ecn_to_string( header, str, length );
      break;

    case OVSM_OVS_IP_TTL: 
      ret = ovs_match_ip_ttl_to_string( header, str, length );
      break;

#if OVS_VERSION_CODE >= OVS_VERSION( 1, 5, 0 )
    case OVSM_OVS_COOKIE:
    case OVSM_OVS_COOKIE_W:
      ret = ovs_match_cookie_to_string( header, str, length );
      break;
#endif

#if OVS_VERSION_CODE >= OVS_VERSION( 2, 0, 0 )
    case OVSM_OVS_TUN_IPV4_SRC:
    case OVSM_OVS_TUN_IPV4_SRC_W:
    case OVSM_OVS_TUN_IPV4_DST:
    case OVSM_OVS_TUN_IPV4_DST_W:
      ret = ovs_match_tun_ipv4_addr_to_string( header, str, length );
      break;

    case OVSM_OVS_PKT_MARK:
    case OVSM_OVS_PKT_MARK_W:
      ret = ovs_match_pkt_mark_to_string( header, str, length );
      break;
#endif

#if OVS_VERSION_CODE >= OVS_VERSION( 2, 1, 0 )
    case OVSM_OVS_TCP_FLAGS:
    case OVSM_OVS_TCP_FLAGS_W:
      ret = ovs_match_tcp_flags_to_string( header, str, length );
      break;
#endif

    default:
    {
      ret = false;
      error( "Undefined match type ( header = %#x, type = %#x, has_mask = %u, length = %u ).",
             *header, get_ovs_match_type( *header ), ovs_match_has_mask( *header ), get_ovs_match_length( *header ) );
    }
    break;
  }

  return ret;
}


bool
ovs_matches_to_string( const ovs_matches *matches, char *str, size_t length ) {
  assert( matches );
  assert( str != NULL );
  assert( length > 0 );

  memset( str, '\0', length );

  bool ret = true;
  if ( matches->n_matches > 0 ) {
    for ( list_element *e = matches->list; e != NULL; e = e->next ) {
      size_t current_length = strlen( str );
      size_t remaining_length = length - current_length;
      if ( current_length > 0 && remaining_length > 2 ) {
        snprintf( str + current_length, remaining_length, ", " );
        remaining_length -= 2;
        current_length += 2;
      }
      char *p = str + current_length;
      const ovs_match_header *header = e->data;
      ret = ovs_match_to_string( header, p, remaining_length );
      if ( !ret ) {
        break;
      }
    }
  }
  else {
    snprintf( str, length, "all" );
  }

  str[ length - 1 ] = '\0';

  return ret;
}


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */
