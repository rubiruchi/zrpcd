/*
 * AUTOGENERATED FILE - DO NOT EDIT
 * derived from GPLv2+ sources
 *
 * Copyright (c) 2016 6WIND,
 * This file is part of ZRPC daemon.
 * See the LICENSE file.
 */

#ifndef _ZRPC_BGP_CAPNP_H
#define _ZRPC_BGP_CAPNP_H

/* union sockunion.  */
#include "zrpcd/zrpc_util.h"
#include "zrpcd/qzcclient.h"


#define BGP_MAX_LABELS 1

/* BGP instance structure.  */
struct bgp 
{
  /* AS number of this BGP instance.  */
  uint32_t as;

  /* Name of this BGP instance.  */
  char *name;
  
  /* BGP router ID */
  struct in_addr router_id_static;

  /* flags for BGP configuration */
  u_int32_t flags;
#define BGP_FLAG_ALWAYS_COMPARE_MED       (1 << 0)
#define BGP_FLAG_DETERMINISTIC_MED        (1 << 1)
#define BGP_FLAG_MED_MISSING_AS_WORST     (1 << 2)
#define BGP_FLAG_MED_CONFED               (1 << 3)
#define BGP_FLAG_NO_DEFAULT_IPV4          (1 << 4)
#define BGP_FLAG_NO_CLIENT_TO_CLIENT      (1 << 5)
#define BGP_FLAG_ENFORCE_FIRST_AS         (1 << 6)
#define BGP_FLAG_COMPARE_ROUTER_ID        (1 << 7)
#define BGP_FLAG_ASPATH_IGNORE            (1 << 8)
#define BGP_FLAG_IMPORT_CHECK             (1 << 9)
#define BGP_FLAG_NO_FAST_EXT_FAILOVER     (1 << 10)
#define BGP_FLAG_LOG_NEIGHBOR_CHANGES     (1 << 11)
#define BGP_FLAG_GRACEFUL_RESTART         (1 << 12)
#define BGP_FLAG_ASPATH_CONFED            (1 << 13)
#define BGP_FLAG_ASPATH_MULTIPATH_RELAX   (1 << 14)
#define BGP_FLAG_DELETING                 (1 << 15) /* not taken into account */
#define BGP_FLAG_RR_ALLOW_OUTBOUND_POLICY (1 << 16) /* not taken into account */
#define BGP_FLAG_GR_PRESERVE_FWD          (1 << 17)
#define BGP_FLAG_BFD_SYNC                 (1 << 18)
#define BGP_FLAG_BFD_MULTIHOP             (1 << 19)

  /* BGP Per AF flags */
  u_int16_t af_flags[ADDRESS_FAMILY_MAX][SUBSEQUENT_ADDRESS_FAMILY_MAX];
#define BGP_CONFIG_DAMPENING              (1 << 0)
#define BGP_CONFIG_ASPATH_MULTIPATH_RELAX (1 << 1)
#define BGP_CONFIG_MULTIPATH              (1 << 2)

  /* BGP distance configuration.  */
  u_char distance_ebgp;
  u_char distance_ibgp;
  u_char distance_local;

  /* BGP default local-preference.  */
  u_int32_t default_local_pref;

  /* BGP default timer.  */
  u_int32_t default_holdtime;
  u_int32_t default_keepalive;

  /* BGP graceful restart */
  u_int32_t restart_time;
  u_int32_t stalepath_time;

  /* outbound update feeds */
  char *notify_zmq_url;

  char *logFile;
  char *logLevel;
  char *logLevelSyslog;

#define MAX_EOR_UPDATE_DELAY 3600
  u_int16_t v_update_delay;
};

typedef enum
{
  ZRPC_BGP_LAYER_TYPE_2 = 1,
  ZRPC_BGP_LAYER_TYPE_3 = 2
} bgp_layer_type_t;

struct bgp_vrf
{
  struct bgp *bgp;

  /* RD used for route advertisements */
  struct zrpc_rd_prefix outbound_rd;

  /* import and export lists */
  struct zrpc_rdrt *rt_import;
  struct zrpc_rdrt *rt_export;

  /* labels of Route Distinguishers */
  uint32_t labels[BGP_MAX_LABELS];
  size_t nlabels;

  /* maximum multipath entries for the VRF */
  uint32_t max_mpath;

  /* ZRPC_BGP_LAYER_TYPE_2 or TYPE_3 */
  bgp_layer_type_t ltype;
};

