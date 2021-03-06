/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_NNACL_ACTIVATION_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_NNACL_ACTIVATION_H_

#include <math.h>
#include "src/runtime/kernel/arm/nnacl/op_base.h"
#include "src/runtime/kernel/arm/nnacl/errorcode.h"
#include "src/runtime/kernel/arm/nnacl/quantization/fixed_point.h"

struct ActivationParameter {
  OpParameter op_parameter_;
  int type_;
  float alpha_{0.2};
};

inline int Relu(const float *src, int length, float *dst) {
  for (int i = 0; i < length; ++i) {
    dst[i] = src[i] > 0 ? src[i] : 0;
  }
  return NNACL_OK;
}

inline int Relu6(const float *src, int length, float *dst) {
  for (int i = 0; i < length; ++i) {
    if (src[i] < 0) {
      dst[i] = 0;
    } else {
      dst[i] = src[i] > 6.0f ? 6.0f : src[i];
    }
  }
  return NNACL_OK;
}

inline int LRelu(const float *src, int length, float *dst, float alpha) {
  for (int i = 0; i < length; ++i) {
    dst[i] = src[i] > 0 ? src[i] : (src[i] * alpha);
  }
  return NNACL_OK;
}

inline int Sigmoid(const float *src, int length, float *dst) {
  for (int i = 0; i < length; ++i) {
    dst[i] = 1.0f / (1.0f + exp(-src[i]));
  }
  return NNACL_OK;
}

inline int Tanh(const float *src, int length, float *dst) {
  for (int i = 0; i < length; ++i) {
    dst[i] = 1.0f - 2.0f / (exp(2 * src[i]) + 1);
  }
  return NNACL_OK;
}

inline int HSwish(const float *src, int length, float *dst) {
  for (int i = 0; i < length; ++i) {
    float in = src[i];
    float relu6 = MSMIN(MSMAX(in + 3, 0), 6);
    dst[i] = in * relu6 / 6;
  }
  return NNACL_OK;
}

#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_NNACL_ACTIVATION_H_
