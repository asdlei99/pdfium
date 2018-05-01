// Copyright 2015 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FXCODEC_JBIG2_JBIG2_GRDPROC_H_
#define CORE_FXCODEC_JBIG2_JBIG2_GRDPROC_H_

#include <memory>

#include "core/fxcodec/fx_codec_def.h"
#include "core/fxcrt/fx_coordinates.h"
#include "core/fxcrt/fx_system.h"
#include "core/fxcrt/unowned_ptr.h"

class CJBig2_ArithDecoder;
class CJBig2_BitStream;
class CJBig2_Image;
class PauseIndicatorIface;
struct JBig2ArithCtx;

class CJBig2_GRDProc {
 public:
  CJBig2_GRDProc();
  ~CJBig2_GRDProc();

  std::unique_ptr<CJBig2_Image> DecodeArith(CJBig2_ArithDecoder* pArithDecoder,
                                            JBig2ArithCtx* gbContext);

  FXCODEC_STATUS StartDecodeArith(std::unique_ptr<CJBig2_Image>* pImage,
                                  CJBig2_ArithDecoder* pArithDecoder,
                                  JBig2ArithCtx* gbContext,
                                  PauseIndicatorIface* pPause);
  FXCODEC_STATUS StartDecodeMMR(std::unique_ptr<CJBig2_Image>* pImage,
                                CJBig2_BitStream* pStream);
  FXCODEC_STATUS ContinueDecode(PauseIndicatorIface* pPause,
                                CJBig2_ArithDecoder* pArithDecoder);
  const FX_RECT& GetReplaceRect() const { return m_ReplaceRect; }

  bool MMR;
  uint32_t GBW;
  uint32_t GBH;
  uint8_t GBTEMPLATE;
  bool TPGDON;
  bool USESKIP;
  CJBig2_Image* SKIP;
  int8_t GBAT[8];

 private:
  bool UseTemplate0Opt3() const;
  bool UseTemplate1Opt3() const;
  bool UseTemplate23Opt3() const;

  FXCODEC_STATUS ProgressiveDecodeArith(PauseIndicatorIface* pPause,
                                        CJBig2_ArithDecoder* pArithDecoder);
  FXCODEC_STATUS ProgressiveDecodeArithTemplate0Opt3(
      CJBig2_ArithDecoder* pArithDecoder,
      PauseIndicatorIface* pPause);
  FXCODEC_STATUS ProgressiveDecodeArithTemplate0Unopt(
      CJBig2_ArithDecoder* pArithDecoder,
      PauseIndicatorIface* pPause);
  FXCODEC_STATUS ProgressiveDecodeArithTemplate1Opt3(
      CJBig2_ArithDecoder* pArithDecoder,
      PauseIndicatorIface* pPause);
  FXCODEC_STATUS ProgressiveDecodeArithTemplate1Unopt(
      CJBig2_ArithDecoder* pArithDecoder,
      PauseIndicatorIface* pPause);
  FXCODEC_STATUS ProgressiveDecodeArithTemplate2Opt3(
      CJBig2_ArithDecoder* pArithDecoder,
      PauseIndicatorIface* pPause);
  FXCODEC_STATUS ProgressiveDecodeArithTemplate2Unopt(
      CJBig2_ArithDecoder* pArithDecoder,
      PauseIndicatorIface* pPause);
  FXCODEC_STATUS ProgressiveDecodeArithTemplate3Opt3(
      CJBig2_ArithDecoder* pArithDecoder,
      PauseIndicatorIface* pPause);
  FXCODEC_STATUS ProgressiveDecodeArithTemplate3Unopt(
      CJBig2_ArithDecoder* pArithDecoder,
      PauseIndicatorIface* pPause);

  std::unique_ptr<CJBig2_Image> DecodeArithTemplate0Opt3(
      CJBig2_ArithDecoder* pArithDecoder,
      JBig2ArithCtx* gbContext);
  std::unique_ptr<CJBig2_Image> DecodeArithTemplate0Unopt(
      CJBig2_ArithDecoder* pArithDecoder,
      JBig2ArithCtx* gbContext);
  std::unique_ptr<CJBig2_Image> DecodeArithTemplate1Opt3(
      CJBig2_ArithDecoder* pArithDecoder,
      JBig2ArithCtx* gbContext);
  std::unique_ptr<CJBig2_Image> DecodeArithTemplate1Unopt(
      CJBig2_ArithDecoder* pArithDecoder,
      JBig2ArithCtx* gbContext);
  std::unique_ptr<CJBig2_Image> DecodeArithTemplate2Opt3(
      CJBig2_ArithDecoder* pArithDecoder,
      JBig2ArithCtx* gbContext);
  std::unique_ptr<CJBig2_Image> DecodeArithTemplate2Unopt(
      CJBig2_ArithDecoder* pArithDecoder,
      JBig2ArithCtx* gbContext);
  std::unique_ptr<CJBig2_Image> DecodeArithTemplate3Opt3(
      CJBig2_ArithDecoder* pArithDecoder,
      JBig2ArithCtx* gbContext);
  std::unique_ptr<CJBig2_Image> DecodeArithTemplate3Unopt(
      CJBig2_ArithDecoder* pArithDecoder,
      JBig2ArithCtx* gbContext);

  uint32_t m_loopIndex;
  uint8_t* m_pLine;
  FXCODEC_STATUS m_ProssiveStatus;
  CJBig2_Image* m_pImage;
  JBig2ArithCtx* m_gbContext;
  uint16_t m_DecodeType;
  int m_LTP;
  FX_RECT m_ReplaceRect;
};

#endif  // CORE_FXCODEC_JBIG2_JBIG2_GRDPROC_H_
