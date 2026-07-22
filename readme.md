---

[中文](./readme.zh.md)

---

# MicroAVG — Sliding Average Component

## Overview

**MicroAVG** is a lightweight, deterministic sliding average filter designed for embedded systems.

It is intended to be used as a reusable component for smoothing physical-domain signals such as temperature, pressure, voltage, or current.

MicroAVG is **not tied to ADC hardware**, does **not use dynamic memory allocation**, and is suitable for **ISR-driven data paths**.

---

## Key Features

* Fixed-size sliding window (compile-time configurable)
* No dynamic memory allocation
* User-configurable sample data type
* Deterministic execution time (O(1) per update)
* ISR-friendly update path (no division)
* Platform and signal-source independent

---

## Configuration

All user configuration is done in **`MicroAVG_conf.h`**.
Do **not** modify component source files.

---

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
#define MICROAVG_VALUE_T int16_t   // Fixed-point physical values
#define MICROAVG_VALUE_T int32_t
```

> ⚠️ The sample type represents **physical-domain values**, not raw ADC codes.

---

### 3. Accumulator Type (Advanced)

The accumulator type is internally separated from the sample type to ensure numerical safety.

Advanced users may override it if necessary:

```c
#define MICROAVG_ACC_T float
```

> ⚠️ Do not change this unless you fully understand the numeric range and overflow risk of your data.

---

## API Usage

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

* Clears internal buffer and state
* Must be called before any update or read operation

---

### 3. Update with New Samples (ISR-safe)

Call `MicroAVG_Update()` whenever a new sample is available.

```c
MicroAVG_Update(&avg, input_value);
```

* Pushes a new sample into the sliding window
* Updates internal sum, index, and count
* **Does not perform division**
* Designed to be safely callable from an interrupt context

Return value:

```c
MICROAVG_OK        // Update successful
MICROAVG_ERR       // Invalid object pointer
```

---

### 4. Get Averaged Result (Non-ISR)

Retrieve the current averaged result using:

```c
MicroAVG_Value_t result;

result  = MicroAVG_GetResult(&avg);
```

> ℹ️ This API performs division and is intended for **non-interrupt context** (task / main loop).

---

### 5. Reset When Needed

To clear internal history and restart averaging:

```c
MicroAVG_Reset(&avg);
```

Typical use cases:

* Mode transitions
* Sensor recovery
* Control logic reinitialization
* Debug or forced-control transitions

Reset clears internal state but **keeps configuration unchanged**.

---

## Design Notes

* MicroAVG operates on **physical-domain values**, not raw sensor codes
* Update and result computation are intentionally separated
* ISR path contains only constant-time arithmetic operations
* Division is deferred to non-real-time context
* Internal buffer layout is an implementation detail and not part of the API

---

## Typical Data Flow

```text
ADC Raw Data
    ↓
Physical Unit Conversion
    ↓
MicroAVG_Update()   (ISR / fast path)
    ↓
MicroAVG_GetResult() (task / main loop)
    ↓
Control / Monitoring / Logging
```

---

## License

Copyright (c) 2026
Author: [https://xfp23.github.io](https://xfp23.github.io)

---
