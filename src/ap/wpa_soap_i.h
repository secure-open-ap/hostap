/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#ifndef WPA_SOAP_I_H
#define WPA_SOAP_I_H

struct wpa_soap {
  int sta_use_soap;
  // const struct dh_group *dh_group;
  struct crypto_ec *e;
  struct crypto_ec_point *g;
  struct crypto_bignum *b;
  struct crypto_ec_point *q;

  u8 addr[ETH_ALEN];
};

#endif /* WPA_SOAP_I_H */
