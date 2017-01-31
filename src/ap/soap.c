/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#include "includes.h"

#include "common.h"
#include "ap/hostapd.h"

#include "soap.h"
/* SOAP TODO: Which headers should be includede? */

u8 * hostapd_eid_soap(struct hostapd_data *hapd, u8 *eid)
{
  u8 *ie;
  
  /*
   * SOAP TODO: Currently, SOAP is implemented based on assumption that WPA is used,
   * but should support open system and shared key system (WEP) by running WPA
   * dedicated for SOAP.
   */
  if (hapd->conf->soap && (hapd->conf->wpa & (WPA_PROTO_WPA | WPA_PROTO_RSN)))
    return eid;

  /*
   * Information Element (octets)
   * Element ID (1), Length (1), bool SOAP (1)
   */
  ie = os_malloc(1 + 1 + 1);
  if (ie == NULL)
    return eid;

  ie[0] = WLAN_EID_SOAP;
  ie[1] = 1;
  ie[2] = 1;

  *eid++ = ie[0];
  *eid++ = ie[1];
  *eid++ = ie[2];
  
  os_free(ie);

  return eid;
  
}
