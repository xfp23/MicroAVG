---

[中文](./readme.zh.md)

---

# MicroAVG — Sliding Average Component

## Overview

**MicroAVG** is a lightweight, deterministic sliding average filter designed for embedded systems.

It is intended to be used as a reusable component for smoothing physical-domain signals such as temperature, pressure, voltage, or current.

MicroAVG is **not tied to ADC hardware** and does **not use dynamic memory allocation**.

---

## Key Features

* Fixed-size sliding window (compile-time configurable)
* No dynamic memory allocation
* User-configurable sample data type
* Deterministic execution time
* Platform and signal-source independent

---

## Configuration

All user configuration is done in **`MicroAVG_conf.h`**.
Do **not** modify component source files.

### 1. Window Depth

```c
#define MICROAVG_DEPTH 200
```

* Defines the number of samples used for averaging
* Larger values increase smoothing but require more RAM
* Must be greater than 0

---

### 2. Sample Value Type (Optional)

By default, MicroAVG uses `float` as the sample type.

You may override this by defining `MICROAVG_VALUE_T`:

```c
#define MICROAVG_VALUE_T float
```

Examples:

```c
#define MICROAVG_VALUE_T int16_t   // Fixed-point input
#define MICROAVG_VALUE_T int32_t
```

> ⚠️ The sample type represents **physical-domain values**, not raw ADC codes.

---

### 3. Advanced Configuration (Optional)

The accumulator type is internally separated from the sample type to ensure numerical safety.

Advanced users may override it if necessary:

```c
#define MICROAVG_ACC_T float
```

> ⚠️ Do not change this unless you fully understand the numeric range of your data.

---

## Usage

### 1. Declare an Object

```c
MicroAVG_Obj_t avg;
```

---

### 2. Initialize

Call once before use, typically during system initialization:

```c
MicroAVG_Init(&avg);
```

---

### 3. Update with New Samples

Call `MicroAVG_Update()` whenever a new sample is available:

```c
float filtered;

filtered = MicroAVG_Update(&avg, input_value);
```

* Pushes a new sample into the sliding window
* Updates internal state
* Returns the current averaged result

---

### 4. Reset When Needed

To clear internal history and restart averaging:

```c
MicroAVG_Reset(&avg);
```

Typical use cases:

* Mode changes
* Sensor recovery
* Control logic reset
* Debug or forced-control transitions

Reset clears internal state but **keeps configuration unchanged**.

---

## Design Notes

* MicroAVG operates on **physical-domain values**, not raw sensor codes
* The component maintains no external dependencies
* Output value is returned directly by `MicroAVG_Update()`
* Internal buffer contents are implementation details and not part of the API

---

## Typical Data Flow

```text
ADC Raw Data
    ↓
Physical Unit Conversion
    ↓
MicroAVG_Update()
    ↓
Control / Monitoring / Reporting
```

---

## License

Copyright (c) 2026
Author: [https://github.com/xfp23](https://github.com/xfp23)

---
