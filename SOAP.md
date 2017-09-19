# Secure Open AP Design

| Frame | Description |
|:-----:|:------:|
| Beacon, ProbeResp | If SOAP IE exists, SOAP capable AP. |
| AuthReq | If SOAP IE exists, SOAP capable STA. |
| SOAP-Key M1 | contains P, G and A |
| SOAP-Key M2 | contains B |

**Maybe SOAP-Key frame requires RSN IE**

## Beacon, ProbeResp and AuthReq

```
0        7       15
+--------+--------+-----+
|   EID  | Length | RSN |
+--------+--------+-----+
|   255  |    X   | ... |
+--------+--------+-----+
```

If RSN IE is specified, RSN subfield in SOAP-IE can be omitted.

## SOAP-Key message (Not complete)

### Message 1

```
+---+---+---+
| A | P | G |
+---+---+---+
```
### Message 2

```
+---+
| B |
+---+
```
