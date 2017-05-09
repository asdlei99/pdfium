// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FPDFAPI_EDIT_CPDF_XREFSTREAM_H_
#define CORE_FPDFAPI_EDIT_CPDF_XREFSTREAM_H_

#include <vector>

#include "core/fpdfapi/edit/cpdf_objectstream.h"
#include "core/fxcrt/fx_basic.h"

class CPDF_Creator;
class CPDF_Object;

class CPDF_XRefStream {
 public:
  struct Index {
    uint32_t objnum;
    uint32_t count;
  };

  CPDF_XRefStream();
  ~CPDF_XRefStream();

  bool Start();
  int32_t CompressIndirectObject(uint32_t dwObjNum,
                                 const CPDF_Object* pObj,
                                 CPDF_Creator* pCreator);
  int32_t CompressIndirectObject(uint32_t dwObjNum,
                                 const uint8_t* pBuffer,
                                 uint32_t dwSize,
                                 CPDF_Creator* pCreator);
  bool End(CPDF_Creator* pCreator, bool bEOF);
  void AddObjectNumberToIndexArray(uint32_t objnum);
  bool EndXRefStream(CPDF_Creator* pCreator);

  FX_FILESIZE GetPreviousOffset() const { return m_PrevOffset; }
  void SetPreviousOffset(FX_FILESIZE offset) { m_PrevOffset = offset; }

  uint32_t CountIndexArrayItems() const {
    uint32_t size = 0;
    for (const auto& pair : m_IndexArray)
      size += pair.count;
    return size;
  }

 private:
  int32_t EndObjectStream(CPDF_Creator* pCreator, bool bEOF);
  bool GenerateXRefStream(CPDF_Creator* pCreator, bool bEOF);

  std::vector<Index> m_IndexArray;
  FX_FILESIZE m_PrevOffset;
  uint32_t m_dwTempObjNum;
  size_t m_iSeg;
  CPDF_ObjectStream m_ObjStream;
  CFX_ByteTextBuf m_Buffer;
};

#endif  // CORE_FPDFAPI_EDIT_CPDF_XREFSTREAM_H_