struct bgp_event_vrf
{
#define BGP_EVENT_MASK_ANNOUNCE 0x1
#define BGP_EVENT_SHUT 0x2
  uint8_t announce;
  struct zrpc_rd_prefix outbound_rd; /* dummy for event_shut */
  struct zrpc_prefix prefix; /* alias subtype */
  struct zrpc_prefix nexthop; /* alias peer */
  uint32_t label; /* alias type */
  uint32_t ethtag;
  char *esi;
  char *mac_router;
  uint32_t l2label;
  char *gatewayIp;
};

struct bgp_event_shut
{
  struct zrpc_prefix peer;
  uint8_t type, subtype;
};

struct bgp_api_route
{
  struct zrpc_prefix prefix;
  struct zrpc_prefix nexthop;
  uint32_t label;
  uint32_t ethtag;
  uint32_t l2label; /* alias information on labeled unicast */
  char *esi;
  char *mac_router;
  struct zrpc_prefix gatewayIp;
};

/* BGP neighbor structure. */
struct peer
{
  /* Peer's remote AS number. */
  uint32_t as;			

  /* Printable address of the peer. */
  char *host;

  char *desc;			/* Description of the peer. */

  unsigned short port;          /* Destination port for peer */

  u_int32_t weight;
  u_int32_t holdtime;
  u_int32_t keepalive;

  /* Global configuration flags. */
  u_int32_t flags;
#define PEER_FLAG_PASSIVE                   (1 << 0) /* passive mode */
#define PEER_FLAG_SHUTDOWN                  (1 << 1) /* shutdown */
#define PEER_FLAG_DONT_CAPABILITY           (1 << 2) /* dont-capability */
#define PEER_FLAG_OVERRIDE_CAPABILITY       (1 << 3) /* override-capability */
#define PEER_FLAG_STRICT_CAP_MATCH          (1 << 4) /* strict-match */
#define PEER_FLAG_DYNAMIC_CAPABILITY        (1 << 5) /* dynamic capability */
#define PEER_FLAG_DISABLE_CONNECTED_CHECK   (1 << 6) /* disable-connected-check */
#define PEER_FLAG_LOCAL_AS_NO_PREPEND       (1 << 7) /* local-as no-prepend */
#define PEER_FLAG_LOCAL_AS_REPLACE_AS       (1 << 8) /* local-as no-prepend replace-as */
#define PEER_FLAG_USE_CONFIGURED_SOURCE     (1 << 9) /* use configured source-only */
#define PEER_FLAG_MULTIHOP                  (1 << 10) /* multihop */
#define PEER_FLAG_BFD                       (1 << 11) /* fall-over bfd */
#define PEER_FLAG_BFD_SYNC                  (1 << 12) /* fall-over bfd sync */

  int ttl;			/* TTL of TCP connection to the peer. */

  char *update_source;

  u_char afc[ADDRESS_FAMILY_MAX][SUBSEQUENT_ADDRESS_FAMILY_MAX];

  /* Per AF configuration flags. */
  u_int32_t af_flags[ADDRESS_FAMILY_MAX][SUBSEQUENT_ADDRESS_FAMILY_MAX];
#define PEER_FLAG_SEND_COMMUNITY            (1 << 0) /* send-community */
#define PEER_FLAG_SEND_EXT_COMMUNITY        (1 << 1) /* send-community ext. */
#define PEER_FLAG_NEXTHOP_SELF              (1 << 2) /* next-hop-self */
#define PEER_FLAG_REFLECTOR_CLIENT          (1 << 3) /* reflector-client */
#define PEER_FLAG_RSERVER_CLIENT            (1 << 4) /* route-server-client */
#define PEER_FLAG_SOFT_RECONFIG             (1 << 5) /* soft-reconfiguration */
#define PEER_FLAG_AS_PATH_UNCHANGED         (1 << 6) /* transparent-as */
#define PEER_FLAG_NEXTHOP_UNCHANGED         (1 << 7) /* transparent-next-hop */
#define PEER_FLAG_MED_UNCHANGED             (1 << 8) /* transparent-next-hop */
#define PEER_FLAG_DEFAULT_ORIGINATE         (1 << 9) /* default-originate */
#define PEER_FLAG_REMOVE_PRIVATE_AS         (1 << 10) /* remove-private-as */
#define PEER_FLAG_ALLOWAS_IN                (1 << 11) /* set allowas-in */
#define PEER_FLAG_ORF_PREFIX_SM             (1 << 12) /* orf capability send-mode */
#define PEER_FLAG_ORF_PREFIX_RM             (1 << 13) /* orf capability receive-mode */
#define PEER_FLAG_MAX_PREFIX                (1 << 14) /* maximum prefix */
#define PEER_FLAG_MAX_PREFIX_WARNING        (1 << 15) /* maximum prefix warning-only */
#define PEER_FLAG_NEXTHOP_LOCAL_UNCHANGED   (1 << 16) /* leave link-local nexthop unchanged */
#define PEER_FLAG_NEXTHOP_SELF_ALL          (1 << 17) /* next-hop-self all */

