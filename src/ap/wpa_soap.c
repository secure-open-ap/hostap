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

#include "wpa_soap.h"
#include "wpa_soap_i.h"

#define STATE_MACHINE_DATA struct soap_state_machine
#define STATE_MACHINE_DEBUG_PREFIX "SOAP"
#define STATE_MACHINE_ADDR sm->addr

static int soap_sm_step(struct soap_state_machine *sm);

struct wpa_soap_agent * soap_init(const u8 *addr) {
  struct wpa_soap_agent *wpa_soap;

  wpa_soap = os_zalloc(sizeof(struct wpa_soap_agent));
  if (wpa_soap == NULL)
    return NULL;
  os_memcpy(wpa_soap->addr, addr, ETH_ALEN);

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

struct soap_state_machine * wpa_soap_sta_init(struct wpa_soap_agent *wpa_soap,
      const u8 *addr)
{
  struct soap_state_machine *sm;

  sm = os_zalloc(sizeof(struct soap_state_machine));
  if (sm == NULL)
    return NULL;
  os_memcpy(sm->addr, addr, ETH_ALEN);

  sm->wpa_soap = wpa_soap;

  return sm;
}

int wpa_soap_sta_associated(struct wpa_soap_agent *wpa_soap,
          struct soap_state_machine *sm)
{
  if (wpa_soap == NULL || sm == NULL)
    return -1;

  sm->started = 1;

  sm->Init = TRUE;
  if (soap_sm_step(sm) == 1)
    return 1; /* should not really happen */
  sm->Init = FALSE;
  sm->SendSoapM1 = TRUE;
  return soap_sm_step(sm);
}

/*
 * NOTE
 * SM_STEP(SOAP): defines sm_SOAP_Step(sm)
 * SM_STEP_RUN(SOAP): calls sm_SOAP_Step(sm) (SM_STEP(SOAP))
 *                    (execute state machine itself)
 * SM_STATE(SOAP, STATE): defines static void sm_SOAP_STATE_Enter(sm, int)
 * SM_ENTER: calls sm_SOAP_STATE_Enter(sm, 0)
 * SM_ENTRY_MA(SOAP, STATE, soap): sets the current state
 *                                 (sm->soap_state = SOAP_STATE)
 */

SM_STATE(SOAP, INITIALIZE)
{
  SM_ENTRY_MA(SOAP, INITIALIZE, soap)
  if (sm->Init) {
    u8 _rand[20];
		/* Init flag is not cleared here, so avoid busy
		 * loop by claiming nothing changed. */
    sm->changed = FALSE;
    struct crypto_ec *e = sm->wpa_soap->e;
    if (crypto_get_random(_rand, crypto_ec_prime_len(e)) < 0) {
      /*
       * TODO: error handling
       */
    }
    sm->wpa_soap->b = crypto_bignum_init_set(_rand, crypto_ec_prime_len(e));
    if (sm->wpa_soap->b == NULL) {
      /*
       * TODO: error handling
       */
    }
    if (crypto_ec_point_mul(e, sm->wpa_soap->g, sm->wpa_soap->b,
          sm->wpa_soap->q)) {
      /*
       * TODO: error handling
       */
    }
    /*
     * TODO: Send SoapM1
     */
  }
}

SM_STEP(SOAP)
{
  // struct wpa_soap_agent *wpa_soap = sm->wpa_soap;

  if (sm->Init)
    SM_ENTER(SOAP, INITIALIZE);
}

static int soap_sm_step(struct soap_state_machine *sm)
{
  if (sm == NULL)
    return 0;

  if (sm->in_step_loop) {
    return 0;
  }

  sm->in_step_loop = 1;
  do {
    if (sm->pending_deinit)
      break;

    sm->changed = FALSE;

    SM_STEP_RUN(SOAP);
    if (sm->pending_deinit)
      break;
  } while (sm->changed);
  sm->in_step_loop = 0;

  if (sm->pending_deinit) {
    return 1;
  }
  return 0;
}
