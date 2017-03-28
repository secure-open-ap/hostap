/*
 * Secure Open Access Point
 * Seokseong Jeon
 * songsong@monet.postech.ac.kr
 */

#ifndef SOAP_H
#define SOAP_H

int wpa_parse_soap_ie(const u8 *wpa_ie, size_t wpa_ie_len,
		     char *data);
struct wpabuf * soap_build_assoc_req(int soap);

#endif /* SOAP_H */
