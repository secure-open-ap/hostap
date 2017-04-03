/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#ifndef WPA_SOAP_H
#define WPA_SOAP_H

#include "common/defs.h"

struct wpa_state_machine;

struct wpa_soap * soap_init(const u8 *addr);
int wpa_soap_sta_init(struct wpa_state_machine *sm, struct wpa_soap *wpa_soap,
      const u8 *addr, int sta_use_soap);

#endif /* WPA_SOAP_H */
