---

[English](./readme.md)

---

# MicroAVG — 滑动平均组件

## 概述

**MicroAVG** 是一个轻量级、确定性的滑动平均滤波组件，专为嵌入式系统设计。

它被设计为一个可复用的组件，用于对**物理域信号**（如温度、压力、电压或电流）进行平滑处理。

MicroAVG **不依赖 ADC 硬件**，并且**不使用动态内存分配**。

---

## 主要特性

* 固定大小的滑动窗口（编译期可配置）
* 无动态内存分配
* 用户可配置的采样数据类型
* 确定性的执行时间
* 平台无关、信号源无关

---

## 配置

所有用户配置均在 **`MicroAVG_conf.h`** 中完成。
**不要**修改组件源文件。

### 1. 窗口深度

```c
#define MICROAVG_DEPTH 200
```

* 定义参与平均计算的样本数量
* 数值越大，平滑效果越强，但占用的 RAM 越多
* 必须大于 0

---

### 2. 采样值类型（可选）

默认情况下，MicroAVG 使用 `float` 作为采样类型。

你可以通过定义 `MICROAVG_VALUE_T` 进行覆盖：

```c
#define MICROAVG_VALUE_T float
```

示例：

```c
#define MICROAVG_VALUE_T int16_t   // 定点输入
#define MICROAVG_VALUE_T int32_t
```

> ⚠️ 采样类型表示的是**物理域数值**，而不是原始 ADC 码值。

---

### 3. 高级配置（可选）

为了保证数值安全性，内部累加器类型与采样类型是分离的。

高级用户在确有需要时可以覆盖该类型：

```c
#define MICROAVG_ACC_T float
```

> ⚠️ 除非你完全理解数据的数值范围，否则不要修改该项。

---

## 使用方法

### 1. 声明对象

```c
MicroAVG_Obj_t avg;
```

---

### 2. 初始化

在使用前调用一次，通常在系统初始化阶段完成：

```c
MicroAVG_Init(&avg);
```

---

### 3. 更新新样本

每当有新的样本值时，调用 `MicroAVG_Update()`：

```c
float filtered;

filtered = MicroAVG_Update(&avg, input_value);
```

* 将新样本压入滑动窗口
* 更新内部状态
* 返回当前的平均结果

---

### 4. 按需复位

用于清空内部历史数据并重新开始平均计算：

```c
MicroAVG_Reset(&avg);
```

典型使用场景：

* 工作模式切换
* 传感器恢复
* 控制逻辑复位
* 调试或强制控制切换

复位会清空内部状态，但**不会改变任何配置**。

---

## 设计说明

* MicroAVG 处理的是**物理域数值**，而非原始传感器码值
* 组件不依赖任何外部模块
* 输出值由 `MicroAVG_Update()` 直接返回
* 内部缓冲区内容属于实现细节，不属于 API 的一部分

---

## 典型数据流

```text
ADC 原始数据
    ↓
物理量转换
    ↓
MicroAVG_Update()
    ↓
控制 / 监控 / 上报
```

---

## 许可证

Copyright (c) 2026
作者：[https://github.com/xfp23](https://github.com/xfp23)

---
