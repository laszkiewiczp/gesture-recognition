//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  computeFeatures.cpp
//
//  Code generation for function 'computeFeatures'
//


// Include files
#include "computeFeatures.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
namespace coder
{
  static void b_std(const ::coder::array<double, 2U> &x, double y[3]);
}

static void cutData(const coder::array<double, 2U> &b_signal, coder::array<
                    double, 2U> &sig1, coder::array<double, 2U> &sig2, coder::
                    array<double, 2U> &sig3, coder::array<double, 2U> &sig4);

// Function Definitions
namespace coder
{
  static void b_std(const ::coder::array<double, 2U> &x, double y[3])
  {
    array<double, 1U> xv;
    double xbar;
    double yv;
    int loop_ub;
    int n;
    int nx;
    nx = x.size(0);
    loop_ub = x.size(0);
    n = x.size(0);
    for (int p = 0; p < 3; p++) {
      int k;
      int tunableEnvironment_idx_0;
      tunableEnvironment_idx_0 = p * nx + 1;
      xv.set_size(nx);
      for (k = 0; k < loop_ub; k++) {
        xv[k] = 0.0;
      }

      for (k = 0; k < nx; k++) {
        xv[k] = x[(tunableEnvironment_idx_0 + k) - 1];
      }

      if (x.size(0) == 0) {
        y[p] = rtNaN;
      } else if (x.size(0) == 1) {
        if ((!rtIsInf(xv[0])) && (!rtIsNaN(xv[0]))) {
          y[p] = 0.0;
        } else {
          y[p] = rtNaN;
        }
      } else {
        double scale;
        if (xv.size(0) == 0) {
          xbar = 0.0;
        } else {
          xbar = xv[0];
          for (k = 2; k <= n; k++) {
            xbar += xv[k - 1];
          }
        }

        xbar /= static_cast<double>(x.size(0));
        yv = 0.0;
        scale = 3.3121686421112381E-170;
        for (k = 0; k < n; k++) {
          double d;
          d = std::abs(xv[k] - xbar);
          if (d > scale) {
            double t;
            t = scale / d;
            yv = yv * t * t + 1.0;
            scale = d;
          } else {
            double t;
            t = d / scale;
            yv += t * t;
          }
        }

        yv = scale * std::sqrt(yv);
        y[p] = yv / std::sqrt(static_cast<double>(x.size(0)) - 1.0);
      }
    }
  }
}

static void cutData(const coder::array<double, 2U> &b_signal, coder::array<
                    double, 2U> &sig1, coder::array<double, 2U> &sig2, coder::
                    array<double, 2U> &sig3, coder::array<double, 2U> &sig4)
{
  int i;
  int i1;
  int i2;
  int i3;
  int loop_ub;
  int piece_length;

  // This function is used to divide the acceleration signal into four equally
  // long pieces. Returns 4 arrays containing acceleration data as row vectors
  // [ax, ay, az]
  // the number of pieces that the signal will be divided into
  piece_length = static_cast<int>(std::floor(static_cast<double>(b_signal.size(0))
    / 4.0));
  if (1 > piece_length) {
    loop_ub = 0;
  } else {
    loop_ub = piece_length;
  }

  sig1.set_size(loop_ub, 3);
  for (i = 0; i < 3; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      sig1[i1 + sig1.size(0) * i] = b_signal[i1 + b_signal.size(0) * i];
    }
  }

  i = piece_length << 1;
  if (piece_length + 1 > i) {
    i1 = 0;
    i2 = 0;
  } else {
    i1 = piece_length;
    i2 = i;
  }

  loop_ub = i2 - i1;
  sig2.set_size(loop_ub, 3);
  for (i2 = 0; i2 < 3; i2++) {
    for (i3 = 0; i3 < loop_ub; i3++) {
      sig2[i3 + sig2.size(0) * i2] = b_signal[(i1 + i3) + b_signal.size(0) * i2];
    }
  }

  i1 = 3 * piece_length;
  if (i + 1 > i1) {
    i = 0;
    i2 = 0;
  } else {
    i2 = i1;
  }

  loop_ub = i2 - i;
  sig3.set_size(loop_ub, 3);
  for (i2 = 0; i2 < 3; i2++) {
    for (i3 = 0; i3 < loop_ub; i3++) {
      sig3[i3 + sig3.size(0) * i2] = b_signal[(i + i3) + b_signal.size(0) * i2];
    }
  }

  if (i1 + 1 > b_signal.size(0)) {
    i1 = 0;
    i = 0;
  } else {
    i = b_signal.size(0);
  }

  loop_ub = i - i1;
  sig4.set_size(loop_ub, 3);
  for (i = 0; i < 3; i++) {
    for (i2 = 0; i2 < loop_ub; i2++) {
      sig4[i2 + sig4.size(0) * i] = b_signal[(i1 + i2) + b_signal.size(0) * i];
    }
  }
}

