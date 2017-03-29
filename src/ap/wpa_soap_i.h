/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#ifndef WPA_SOAP_I_H
#define WPA_SOAP_I_H

struct wpa_soap_agent {
  // const struct dh_group *dh_group;
  struct crypto_ec *crypto_ec;
  struct crypto_ec_point *crypto_ec_point;
};

#endif /* WPA_SOAP_I_H */
