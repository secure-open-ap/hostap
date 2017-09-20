/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#include "includes.h"

#include "common/ieee802_11_defs.h"

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

struct wpabuf * soap_build_assoc_req(int soap)
{
  struct wpabuf *buf;

  if (!soap) {
    return NULL;
  }

  buf = wpabuf_alloc(3);
  if (!buf) {
    return NULL;
  }

  wpabuf_put_u8(buf, WLAN_EID_SOAP); /* Element ID */
  wpabuf_put_u8(buf, 1); /* Length */
  wpabuf_put_u8(buf, soap);

  wpa_hexdump_buf(MSG_DEBUG, "SOAP: Association Request plaintext", buf);

  return buf;
}
