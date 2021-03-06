#ifndef HTTP_HEADERS_H
#define HTTP_HEADERS_H

/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* iot_support at tid dot es
*
* Author: Ken Zangelin
*/
#include <string>
#include <vector>

#include "common/MimeType.h"



/* ****************************************************************************
*
* HTTP Headers -
*/
#define ACCESS_CONTROL_ALLOW_ORIGIN   "Access-Control-Allow-Origin"
#define ACCESS_CONTROL_ALLOW_HEADERS  "Access-Control-Allow-Headers"
#define ACCESS_CONTROL_ALLOW_METHODS  "Access-Control-Allow-Methods"
#define ACCESS_CONTROL_MAX_AGE        "Access-Control-Max-Age"
#define ACCESS_CONTROL_EXPOSE_HEADERS "Access-Control-Expose-Headers"
#define CONTENT_TYPE                  "Content-Type"
#define FIWARE_CORRELATOR             "Fiware-Correlator"
#define FIWARE_SERVICE                "Fiware-Service"
#define FIWARE_SERVICEPATH            "Fiware-Servicepath"
#define FIWARE_TOTAL_COUNT            "Fiware-Total-Count"
#define NGSIV2_ATTRSFORMAT            "Ngsiv2-AttrsFormat"
#define RESOURCE_LOCATION             "Location"
#define X_AUTH_TOKEN                  "X-Auth-Token"
#define X_REAL_IP                     "X-Real-IP"
#define X_FORWARDED_FOR               "X-Forwarded-For"



/* ****************************************************************************
*
* CORS Allowed Headers -
*/
#define CORS_ALLOWED_HEADERS CONTENT_TYPE ", " FIWARE_SERVICE ", " FIWARE_SERVICEPATH ", " NGSIV2_ATTRSFORMAT ", " FIWARE_CORRELATOR ", " X_FORWARDED_FOR ", " X_REAL_IP ", " X_AUTH_TOKEN



/* ****************************************************************************
*
* CORS Exposed Headers -
*/
#define CORS_EXPOSED_HEADERS FIWARE_CORRELATOR ", " FIWARE_TOTAL_COUNT ", " RESOURCE_LOCATION



// -----------------------------------------------------------------------------
//
// HttpAcceptHeader -
//
// The incoming data is a comma-separated list of media-range, accept-params, and accept-extension.
// The three components are separated by semicolon, and so are multiple accept-extensions.
// There is only one media-range and only one instance of accept-params (or zero)
//
// See https://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html
//
// Accept = "Accept" ":" <media-range> [;<accept-params>[;accept-extension]*]
//
//   media-range:      < */* | type/* | type/subtype >
//   accept-params:    [ q=<qvalue> ]
//   accept-extension: [ token=<token|quoted-string> ]*
//
// The qvalue is a parameter for indicating a relative quality factor. It goes from 1 to 0, 1 being max-priority.
// The default value of q is 1.
//
typedef struct HttpAcceptHeader
{
  std::string               mediaRange;
  double                    qvalue;
  std::vector<std::string>  acceptExtensions;
} HttpAcceptHeader;



/* ****************************************************************************
*
* HttpHeaders -
*/
typedef struct HttpHeaders
{
  HttpHeaders();

  void      release(void);
  bool      accepted(const std::string& mime);
  MimeType  outformatSelect(void);

  std::vector<HttpAcceptHeader*> acceptHeaderV;

  bool          gotHeaders;
  std::string   userAgent;
  std::string   host;
  std::string   accept;
  std::string   expect;
  std::string   contentType;
  std::string   origin;
  std::string   tenant;
  std::string   servicePath;
  std::string   xauthToken;
  std::string   xrealIp;
  std::string   xforwardedFor;
  std::string   correlator;
  std::string   ngsiv2AttrsFormat;

  bool          servicePathReceived;

  unsigned int  contentLength;
  std::string   connection;
} HttpHeaders;

#endif
