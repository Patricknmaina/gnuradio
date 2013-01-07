/* -*- c++ -*- */
/*
 * Copyright 2008-2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef WATERFALL_DISPLAY_PLOT_H
#define WATERFALL_DISPLAY_PLOT_H

#include <stdint.h>
#include <cstdio>
#include <vector>
#include <qwt_plot_spectrogram.h>
#include "DisplayPlot.h"
#include "waterfallGlobalData.h"
#include <gruel/high_res_timer.h>

#if QWT_VERSION < 0x060000
#include <plot_waterfall.h>
#else
#include <qwt_compat.h>
#endif

class WaterfallDisplayPlot: public DisplayPlot
{
  Q_OBJECT

  Q_PROPERTY ( int intensity_color_map_type1 READ getIntensityColorMapType1 WRITE setIntensityColorMapType1 )
  Q_PROPERTY ( QColor low_intensity_color READ getUserDefinedLowIntensityColor WRITE setUserDefinedLowIntensityColor )
  Q_PROPERTY ( QColor high_intensity_color READ getUserDefinedHighIntensityColor WRITE setUserDefinedHighIntensityColor )
  

public:
  WaterfallDisplayPlot(int nplots, QWidget*);
  virtual ~WaterfallDisplayPlot();

  void resetAxis();

  void setFrequencyRange(const double, const double,
			 const double units=1000.0,
			 const std::string &strunits = "kHz");
  double getStartFrequency() const;
  double getStopFrequency() const;

  void plotNewData(const std::vector<double*> dataPoints,
		   const int64_t numDataPoints,
		   const double timePerFFT,
		   const gruel::high_res_timer_type timestamp,
		   const int droppedFrames);

  // to be removed
  void plotNewData(const double* dataPoints,
		   const int64_t numDataPoints,
		   const double timePerFFT,
		   const gruel::high_res_timer_type timestamp,
		   const int droppedFrames);

  void setIntensityRange(const double minIntensity, const double maxIntensity);

  void replot(void);

  int getIntensityColorMapType(int) const;
  int getIntensityColorMapType1() const;
  const QColor getUserDefinedLowIntensityColor() const;
  const QColor getUserDefinedHighIntensityColor() const;

public slots:
  void setIntensityColorMapType(const int, const int, const QColor, const QColor);
  void setIntensityColorMapType1(int);
  void setUserDefinedLowIntensityColor(QColor);
  void setUserDefinedHighIntensityColor(QColor);

signals:
  void updatedLowerIntensityLevel(const double);
  void updatedUpperIntensityLevel(const double);

private:
  void _updateIntensityRangeDisplay();

  double _startFrequency;
  double _stopFrequency;
  int    _xAxisMultiplier;

  std::vector<WaterfallData*> d_data;

#if QWT_VERSION < 0x060000
  std::vector<PlotWaterfall*> d_spectrogram;
#else
  std::vector<QwtPlotSpectrogram*> d_spectrogram;
#endif

  gruel::high_res_timer_type _lastReplot;

  std::vector<int> _intensityColorMapType;
  QColor _userDefinedLowIntensityColor;
  QColor _userDefinedHighIntensityColor;
};

#endif /* WATERFALL_DISPLAY_PLOT_H */
