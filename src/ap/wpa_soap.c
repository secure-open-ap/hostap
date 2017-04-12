/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#include "utils/includes.h"
#include <openssl/bn.h>

#include "utils/common.h"
#include "utils/state_machine.h"
#include "crypto/dh_groups.h"
#include "crypto/crypto.h"

#include "wpa_auth.h"
#include "wpa_auth_i.h"

#include "wpa_soap.h"

struct wpa_soap * soap_init(const u8 *addr,
		    struct wpa_soap_callbacks *cb) {
  struct wpa_soap *wpa_soap;

  wpa_soap = os_zalloc(sizeof(struct wpa_soap));
  if (wpa_soap == NULL)
    return NULL;
  os_memcpy(wpa_soap->addr, addr, ETH_ALEN);
	os_memcpy(&wpa_soap->cb, cb, sizeof(*cb));

  /*
   * 14: 2048 bit MODP
   */
  // wpa_soap->dh_group = dh_groups_get(14);
  // if (wpa_soap->dh_group == NULL)
  //   os_free(wpa_soap);
  //   return NULL;

  /*
   * 26: NID_secp224r1
   * TODO: Need to negotiate gorup between STA and AP?
   */
  wpa_soap->e = crypto_ec_init(26);
  if (wpa_soap->e == NULL) {
    wpa_printf(MSG_ERROR, "Initializing EC group (%d) for SOAP failed", 26);
    goto free_wpa_soap;
  }

  wpa_soap->g = crypto_ec_point_init(wpa_soap->e);
  if (wpa_soap->g == NULL) {
    wpa_printf(MSG_ERROR, "Initializing EC generator for SOAP failed");
    goto deinit_e;
  }

  return wpa_soap;

deinit_e:
  crypto_ec_deinit(wpa_soap->e);
free_wpa_soap:
  os_free(wpa_soap);
  return NULL;
}

int wpa_soap_sta_init(struct wpa_state_machine *sm, struct wpa_soap *wpa_soap,
      const u8 *addr, int sta_use_soap)
{

  /*
   * TODO: edit in wpa_state_machine
   */
  wpa_soap->sta_use_soap = sta_use_soap;
  sm->wpa_soap = wpa_soap;
  if (!sta_use_soap) {
    return 0;
  }
  return 0;

}
