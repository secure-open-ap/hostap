/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#ifndef WPA_SOAP_H
#define WPA_SOAP_H

#include "common/defs.h"

struct wpa_state_machine;

struct wpa_soap_callbacks {
	void *ctx;

	int (*send_soap)(void *ctx, const u8 *addr, const u8 *data,
			  size_t data_len, int encrypt);
};

struct wpa_soap * soap_init(const u8 *addr,
				    struct wpa_soap_callbacks *cb);
int wpa_soap_sta_init(struct wpa_state_machine *sm, struct wpa_soap *wpa_soap,
				    const u8 *addr, int sta_use_soap);

#endif /* WPA_SOAP_H */
