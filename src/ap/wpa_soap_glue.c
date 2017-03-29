/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#include "utils/includes.h"

#include "utils/common.h"
#include "hostapd.h"

#include "wpa_soap.h"

int hostapd_setup_soap(struct hostapd_data *hapd)
{
  hapd->wpa_soap = soap_init();
  if (hapd->wpa_soap == NULL) {
    wpa_printf(MSG_ERROR, "SOAP initialization failed.");
    return -1;
  }
  return 0;
}
