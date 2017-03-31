/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#ifndef WPA_SOAP_I_H
#define WPA_SOAP_I_H

struct soap_state_machine {
  struct wpa_soap_agent *wpa_soap;

  u8 addr[ETH_ALEN];

  enum {
      SOAP_INITIALIZE
  } soap_state;

  Boolean Init;
  Boolean SendSoapM1;

  unsigned int changed:1;
  unsigned int in_step_loop:1;
  unsigned int pending_deinit:1;
  unsigned int started:1;
};

struct wpa_soap_agent {
  // const struct dh_group *dh_group;
  struct crypto_ec *e;
  struct crypto_ec_point *g;
  struct crypto_bignum *b;
  struct crypto_ec_point *q;

  u8 addr[ETH_ALEN];
};

#endif /* WPA_SOAP_I_H */
