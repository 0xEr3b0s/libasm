# x86_64 Registers (Intel Syntax)

### Historical General Purpose Registers (R0 to R7)

| 64-bit Register | 32-bit Sub-reg | 16-bit Sub-reg | 8-bit Sub-reg (Low) | 8-bit Sub-reg (High) | Main Role / Calling Convention |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **RAX** | EAX | AX | AL | AH | Accumulator / Function return value / System call |
| **RBX** | EBX | BX | BL | BH | Base Register (callee-saved) |
| **RCX** | ECX | CX | CL | CH | Counter (loops) / 4th function argument |
| **RDX** | EDX | DX | DL | DH | Data (I/O, div/mul) / 3rd function argument |
| **RSI** | ESI | SI | SIL | *N/A* | Source Index (strings) / 2nd function argument |
| **RDI** | EDI | DI | DIL | *N/A* | Destination Index (strings) / 1st function argument |
| **RBP** | EBP | BP | BPL | *N/A* | Base Pointer (stack frame) / Callee-saved |
| **RSP** | ESP | SP | SPL | *N/A* | Stack Pointer (current top of the stack) |

### New x86_64 Registers (R8 to R15)

| 64-bit Register | 32-bit Sub-reg | 16-bit Sub-reg | 8-bit Sub-reg | Main Role / Calling Convention |
| :--- | :--- | :--- | :--- | :--- |
| **R8** | R8D | R8W | R8B | 5th function argument |
| **R9** | R9D | R9W | R9B | 6th function argument |
| **R10** | R10D | R10W | R10B | Temporary register (caller-saved) |
| **R11** | R11D | R11W | R11B | Temporary register (caller-saved) |
| **R12** | R12D | R12W | R12B | General purpose (callee-saved) |
| **R13** | R13D | R13W | R13B | General purpose (callee-saved) |
| **R14** | R14D | R14W | R14B | General purpose (callee-saved) |
| **R15** | R15D | R15W | R15B | General purpose (callee-saved) |

### Special Registers & Pointers

| Register | Size | Main Role |
| :--- | :--- | :--- |
| **RIP** | 64 bits | Instruction Pointer (points to the next instruction) |
| **RFLAGS** | 64 bits | Status register containing flags (e.g., ZF, CF, SF, OF) |
