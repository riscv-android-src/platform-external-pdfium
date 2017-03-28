// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "xfa/fxfa/parser/cxfa_timezoneprovider.h"

#include <time.h>

static bool g_bProviderTimeZoneSet = false;

CXFA_TimeZoneProvider::CXFA_TimeZoneProvider() {
#if _FXM_PLATFORM_ == _FXM_PLATFORM_WINDOWS_
  if (!g_bProviderTimeZoneSet) {
    g_bProviderTimeZoneSet = true;
    _tzset();
  }
  m_tz.tzHour = static_cast<int8_t>(_timezone / 3600 * -1);
  m_tz.tzMinute = static_cast<int8_t>((FXSYS_abs(_timezone) % 3600) / 60);
#else
  if (!g_bProviderTimeZoneSet) {
    g_bProviderTimeZoneSet = true;
    tzset();
  }
  m_tz.tzHour = static_cast<int8_t>(timezone / 3600 * -1);
  m_tz.tzMinute =
      static_cast<int8_t>((FXSYS_abs(static_cast<int>(timezone)) % 3600) / 60);
#endif
}

CXFA_TimeZoneProvider::~CXFA_TimeZoneProvider() {}

void CXFA_TimeZoneProvider::GetTimeZone(FX_TIMEZONE* tz) const {
  *tz = m_tz;
}