void computeFeatures(coder::array<double, 2U> &accData, double features[48])
{
  coder::array<double, 2U> MI;
  coder::array<double, 2U> SIGMA;
  coder::array<double, 2U> acc1;
  coder::array<double, 2U> acc2;
  coder::array<double, 2U> acc3;
  coder::array<double, 2U> acc4;
  coder::array<double, 2U> b_MI;
  coder::array<double, 2U> b_signal;
  coder::array<double, 2U> grad4;
  coder::array<double, 1U> varargin_1;
  coder::array<double, 1U> varargin_2;
  coder::array<double, 1U> varargin_3;
  double b_y[3];
  double c_y[3];
  double d_y[3];
  double dv[3];
  double dv1[3];
  double dv2[3];
  double dv3[3];
  double dv4[3];
  double dv5[3];
  double dv6[3];
  double dv7[3];
  double e_y[3];
  double f_y[3];
  double mi[3];
  double sigma[3];
  double y[3];
  int b_i;
  int i;
  int k;
  int vlen;
  int xpageoffset;

  // This function produces features from the acceleration signal
  // This function computes derivatives of all the acceleration components over
  // time. The input is a matrix containing acceleration data in the form of
  // [ax, ay, az] being row vectors representing the acceleration components in
  // an instant of time
  varargin_1.set_size(accData.size(0));
  if (accData.size(0) >= 2) {
    varargin_1[0] = accData[1] - accData[0];
    i = accData.size(0) - 1;
    for (vlen = 2; vlen <= i; vlen++) {
      varargin_1[vlen - 1] = (accData[vlen] - accData[vlen - 2]) / 2.0;
    }

    varargin_1[accData.size(0) - 1] = accData[accData.size(0) - 1] -
      accData[accData.size(0) - 2];
  } else {
    vlen = accData.size(0);
    varargin_1.set_size(accData.size(0));
    for (i = 0; i < vlen; i++) {
      varargin_1[i] = 0.0;
    }
  }

  varargin_2.set_size(accData.size(0));
  if (accData.size(0) >= 2) {
    varargin_2[0] = accData[accData.size(0) + 1] - accData[accData.size(0)];
    i = accData.size(0) - 1;
    for (vlen = 2; vlen <= i; vlen++) {
      varargin_2[vlen - 1] = (accData[vlen + accData.size(0)] - accData[(vlen +
        accData.size(0)) - 2]) / 2.0;
    }

    varargin_2[accData.size(0) - 1] = accData[(accData.size(0) + accData.size(0))
      - 1] - accData[(accData.size(0) + accData.size(0)) - 2];
  } else {
    vlen = accData.size(0);
    varargin_2.set_size(accData.size(0));
    for (i = 0; i < vlen; i++) {
      varargin_2[i] = 0.0;
    }
  }

  varargin_3.set_size(accData.size(0));
  if (accData.size(0) >= 2) {
    varargin_3[0] = accData[accData.size(0) * 2 + 1] - accData[accData.size(0) *
      2];
    i = accData.size(0) - 1;
    for (vlen = 2; vlen <= i; vlen++) {
      varargin_3[vlen - 1] = (accData[vlen + accData.size(0) * 2] - accData
        [(vlen + accData.size(0) * 2) - 2]) / 2.0;
    }

    varargin_3[accData.size(0) - 1] = accData[(accData.size(0) + accData.size(0)
      * 2) - 1] - accData[(accData.size(0) + accData.size(0) * 2) - 2];
  } else {
    vlen = accData.size(0);
    varargin_3.set_size(accData.size(0));
    for (i = 0; i < vlen; i++) {
      varargin_3[i] = 0.0;
    }
  }

  // This function is used to normalize the signal with respect to its own
  vlen = accData.size(0);
  if (accData.size(0) == 0) {
    mi[0] = 0.0;
    mi[1] = 0.0;
    mi[2] = 0.0;
  } else {
    for (b_i = 0; b_i < 3; b_i++) {
      xpageoffset = b_i * accData.size(0);
      mi[b_i] = accData[xpageoffset];
      for (k = 2; k <= vlen; k++) {
        mi[b_i] += accData[(xpageoffset + k) - 1];
      }
    }
  }

  mi[0] /= static_cast<double>(accData.size(0));
  mi[1] /= static_cast<double>(accData.size(0));
  mi[2] /= static_cast<double>(accData.size(0));
  coder::b_std(accData, sigma);
  MI.set_size(0, 3);
  SIGMA.set_size(0, 3);
  i = accData.size(0);
  for (b_i = 0; b_i < i; b_i++) {
    vlen = MI.size(0);
    b_MI.set_size((MI.size(0) + 1), 3);
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      for (k = 0; k < vlen; k++) {
        b_MI[k + b_MI.size(0) * xpageoffset] = MI[k + MI.size(0) * xpageoffset];
      }
    }

    b_MI[MI.size(0)] = mi[0];
    b_MI[MI.size(0) + b_MI.size(0)] = mi[1];
    b_MI[MI.size(0) + b_MI.size(0) * 2] = mi[2];
    MI.set_size(b_MI.size(0), 3);
    vlen = b_MI.size(0) * b_MI.size(1);
    for (xpageoffset = 0; xpageoffset < vlen; xpageoffset++) {
      MI[xpageoffset] = b_MI[xpageoffset];
    }

    vlen = SIGMA.size(0);
    b_MI.set_size((SIGMA.size(0) + 1), 3);
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      for (k = 0; k < vlen; k++) {
        b_MI[k + b_MI.size(0) * xpageoffset] = SIGMA[k + SIGMA.size(0) *
          xpageoffset];
      }
    }

    b_MI[SIGMA.size(0)] = sigma[0];
    b_MI[SIGMA.size(0) + b_MI.size(0)] = sigma[1];
    b_MI[SIGMA.size(0) + b_MI.size(0) * 2] = sigma[2];
    SIGMA.set_size(b_MI.size(0), 3);
    vlen = b_MI.size(0) * b_MI.size(1);
    for (xpageoffset = 0; xpageoffset < vlen; xpageoffset++) {
      SIGMA[xpageoffset] = b_MI[xpageoffset];
    }
  }

  vlen = accData.size(0) * accData.size(1);
  accData.set_size(accData.size(0), 3);
  for (i = 0; i < vlen; i++) {
    accData[i] = (accData[i] - MI[i]) / SIGMA[i];
  }

  cutData(accData, acc1, acc2, acc3, acc4);
  b_signal.set_size(varargin_1.size(0), 3);
  vlen = varargin_1.size(0);
  for (i = 0; i < vlen; i++) {
    b_signal[i] = varargin_1[i];
  }

  vlen = varargin_2.size(0);
  for (i = 0; i < vlen; i++) {
    b_signal[i + b_signal.size(0)] = varargin_2[i];
  }

  vlen = varargin_3.size(0);
  for (i = 0; i < vlen; i++) {
    b_signal[i + b_signal.size(0) * 2] = varargin_3[i];
  }

  // This function is used to normalize the signal with respect to its own
  vlen = b_signal.size(0);
  if (b_signal.size(0) == 0) {
    mi[0] = 0.0;
    mi[1] = 0.0;
    mi[2] = 0.0;
  } else {
    for (b_i = 0; b_i < 3; b_i++) {
      xpageoffset = b_i * b_signal.size(0);
      mi[b_i] = b_signal[xpageoffset];
      for (k = 2; k <= vlen; k++) {
        mi[b_i] += b_signal[(xpageoffset + k) - 1];
      }
    }
  }

  mi[0] /= static_cast<double>(b_signal.size(0));
  mi[1] /= static_cast<double>(b_signal.size(0));
  mi[2] /= static_cast<double>(b_signal.size(0));
  coder::b_std(b_signal, sigma);
  MI.set_size(0, 3);
  SIGMA.set_size(0, 3);
  i = b_signal.size(0);
  for (b_i = 0; b_i < i; b_i++) {
    vlen = MI.size(0);
    b_MI.set_size((MI.size(0) + 1), 3);
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      for (k = 0; k < vlen; k++) {
        b_MI[k + b_MI.size(0) * xpageoffset] = MI[k + MI.size(0) * xpageoffset];
      }
    }

    b_MI[MI.size(0)] = mi[0];
    b_MI[MI.size(0) + b_MI.size(0)] = mi[1];
    b_MI[MI.size(0) + b_MI.size(0) * 2] = mi[2];
    MI.set_size(b_MI.size(0), 3);
    vlen = b_MI.size(0) * b_MI.size(1);
    for (xpageoffset = 0; xpageoffset < vlen; xpageoffset++) {
      MI[xpageoffset] = b_MI[xpageoffset];
    }

    vlen = SIGMA.size(0);
    b_MI.set_size((SIGMA.size(0) + 1), 3);
    for (xpageoffset = 0; xpageoffset < 3; xpageoffset++) {
      for (k = 0; k < vlen; k++) {
        b_MI[k + b_MI.size(0) * xpageoffset] = SIGMA[k + SIGMA.size(0) *
          xpageoffset];
      }
    }

    b_MI[SIGMA.size(0)] = sigma[0];
    b_MI[SIGMA.size(0) + b_MI.size(0)] = sigma[1];
    b_MI[SIGMA.size(0) + b_MI.size(0) * 2] = sigma[2];
    SIGMA.set_size(b_MI.size(0), 3);
    vlen = b_MI.size(0) * b_MI.size(1);
    for (xpageoffset = 0; xpageoffset < vlen; xpageoffset++) {
      SIGMA[xpageoffset] = b_MI[xpageoffset];
    }
  }

  vlen = b_signal.size(0) * b_signal.size(1);
  b_signal.set_size(b_signal.size(0), 3);
  for (i = 0; i < vlen; i++) {
    b_signal[i] = (b_signal[i] - MI[i]) / SIGMA[i];
  }

  cutData(b_signal, MI, SIGMA, b_MI, grad4);

  // spectr1 = abs(fft(acc1));
  // spectr1 = spectr1(1:(ceil(length(spectr1))/2), :);
  // freq1 = linspace(0, 1, length(spectr1));
  // spectr2 = abs(fft(acc2));
  // spectr2 = spectr2(1:(ceil(length(spectr2))/2), :);
  // freq2 = linspace(0, 1, length(spectr2));
  // spectr3 = abs(fft(acc3));
  // spectr3 = spectr3(1:(ceil(length(spectr3))/2), :);
  // freq3 = linspace(0, 1, length(spectr3));
  // spectr4 = abs(fft(acc4));
  // spectr4 = spectr4(1:(ceil(length(spectr4))/2), :);
  // freq4 = linspace(0, 1, length(spectr4));
  // meanSpectr1 = (freq1 * spectr1)./(sum(freq1));
  // meanSpectr2 = (freq2 * spectr2)./(sum(freq2));
  // meanSpectr3 = (freq3 * spectr3)./(sum(freq3));
  // meanSpectr4 = (freq4 * spectr4)./(sum(freq4));
  vlen = acc1.size(0);
  if (acc1.size(0) == 0) {
    mi[0] = 0.0;
    mi[1] = 0.0;
    mi[2] = 0.0;
  } else {
    for (b_i = 0; b_i < 3; b_i++) {
      xpageoffset = b_i * acc1.size(0);
      mi[b_i] = acc1[xpageoffset];
      for (k = 2; k <= vlen; k++) {
        mi[b_i] += acc1[(xpageoffset + k) - 1];
      }
    }
  }

  vlen = acc2.size(0);
  if (acc2.size(0) == 0) {
    sigma[0] = 0.0;
    sigma[1] = 0.0;
    sigma[2] = 0.0;
  } else {
    for (b_i = 0; b_i < 3; b_i++) {
      xpageoffset = b_i * acc2.size(0);
      sigma[b_i] = acc2[xpageoffset];
      for (k = 2; k <= vlen; k++) {
        sigma[b_i] += acc2[(xpageoffset + k) - 1];
      }
    }
  }

  vlen = acc3.size(0);
  if (acc3.size(0) == 0) {
    y[0] = 0.0;
    y[1] = 0.0;
    y[2] = 0.0;
  } else {
    for (b_i = 0; b_i < 3; b_i++) {
      xpageoffset = b_i * acc3.size(0);
      y[b_i] = acc3[xpageoffset];
      for (k = 2; k <= vlen; k++) {
        y[b_i] += acc3[(xpageoffset + k) - 1];
      }
    }
  }

  vlen = acc4.size(0);
  if (acc4.size(0) == 0) {
    b_y[0] = 0.0;
    b_y[1] = 0.0;
    b_y[2] = 0.0;
  } else {
    for (b_i = 0; b_i < 3; b_i++) {
      xpageoffset = b_i * acc4.size(0);
      b_y[b_i] = acc4[xpageoffset];
      for (k = 2; k <= vlen; k++) {
        b_y[b_i] += acc4[(xpageoffset + k) - 1];
      }
    }
  }

  vlen = MI.size(0);
  if (MI.size(0) == 0) {
    c_y[0] = 0.0;
    c_y[1] = 0.0;
    c_y[2] = 0.0;
  } else {
    for (b_i = 0; b_i < 3; b_i++) {
      xpageoffset = b_i * MI.size(0);
      c_y[b_i] = MI[xpageoffset];
      for (k = 2; k <= vlen; k++) {
        c_y[b_i] += MI[(xpageoffset + k) - 1];
      }
    }
  }

  vlen = SIGMA.size(0);
  if (SIGMA.size(0) == 0) {
    d_y[0] = 0.0;
    d_y[1] = 0.0;
    d_y[2] = 0.0;
  } else {
    for (b_i = 0; b_i < 3; b_i++) {
      xpageoffset = b_i * SIGMA.size(0);
      d_y[b_i] = SIGMA[xpageoffset];
      for (k = 2; k <= vlen; k++) {
        d_y[b_i] += SIGMA[(xpageoffset + k) - 1];
      }
    }
  }

  vlen = b_MI.size(0);
  if (b_MI.size(0) == 0) {
    e_y[0] = 0.0;
    e_y[1] = 0.0;
    e_y[2] = 0.0;
  } else {
    for (b_i = 0; b_i < 3; b_i++) {
      xpageoffset = b_i * b_MI.size(0);
      e_y[b_i] = b_MI[xpageoffset];
      for (k = 2; k <= vlen; k++) {
        e_y[b_i] += b_MI[(xpageoffset + k) - 1];
      }
    }
  }

  vlen = grad4.size(0);
  if (grad4.size(0) == 0) {
    f_y[0] = 0.0;
    f_y[1] = 0.0;
    f_y[2] = 0.0;
  } else {
    for (b_i = 0; b_i < 3; b_i++) {
      xpageoffset = b_i * grad4.size(0);
      f_y[b_i] = grad4[xpageoffset];
      for (k = 2; k <= vlen; k++) {
        f_y[b_i] += grad4[(xpageoffset + k) - 1];
      }
    }
  }

  coder::b_std(acc1, dv);
  coder::b_std(acc2, dv1);
  coder::b_std(acc3, dv2);
  coder::b_std(acc4, dv3);
  coder::b_std(MI, dv4);
  coder::b_std(SIGMA, dv5);
  coder::b_std(b_MI, dv6);
  coder::b_std(grad4, dv7);
  features[0] = mi[0] / static_cast<double>(acc1.size(0));
  features[3] = sigma[0] / static_cast<double>(acc2.size(0));
  features[6] = y[0] / static_cast<double>(acc3.size(0));
  features[9] = b_y[0] / static_cast<double>(acc4.size(0));
  features[12] = c_y[0] / static_cast<double>(MI.size(0));
  features[15] = d_y[0] / static_cast<double>(SIGMA.size(0));
  features[18] = e_y[0] / static_cast<double>(b_MI.size(0));
  features[21] = f_y[0] / static_cast<double>(grad4.size(0));
  features[24] = dv[0];
  features[27] = dv1[0];
  features[30] = dv2[0];
  features[33] = dv3[0];
  features[36] = dv4[0];
  features[39] = dv5[0];
  features[42] = dv6[0];
  features[45] = dv7[0];
  features[1] = mi[1] / static_cast<double>(acc1.size(0));
  features[4] = sigma[1] / static_cast<double>(acc2.size(0));
  features[7] = y[1] / static_cast<double>(acc3.size(0));
  features[10] = b_y[1] / static_cast<double>(acc4.size(0));
  features[13] = c_y[1] / static_cast<double>(MI.size(0));
  features[16] = d_y[1] / static_cast<double>(SIGMA.size(0));
  features[19] = e_y[1] / static_cast<double>(b_MI.size(0));
  features[22] = f_y[1] / static_cast<double>(grad4.size(0));
  features[25] = dv[1];
  features[28] = dv1[1];
  features[31] = dv2[1];
  features[34] = dv3[1];
  features[37] = dv4[1];
  features[40] = dv5[1];
  features[43] = dv6[1];
  features[46] = dv7[1];
  features[2] = mi[2] / static_cast<double>(acc1.size(0));
  features[5] = sigma[2] / static_cast<double>(acc2.size(0));
  features[8] = y[2] / static_cast<double>(acc3.size(0));
  features[11] = b_y[2] / static_cast<double>(acc4.size(0));
  features[14] = c_y[2] / static_cast<double>(MI.size(0));
  features[17] = d_y[2] / static_cast<double>(SIGMA.size(0));
  features[20] = e_y[2] / static_cast<double>(b_MI.size(0));
  features[23] = f_y[2] / static_cast<double>(grad4.size(0));
  features[26] = dv[2];
  features[29] = dv1[2];
  features[32] = dv2[2];
  features[35] = dv3[2];
  features[38] = dv4[2];
  features[41] = dv5[2];
  features[44] = dv6[2];
  features[47] = dv7[2];
}

void computeFeatures_initialize()
{
}

void computeFeatures_terminate()
{
  // (no terminate code required)
}

// End of code generation (computeFeatures.cpp)
