/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#include "utils/includes.h"

#include "utils/common.h"
#include "crypto/dh_groups.h"
#include "crypto/crypto.h"

#include "wpa_soap_i.h"

struct wpa_soap_agent * soap_init() {
  struct wpa_soap_agent *wpa_soap;

  wpa_soap = os_zalloc(sizeof(struct wpa_soap_agent));
  if (wpa_soap == NULL)
    return NULL;

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
  wpa_soap->crypto_ec = crypto_ec_init(26);
  if (wpa_soap->crypto_ec == NULL) {
    os_free(wpa_soap);
    return NULL;
  }

  wpa_soap->crypto_ec_point = crypto_ec_point_init(wpa_soap->crypto_ec);
  if (wpa_soap->crypto_ec_point == NULL) {
    crypto_ec_deinit(wpa_soap->crypto_ec);
    os_free(wpa_soap);
    return NULL;
  }

  return wpa_soap;

}
