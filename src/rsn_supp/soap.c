/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#include "includes.h"

#include "common/ieee802_11_defs.h"
#include "soap.h"

int wpa_parse_soap_ie(const u8 *wpa_ie, size_t wpa_ie_len,
		     char *data)
{
  /* TODO: Currently, SOAP is simple true of false boolean
   * need to contain WPA/RSN information if open system is used
   */
	*data = 0;
  if (wpa_ie_len >= 1 && wpa_ie[0] == WLAN_EID_SOAP)
		*data = wpa_ie[2];
	return 0;
}
