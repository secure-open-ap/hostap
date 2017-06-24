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

u8 g_bin[] = {
  0xB7,0x0E,0x0C,0xBD,0x6B,0xB4,0xBF,0x7F,0x32,0x13,
  0x90,0xB9,0x4A,0x03,0xC1,0xD3,0x56,0xC2,0x11,0x22,
  0x34,0x32,0x80,0xD6,0x11,0x5C,0x1D,0x21,
  0xbd,0x37,0x63,0x88,0xb5,0xf7,0x23,0xfb,0x4c,0x22,
  0xdf,0xe6,0xcd,0x43,0x75,0xa0,0x5a,0x07,0x47,0x64,
  0x44,0xd5,0x81,0x99,0x85,0x00,0x7e,0x34
};

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
  wpa_soap->ec = crypto_ec_init(26);
  if (wpa_soap->ec == NULL) {
    wpa_printf(MSG_ERROR, "Initializing EC group (%d) for SOAP failed", 26);
    goto free_wpa_soap;
  }

  wpa_soap->generator = crypto_ec_point_from_bin(wpa_soap->ec, g_bin);
  if (wpa_soap->generator == NULL) {
    wpa_printf(MSG_ERROR, "Initializing EC generator for SOAP failed");
    goto deinit_e;
  }

  return wpa_soap;

deinit_e:
  crypto_ec_deinit(wpa_soap->ec);
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
