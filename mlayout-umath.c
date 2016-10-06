/*
  Copyright (C) 2016 Clerk Ma (clerkma@gmail.com)

  This file is part of mlayout.
*/

/* for unicode math rendering */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// 'COLR', color table
typedef struct {
  uint16_t GID;
  uint16_t firstLayerIndex;
  uint16_t numLayers;
} OTF_COLR_BaseGlyph;

typedef struct {
  uint16_t GID;
  uint16_t paletteIndex;
} OTF_COLR_Layer;

typedef struct {
  uint16_t version;
  uint16_t numBaseGlyphRecords;
  uint16_t numLayerRecords;
  OTF_COLR_BaseGlyph * base_glyphs;
  OTF_COLR_Layer * layers;
} OTF_COLR;

// 'CPAL', color palette table
typedef struct {
  uint8_t blue;
  uint8_t green;
  uint8_t red;
  uint8_t alpha;
} OTF_CPAL_Color;

typedef struct {
  uint16_t version;
  uint16_t numPalettesEntries;
  uint16_t numPalette;
  uint16_t numColorRecords;
  uint16_t * colorRecordIndices;
  OTF_CPAL_Color * colorRecords;
  uint32_t * paletteType;
  uint16_t * paletteLabel;
  uint16_t * paletteEntryLabel;
} OTF_CPAL;

// 'MATH', math layout data

typedef struct {
  int16_t value;
} OTF_MATH_MathValue;

typedef struct {
  int16_t ScriptPercentScaleDown;
  int16_t ScriptScriptPercentScaleDown;
  uint16_t DelimitedSubFormulaMinHeight;
  uint16_t DisplayOperatorMinHeight;
  OTF_MATH_MathValue MathLeading;
  OTF_MATH_MathValue AxisHeight;
  OTF_MATH_MathValue AccentBaseHeight;
  OTF_MATH_MathValue FlattenedAccentBaseHeight;
  OTF_MATH_MathValue SubscriptShiftDown;
  OTF_MATH_MathValue SubscriptTopMax;
  OTF_MATH_MathValue SubscriptBaselineDropMin;
  OTF_MATH_MathValue SuperscriptShiftUp;
  OTF_MATH_MathValue SuperscriptShiftUpCramped;
  OTF_MATH_MathValue SuperscriptBottomMin;
  OTF_MATH_MathValue SuperscriptBaselineDropMax;
  OTF_MATH_MathValue SubSuperscriptGapMin;
  OTF_MATH_MathValue SuperscriptBottomMaxWithSubscript;
  OTF_MATH_MathValue SpaceAfterScript;
  OTF_MATH_MathValue UpperLimitGapMin;
  OTF_MATH_MathValue UpperLimitBaselineRiseMin;
  OTF_MATH_MathValue LowerLimitGapMin;
  OTF_MATH_MathValue LowerLimitBaselineDropMin;
  OTF_MATH_MathValue StackTopShiftUp;
  OTF_MATH_MathValue StackTopDisplayStyleShiftUp;
  OTF_MATH_MathValue StackBottomShiftDown;
  OTF_MATH_MathValue StackBottomDisplayStyleShiftDown;
  OTF_MATH_MathValue StackGapMin;
  OTF_MATH_MathValue StackDisplayStyleGapMin;
  OTF_MATH_MathValue StretchStackTopShiftUp;
  OTF_MATH_MathValue StretchStackBottomShiftDown;
  OTF_MATH_MathValue StretchStackGapAboveMin;
  OTF_MATH_MathValue StretchStackGapBelowMin;
  OTF_MATH_MathValue FractionNumeratorShiftUp;
  OTF_MATH_MathValue FractionNumeratorDisplayStyleShiftUp;
  OTF_MATH_MathValue FractionDenominatorShiftDown;
  OTF_MATH_MathValue FractionDenominatorDisplayStyleShiftDown;
  OTF_MATH_MathValue FractionNumeratorGapMin;
  OTF_MATH_MathValue FractionNumDisplayStyleGapMin;
  OTF_MATH_MathValue FractionRuleThickness;
  OTF_MATH_MathValue FractionDenominatorGapMin;
  OTF_MATH_MathValue FractionDenomDisplayStyleGapMin;
  OTF_MATH_MathValue SkewedFractionHorizontalGap;
  OTF_MATH_MathValue SkewedFractionVerticalGap;
  OTF_MATH_MathValue OverbarVerticalGap;
  OTF_MATH_MathValue OverbarRuleThickness;
  OTF_MATH_MathValue OverbarExtraAscender;
  OTF_MATH_MathValue UnderbarVerticalGap;
  OTF_MATH_MathValue UnderbarRuleThickness;
  OTF_MATH_MathValue UnderbarExtraDescender;
  OTF_MATH_MathValue RadicalVerticalGap;
  OTF_MATH_MathValue RadicalDisplayStyleVerticalGap;
  OTF_MATH_MathValue RadicalRuleThickness;
  OTF_MATH_MathValue RadicalExtraAscender;
  OTF_MATH_MathValue RadicalKernBeforeDegree;
  OTF_MATH_MathValue RadicalKernAfterDegree;
  int16_t RadicalDegreeBottomRaisePercent;
} OTF_MATH_MathConstants;

