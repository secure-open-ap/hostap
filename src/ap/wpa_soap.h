/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#ifndef WPA_SOAP_H
#define WPA_SOAP_H

#include "common/defs.h"

struct wpa_soap_agent * soap_init();
struct soap_state_machine * wpa_soap_sta_init(struct wpa_soap_agent *wpa_soap,
      const u8 *addr);
int wpa_soap_sta_associated(struct wpa_soap_agent *wpa_soap,
          struct soap_state_machine *sm);

#endif /* WPA_SOAP_H */