  /* allowas-in. */
  char allowas_in[ADDRESS_FAMILY_MAX][SUBSEQUENT_ADDRESS_FAMILY_MAX];
  /* BGP peer status */
  uint8_t status;
#define BGP_PEER_STATUS_UP      0
#define BGP_PEER_STATUS_DOWN    1
#define BGP_PEER_STATUS_UNKNOWN 2
};

/* BGP graceful restart  */
#define BGP_DEFAULT_RESTART_TIME               120
#define BGP_DEFAULT_STALEPATH_TIME             360

#define  CAPN_BGPVRF_ROUTE_DEF_SIZE  12


capn_ptr qcapn_new_BGP(struct capn_segment *s);

capn_ptr qcapn_new_AfiKey(struct capn_segment *s);

void qcapn_BGP_read(struct bgp *s, capn_ptr p);
void qcapn_BGP_write(const struct bgp *s, capn_ptr p);
void qcapn_BGPAfiSafi_read(struct bgp *s, capn_ptr p, address_family_t afi, subsequent_address_family_t  safi);
void qcapn_BGPAfiSafi_write(const struct bgp *s, capn_ptr p, address_family_t afi, subsequent_address_family_t safi);
capn_ptr qcapn_new_BGPAfiSafi(struct capn_segment *s);

capn_ptr qcapn_new_VRFTableIter(struct capn_segment *s);
void qcapn_VRFTableIter_read(struct zrpc_prefix *s, capn_ptr p);
void qcapn_VRFTableIter_write(const struct zrpc_prefix *s, capn_ptr p);
uint8_t qcapn_BGPVRF_get_layer_type(capn_ptr p);
capn_ptr qcapn_new_BGPVRFRoute(struct capn_segment *s, uint8_t extend_by);
void qcapn_BGPVRFRoute_read(struct bgp_api_route *s, capn_ptr p);
void qcapn_BGPVRFRoute_write(const struct bgp_api_route *s, capn_ptr p);

void qcapn_BGPEventShut_read(struct bgp_event_shut *s, capn_ptr p);

capn_ptr qcapn_new_BGPPeer(struct capn_segment *s);
void qcapn_BGPPeer_read(struct peer *s, capn_ptr p);
void qcapn_BGPPeer_write(const struct peer *s, capn_ptr p);
void qcapn_BGPPeerAfiSafi_write(const struct peer *s, capn_ptr p, address_family_t afi, subsequent_address_family_t safi);
void qcapn_BGPPeerAfiSafi_read(struct peer *s, capn_ptr p, address_family_t afi, subsequent_address_family_t safi);
capn_ptr qcapn_new_AfiSafiKey(struct capn_segment *s);
capn_ptr qcapn_new_BGPPeerAfiSafi(struct capn_segment *s);
void qcapn_BGPPeerStatus_read (struct peer *s, capn_ptr p);

void qcapn_BGPEventVRFRoute_read(struct bgp_event_vrf *s, capn_ptr p);
//void qcapn_BGPEventVRFRoute_write(const struct bgp_event_vrf *s, capn_ptr p);
capn_ptr qcapn_new_BGPEventVRFRoute(struct capn_segment *s);

capn_ptr qcapn_new_BGPVRFInfoIter(struct capn_segment *s);
void qcapn_BGPVRFInfoIter_write(const unsigned long s, capn_ptr p, int offset);
void qcapn_BGPVRFInfoIter_read(unsigned long *s, capn_ptr p, int offset);

capn_ptr qcapn_new_BGPVRF(struct capn_segment *s);
void qcapn_BGPVRF_read(struct bgp_vrf *s, capn_ptr p);
void qcapn_BGPVRF_write(const struct bgp_vrf *s, capn_ptr p);
void qcapn_prefix_macip_read(capn_ptr p, struct zrpc_prefix *pfx, uint8_t *index);
void qcapn_prefix_macip_write(capn_ptr p, const struct zrpc_prefix *pfx, uint8_t *index);
void qcapn_prefix_ipv4ipv6_write (capn_ptr p, const struct zrpc_prefix *pfx, uint8_t index);
void qcapn_prefix_ipv4ipv6_read(capn_ptr p, struct zrpc_prefix *pfx, uint8_t index);

#endif /* _ZRPC_BGP_CAPNP_H */
