/**
******************************************************************************
* @file    aws_nucleo_certificates.c
* @author  Central LAB
* @version V2.0.0
* @date    22-June-2016
* @brief   AWS IoT Device Certificates, Private Key file
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*/


#include "stdint.h"


/**********************************************************************************************
                                                    Root CA certificate: Never modify
***********************************************************************************************/
/************************************************************************
Downloaded from https://www.symantec.com/content/en/us/enterprise/verisign/roots/VeriSign-Class%203-Public-Primary-Certification-Authority-G5.pem
*************************************************************************/

uint8_t rootCA[] = "\
-----BEGIN CERTIFICATE-----\n\
MIIE0zCCA7ugAwIBAgIQGNrRniZ96LtKIVjNzGs7SjANBgkqhkiG9w0BAQUFADCB\
yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL\
ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp\
U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW\
ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0\
aG9yaXR5IC0gRzUwHhcNMDYxMTA4MDAwMDAwWhcNMzYwNzE2MjM1OTU5WjCByjEL\
MAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLExZW\
ZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2ln\
biwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJp\
U2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9y\
aXR5IC0gRzUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvJAgIKXo1\
nmAMqudLO07cfLw8RRy7K+D+KQL5VwijZIUVJ/XxrcgxiV0i6CqqpkKzj/i5Vbex\
t0uz/o9+B1fs70PbZmIVYc9gDaTY3vjgw2IIPVQT60nKWVSFJuUrjxuf6/WhkcIz\
SdhDY2pSS9KP6HBRTdGJaXvHcPaz3BJ023tdS1bTlr8Vd6Gw9KIl8q8ckmcY5fQG\
BO+QueQA5N06tRn/Arr0PO7gi+s3i+z016zy9vA9r911kTMZHRxAy3QkGSGT2RT+\
rCpSx4/VBEnkjWNHiDxpg8v+R70rfk/Fla4OndTRQ8Bnc+MUCH7lP59zuDMKz10/\
NIeWiu5T6CUVAgMBAAGjgbIwga8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8E\
BAMCAQYwbQYIKwYBBQUHAQwEYTBfoV2gWzBZMFcwVRYJaW1hZ2UvZ2lmMCEwHzAH\
BgUrDgMCGgQUj+XTGoasjY5rw8+AatRIGCx7GS4wJRYjaHR0cDovL2xvZ28udmVy\
aXNpZ24uY29tL3ZzbG9nby5naWYwHQYDVR0OBBYEFH/TZafC3ey78DAJ80M5+gKv\
MzEzMA0GCSqGSIb3DQEBBQUAA4IBAQCTJEowX2LP2BqYLz3q3JktvXf2pXkiOOzE\
p6B4Eq1iDkVwZMXnl2YtmAl+X6/WzChl8gGqCBpH3vn5fJJaCGkgDdk+bW48DW7Y\
5gaRQBi5+MHt39tBquCWIMnNZBU4gcmU7qKEKQsTb47bDN0lAtukixlE0kF6BWlK\
WE9gyn6CagsCqiUXObXbf+eEZSqVir2G3l6BFoMtEMze/aiCKm0oHw0LxOXnGiYZ\
4fQRbxC1lfznQgUy286dUV4otp6F01vvpX1FQHKOtw5rDgb7MzVIcbidJ4vEZV8N\
hnacRHr2lVz2XTIIM6RUthg/aFzyQkqFOFSDX9HoLPKsEdao7WNq\
\n-----END CERTIFICATE-----\n";



/**********************************************************************************************
          Device Identity Certificates: Modify for your AWS IoT Thing
***********************************************************************************************/
/**********************************************************************************************
ECDSA Algo
ECDSA Private Key generated @ User Windows 7 Desktop, using openssl-1.0.2d-x64_86-win64/openssl.exe tool
Device Identity Certificate is Generated @ AWS IOT consoile by submitting a CSR. 
The CSR is generated @ User Windows 7 Desktop, using openssl-1.0.2d-x64_86-win64/openssl.exe tool
************************************************************************************************/
//Hem-Dutt Account

uint8_t clientCRT[] = "\
-----BEGIN CERTIFICATE-----\n\
MIIC0zCCAbugAwIBAgIUFp0qUp9z/+cjPxP3QGuRDF2UV0gwDQYJKoZIhvcNAQEL\
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE3MDIyMjEzMjEw\
MFoXDTQ5MTIzMTIzNTk1OVowYzETMBEGA1UEAwwKd3d3LnN0LmNvbTEgMB4GCSqG\
SIb3DQEJARYRaGVtLmRhYnJhbEBzdC5jb20xDDAKBgNVBAoMA1NUTTEPMA0GA1UE\
BwwGR05vaWRhMQswCQYDVQQGEwJJTjBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IA\
BJhrnjqHmGeL9WBaX31xo/KtQcyow30o8KVWGFczklLUyJU49rbvu6glsGhc5uRF\
OAQrA14Ri72d6dKh2vBt9QKjYDBeMB8GA1UdIwQYMBaAFOTp3jtl0TJQRgIGeDl0\
EY+oSR5WMB0GA1UdDgQWBBSLiPRpiD0M4MoKCPGKI3oHwFKXXDAMBgNVHRMBAf8E\
AjAAMA4GA1UdDwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAQ1YCYXR2TLpp\
ocRdfv/LmqGcnLI61k4SA/9stPhY3whPdq1RnWuODSWYp+Gb3oc+ssuwsJ59j8XW\
4V0ODFg9a8gSJ0nV6lhqlwe0GgdHVTEzkXr+6O3Umn/0glWEihjkmXsm60zqVSsg\
M1dgSzRjb9tXDkNR7MtzEDR1+QdfQfnVJusOkk4eFDyNtpTeDiBD47bRigoAYKrM\
XHVsDPbCFcji3z4CEg5R8TI6eFNFv1u6qXJQiaUXsBERrCwzCjnNf4jlnnBLINam\
A4OlVxDzszzQUsI3BDef+FEURIA2mLDJF8KjA8IcJt69m18BgUkthYgDBb8dGIvP\
4IPV6IGI2g==\
\n-----END CERTIFICATE-----\n";


/**********************************************************************************************
                                                    Private Key
***********************************************************************************************/
/********************************************************************8****************************************
ECDSA Algo
ECDSA Private Key generated @ User Windows 7 Desktop, using openssl-1.0.2d-x64_86-win64/openssl.exe tool
ECDSA-SEC1.PEM
**************************************************************************************************************/

uint8_t clientKey[] ="\
-----BEGIN EC PARAMETERS-----\n\
BggqhkjOPQMBBw==\
\n-----END EC PARAMETERS-----\n\
-----BEGIN EC PRIVATE KEY-----\n\
MHcCAQEEIM5bbZPgdTiGNFfdibwAxwebqu5YktcIhgZea4TdRuJloAoGCCqGSM49\
AwEHoUQDQgAEmGueOoeYZ4v1YFpffXGj8q1BzKjDfSjwpVYYVzOSUtTIlTj2tu+7\
qCWwaFzm5EU4BCsDXhGLvZ3p0qHa8G31Ag==\
\n-----END EC PRIVATE KEY-----\n";
