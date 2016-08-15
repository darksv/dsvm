Dead Simple Virtual Machine (DSVM)
==================================

Bytecode
--------

### Opcodes
|#     | Code | Syntax                |         Description                   |
|------|------|-----------------------|---------------------------------------|
| 0x00 | in   | in *dst*              | read from stdin into *dst*            |
| 0x01 | mov  | mov *dst*, *src*      | move value from *src* to *dst*        |
| 0x02 | add  | add *dst*, *e1*, *e2* | store sum of *e1* and *e2* in *dst*   |
| 0x03 | out  | out *src*             | write value from *src* to stdout      |
| 0x04 | jmp  | jmp *addr*            | jump to *addr*                        |
| 0xFF | nop  | nop                   | do nothing                            |

### Operands
Every instruction has zero or more operands. They are provided via comma-separated list.
Each operand contains immutable data or register identifier followed by data type alias that could be ommited
(it is *u32* by default).

Example instructions:
```
in r0:f32
mov r1:f32, 666
add r0:f32, r0:f32, r1:f32
out r0:f32
```

#### Operand flags
```
0000 0000
     ^^^^ data type
   ^      set when pointer
 ^^       reserved
^         set when value is in register
```

#### Data types

| Byte      | Description             | Alias   |
|:---------:|:------------------------|:-------:|
| 0x01      |  8-bit signed integer   | i8      |
| 0x02      | 16-bit signed integer   | i16     |
| 0x03      | 32-bit signed integer   | i32     |
| 0x04      | 64-bit signed integer   | i64     |
| 0x05      |  8-bit unsigned integer | u8      |
| 0x06      | 16-bit unsigned integer | u16     |
| 0x07      | 32-bit unsigned integer | u32     |
| 0x08      | 64-bit unsigned integer | u64     |
| 0x09      | 32-bit float            | f32     |
| 0x0A      | 64-bit float            | f64     |
| 0x0B-0x0F | *reserved*              |         |

#### Number literals

| Type     | Example |
|:--------:|:-------:|
| integral | 1234    |
| floating | 12.34   |

#### TODOs
- [x] implement disassebler
- [ ] implement interpreter
- [ ] rewrite compiler from Python to C++
- [ ] add more instructions
- [ ] add support for functions
- [ ] add support for concurrency
- [ ] ...