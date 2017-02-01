/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#ifndef SOAP_H
#define SOAP_H

#define WLAN_EID_SOAP 255

u8 hostapd_soap_ie_len(struct hostapd_data *hapd);
u8 * hostapd_eid_soap(struct hostapd_data *hapd, u8 *eid);

#endif /* SOAP_H */