typedef struct {
  uint16_t ItalicsCorrectionCount;
  OTF_MATH_MathValue * ItalicsCorrection;
} OTF_MATH_MathItalicCorrectionInfo;

typedef struct {
  uint16_t TopAccentAttachmentCount;
  OTF_MATH_MathValue * TopAccentAttachment;
} OTF_MATH_MathTopAccentAttachment;

typedef struct {
  uint16_t HeightCount;
  OTF_MATH_MathValue * CorrectionHeight;
  OTF_MATH_MathValue * KernValue;
} OTF_MATH_MathKern;

typedef struct {
  uint32_t TopRightMathKern;
  uint32_t TopLeftMathKern;
  uint32_t BottomRightMathKern;
  uint32_t BottomLeftMathKern;
} OTF_MATH_MathKernInfoRecord;

typedef struct {
  uint16_t MathKernCount;
  OTF_MATH_MathKern * MathKern;
  OTF_MATH_MathKernInfoRecord * MathKernInfoRecords;
} OTF_MATH_MathKernInfo;

typedef struct {
  OTF_MATH_MathItalicCorrectionInfo MathItalicCorrectionInfo;
  OTF_MATH_MathTopAccentAttachment MathTopAccentAttachment;
  OTF_MATH_MathKernInfo MathKernInfo;
} OTF_MATH_MathGlyphInfo;

typedef struct {
  uint16_t Glyph;
  uint16_t StartConnectorLength;
  uint16_t EndConnectorLength;
  uint16_t FullAdvance;
  uint16_t PartFlags;
} OTF_MATH_GlyphPartRecord;

typedef struct {
  OTF_MATH_MathValue ItalicsCorrection;
  uint16_t PartCount;
  OTF_MATH_GlyphPartRecord * PartRecords;
} OTF_MATH_GlyphAssembly;

typedef struct {
  uint16_t VariantGlyph;
  uint16_t AdvanceMeasurement;
} OTF_MATH_MathGlyphVariantRecord;

typedef struct {
  OTF_MATH_GlyphAssembly GlyphAssembly;
  uint16_t VariantCount;
  OTF_MATH_MathGlyphVariantRecord * MathGlyphVariantRecord;
} OTF_MATH_MathGlyphConstruction;

typedef struct {
  uint16_t MinConnectorOverlap;
  uint16_t VertGlyphCount;
  uint16_t HorizGlyphCount;
  OTF_MATH_MathGlyphConstruction VertGlyphConstruction;
  OTF_MATH_MathGlyphConstruction HorizGlyphConstruction;
} OTF_MATH_MathVariants;

typedef struct {
  uint32_t version;
  OTF_MATH_MathConstants MathConstants;
  OTF_MATH_MathGlyphInfo MathGlyphInfo;
  OTF_MATH_MathVariants MathVariants;
} OTF_MATH;
