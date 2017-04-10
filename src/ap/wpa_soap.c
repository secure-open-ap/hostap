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
#include "wpa_soap_i.h"

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
    goto free_wpa_soap;
  }

  wpa_soap->g = crypto_ec_point_init(wpa_soap->e);
  if (wpa_soap->g == NULL) {
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

void soap_receive(struct wpa_soap *wpa_soap,
     struct wpa_state_machine *sm,
     u8 *data, size_t data_len)
{
  /*
   * TODO: need to implement this in state machine!
   */
  struct ieee802_1x_hdr *hdr;
  u8 *payload;
  u8 *p;
  int p_len;

  tmp = os_malloc(data_len);
  if (tmp == NULL) {
    goto out;
  }
  os_memcpy(tmp, data, data_len);

  payload = (u8*)(tmp + sizeof(*hdr));
  p_len = WPA_GET_BE16(payload);
  p = payload + 2;

  wpa_soap->p = crypto_ec_point_from_bin(wpa_soap->e, p);
  if (wpa_soap->p) {
    goto free_tmp;
  }

  if (crypto_ec_point_mul(wpa_soap->e, wpa_soap->b, wpa_soap->p, wpa_soap->soap_pmk_ec)) {
    goto deinit_p;
  }

  if (crypto_ec_point_to_bin(wpa_soap->e, wpa_soap->soap_pmk_ec, NULL, wpa_soap->soap_pmk)) {
    goto deinit_p;
  }
  /*
   * TODO: set PMK
   * NOTE: need to backup *normal* PMK?
   */

deinit_p:
  crypto_ec_point_deinit(wpa_soap->p, 0);
free_tmp:
  os_free(tmp);
out:
  return;
}
