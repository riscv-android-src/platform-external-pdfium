// Copyright 2016 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FPDFAPI_RENDER_CPDF_PAGERENDERCACHE_H_
#define CORE_FPDFAPI_RENDER_CPDF_PAGERENDERCACHE_H_

#include <map>

#include "core/fxcrt/fx_system.h"

class CPDF_Stream;
class CPDF_ImageCacheEntry;
class CPDF_Page;
class CPDF_RenderStatus;
class CFX_DIBitmap;
class CFX_DIBSource;
class IFX_Pause;

class CPDF_PageRenderCache {
 public:
  explicit CPDF_PageRenderCache(CPDF_Page* pPage);
  ~CPDF_PageRenderCache();

  uint32_t EstimateSize();
  void CacheOptimization(int32_t dwLimitCacheSize);
  uint32_t GetTimeCount() const { return m_nTimeCount; }
  void SetTimeCount(uint32_t dwTimeCount) { m_nTimeCount = dwTimeCount; }

  void GetCachedBitmap(CPDF_Stream* pStream,
                       CFX_DIBSource*& pBitmap,
                       CFX_DIBSource*& pMask,
                       uint32_t& MatteColor,
                       bool bStdCS = false,
                       uint32_t GroupFamily = 0,
                       bool bLoadMask = false,
                       CPDF_RenderStatus* pRenderStatus = nullptr,
                       int32_t downsampleWidth = 0,
                       int32_t downsampleHeight = 0);

  void ResetBitmap(CPDF_Stream* pStream, const CFX_DIBitmap* pBitmap);
  void ClearImageCacheEntry(CPDF_Stream* pStream);
  CPDF_Page* GetPage() const { return m_pPage; }
  CPDF_ImageCacheEntry* GetCurImageCacheEntry() const {
    return m_pCurImageCacheEntry;
  }

  bool StartGetCachedBitmap(CPDF_Stream* pStream,
                            bool bStdCS = false,
                            uint32_t GroupFamily = 0,
                            bool bLoadMask = false,
                            CPDF_RenderStatus* pRenderStatus = nullptr,
                            int32_t downsampleWidth = 0,
                            int32_t downsampleHeight = 0);

  bool Continue(IFX_Pause* pPause);

 protected:
  CPDF_Page* const m_pPage;
  CPDF_ImageCacheEntry* m_pCurImageCacheEntry;
  std::map<CPDF_Stream*, CPDF_ImageCacheEntry*> m_ImageCache;
  uint32_t m_nTimeCount;
  uint32_t m_nCacheSize;
  bool m_bCurFindCache;
};

#endif  // CORE_FPDFAPI_RENDER_CPDF_PAGERENDERCACHE_H_
