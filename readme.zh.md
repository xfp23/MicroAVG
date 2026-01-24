---

[English](https://www.google.com/search?q=./readme.md)

---

# MicroAVG — 滑动平均滤波组件

## 概述

**MicroAVG** 是一个专为嵌入式系统设计的轻量级、确定性滑动平均滤波器。

它旨在作为一种可复用的组件，用于平滑物理域信号，如温度、压力、电压或电流。

MicroAVG **不绑定特定 ADC 硬件**，**不使用动态内存分配**，并且非常适合 **ISR（中断服务程序）驱动的数据路径**。

---

## 核心特性

* **固定大小滑动窗口**（编译时配置）
* **零动态内存分配**
* **用户可配置的数据类型**
* **确定性执行时间**（单次更新复杂度为 ）
* **ISR 友好型更新路径**（无除法运算）
* **平台无关**，支持任意信号源

---

## 配置说明

所有用户配置均在 **`MicroAVG_conf.h`** 中完成。
**请勿** 直接修改组件源码。

---

### 1. 窗口深度 (Window Depth)

```c
#define MICROAVG_DEPTH 200

```

* 定义用于平均的采样点数量。
* 值越大，平滑效果越好，但会增加 RAM 占用。
* 必须大于 0。

---

### 2. 采样值类型 (可选)

默认情况下，MicroAVG 使用 `float` 作为采样类型。

您可以通过定义 `MICROAVG_VALUE_T` 来覆盖此设置：

```c
#define MICROAVG_VALUE_T float

```

配置示例：

```c
#define MICROAVG_VALUE_T int16_t   // 适用于定点数物理值
#define MICROAVG_VALUE_T int32_t

```

> ⚠️ **注意**：采样类型代表的是 **物理域数值**，而非原始 ADC 原始码。

---

### 3. 累加器类型 (高级)

为了确保数值安全，累加器类型在内部与采样类型是分离的。

高级用户可以根据需要覆盖它：

```c
#define MICROAVG_ACC_T float

```

> ⚠️ **警告**：除非您完全了解数据的数值范围和溢出风险，否则请勿更改此项。

---

## API 使用指南

### 1. 声明对象

```c
MicroAVG_Obj_t avg;

```

---

### 2. 初始化

在使用前调用一次，通常放在系统初始化阶段：

```c
MicroAVG_Init(&avg);

```

* 清除内部缓冲区和状态。
* 必须在进行任何更新或读取操作前调用。

---

### 3. 更新采样值 (ISR 安全)

每当有新采样点可用时，调用 `MicroAVG_Update()`。

```c
MicroAVG_Update(&avg, input_value);

```

* 将新样本压入滑动窗口。
* 更新内部和、索引指针及计数器。
* **不执行除法运算**。
* 设计上支持在中断上下文中安全调用。

返回值：

```c
MICROAVG_OK       // 更新成功
MICROAVG_ERR      // 无效的对象指针

```

---

### 4. 获取平均结果 (非 ISR)

使用以下函数获取当前的平均计算结果：

```c
MicroAVG_Value_t result;
MicroAVG_Status_t status;

status = MicroAVG_GetResult(&avg, &result);

```

返回值：

* `MICROAVG_OK`
* 结果有效。


* `MICROAVG_DIVZERO_ERR`
* 尚未累积任何样本（`count == 0`）。
* 输出值被设为 0。


* `MICROAVG_ERR`
* 无效的指针。



> ℹ️ **提示**：此 API 涉及除法运算，建议在 **非中断上下文**（任务 / 主循环）中使用。

---

### 5. 重置 (Reset)

如果需要清除内部历史记录并重新开始平均计算：

```c
MicroAVG_Reset(&avg);

```

典型应用场景：

* 模式切换
* 传感器故障恢复
* 控制逻辑初始化
* 调试或强制状态转换

重置操作会清空内部状态，但 **保持配置参数不变**。

---

## 设计笔记

* **物理域运算**：MicroAVG 处理的是物理量，而非传感器原始码。
* **读写分离**：更新操作与结果计算在逻辑上是分离的。
* **高性能**：ISR 路径仅包含常数时间的算术运算。
* **延迟除法**：除法运算被推迟到非实时上下文中执行。
* **封装性**：内部缓冲区布局属于实现细节，不属于 API 的一部分。

---

## 典型数据流

```text
ADC 原始数据
    ↓
物理单位转换 (Physical Unit Conversion)
    ↓
MicroAVG_Update()    (ISR / 快速路径)
    ↓
MicroAVG_GetResult() (任务 / 主循环)
    ↓
控制 / 监测 / 日志

```

---

## 许可证

Copyright (c) 2026
作者: [https://github.com/xfp23](https://github.com/xfp23)

---
