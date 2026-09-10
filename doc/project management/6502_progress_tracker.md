# 6502 / 65C02 Emulator — Instruction Tracker

Reference: `6502_Instruction_Set.htm` (masswerk.at)
Scope: **NMOS 6502** base instruction set (56 mnemonics / 151 opcodes) + **CMOS 65C02 (WDC)** additions. Illegal/undocumented NMOS opcodes are intentionally **not** tracked here.

## How to use this

Edit cells directly. Suggested values:

- **Coded**: ` ` empty / `y` / `wip`
- **Tested**: ` ` empty / `y` / `partial`
- **Comments**: bugs, edge cases, "copy-paste of X", flag behavior gotchas, etc.

Tip: use VS Code's multi-cursor or a quick find/replace to flip statuses as you go. Sort/filter manually — it's just a table, nothing fancy.

Legend for addressing-mode abbreviations: `#` immediate, `zpg` zero page, `zpg,X`/`zpg,Y` zero page indexed, `abs` absolute, `abs,X`/`abs,Y` absolute indexed, `ind` indirect, `X,ind` indexed indirect, `ind,Y` indirect indexed, `rel` relative, `A` accumulator, `impl` implied. CMOS-only modes: `(zpg)` zero-page indirect, `(abs,X)` absolute indexed indirect, `zpg,rel` zero-page + relative.

---

## Load / Store

| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| LDA | $A9 #, $A5 zpg, $B5 zpg,X, $AD abs, $BD abs,X, $B9 abs,Y, $A1 X,ind, $B1 ind,Y | | | | |
| LDX | $A2 #, $A6 zpg, $B6 zpg,Y, $AE abs, $BE abs,Y | | | | |
| LDY | $A0 #, $A4 zpg, $B4 zpg,X, $AC abs, $BC abs,X | | | | |
| STA | $85 zpg, $95 zpg,X, $8D abs, $9D abs,X, $99 abs,Y, $81 X,ind, $91 ind,Y | | | | |
| STX | $86 zpg, $96 zpg,Y, $8E abs | | | | |
| STY | $84 zpg, $94 zpg,X, $8C abs | | | | |

## Arithmetic

| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| ADC | $69 #, $65 zpg, $75 zpg,X, $6D abs, $7D abs,X, $79 abs,Y, $61 X,ind, $71 ind,Y | `yes` | `v1` | | |
| SBC | $E9 #, $E5 zpg, $F5 zpg,X, $ED abs, $FD abs,X, $F9 abs,Y, $E1 X,ind, $F1 ind,Y | `yes` | `v1` | | |

## Increment / Decrement

| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| INC | $E6 zpg, $F6 zpg,X, $EE abs, $FE abs,X | | | | |
| DEC | $C6 zpg, $D6 zpg,X, $CE abs, $DE abs,X | | | | |
| INX | $E8 impl | | | | |
| INY | $C8 impl | | | | |
| DEX | $CA impl | | | | |
| DEY | $88 impl | | | | |

## Shifts / Rotates

| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| ASL | $0A A, $06 zpg, $16 zpg,X, $0E abs, $1E abs,X |`yes` |`v1` | | |
| LSR | $4A A, $46 zpg, $56 zpg,X, $4E abs, $5E abs,X | | | | |
| ROL | $2A A, $26 zpg, $36 zpg,X, $2E abs, $3E abs,X | | | | |
| ROR | $6A A, $66 zpg, $76 zpg,X, $6E abs, $7E abs,X | | | | |

## Logical

| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| AND | $29 #, $25 zpg, $35 zpg,X, $2D abs, $3D abs,X, $39 abs,Y, $21 X,ind, $31 ind,Y | | | | |
| ORA | $09 #, $05 zpg, $15 zpg,X, $0D abs, $1D abs,X, $19 abs,Y, $01 X,ind, $11 ind,Y | | | | |
| EOR | $49 #, $45 zpg, $55 zpg,X, $4D abs, $5D abs,X, $59 abs,Y, $41 X,ind, $51 ind,Y | | | | |
| BIT | $24 zpg, $2C abs | | | | |

## Compare

| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| CMP | $C9 #, $C5 zpg, $D5 zpg,X, $CD abs, $DD abs,X, $D9 abs,Y, $C1 X,ind, $D1 ind,Y | | | | |
| CPX | $E0 #, $E4 zpg, $EC abs | | | | |
| CPY | $C0 #, $C4 zpg, $CC abs | | | | |

## Branches

| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| BCC | $90 rel | `yes` | `v1` |  | |
| BCS | $B0 rel | `yes` | `v1` |  | copy-paste edit of BCC |
| BEQ | $F0 rel | `yes` | `v1` |  | copy-paste edit of BCC |
| BNE | $D0 rel | `yes` | `v1` | | |
| BMI | $30 rel | `yes` | `v1` | | |
| BPL | $10 rel | `yes` | `v1` | | |
| BVC | $50 rel | `yes` | `v1` | | |
| BVS | $70 rel | `yes` | `v1` | | |

***Comments***:
- Check RELATIVE addressing mode modalities: when is a page crossed if the instruction straddles page, and make sure PC + offset should have + 1 added 
- All of these v1 functions are copy-paste edits of the original BCC implementation, so check all of them if duplicated code is buggy


## Jumps / Subroutines / Interrupts

| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| JMP | $4C abs, $6C ind | | | | |
| JSR | $20 abs | | | | |
| RTS | $60 impl | | | | |
| BRK | $00 impl | | | | |
| RTI | $40 impl | | | | |

## Stack / Register Transfers

| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| PHA | $48 impl | | | | |
| PLA | $68 impl | | | | |
| PHP | $08 impl | | | | |
| PLP | $28 impl | | | | |
| TAX | $AA impl | | | | |
| TAY | $A8 impl | | | | | 
| TXA | $8A impl | | | | |
| TYA | $98 impl | | | | |
| TSX | $BA impl | | | | |
| TXS | $9A impl | | | | |

## Flags

| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| CLC | $18 impl | `yes` |`v1` | | |
| SEC | $38 impl | `yes` |`v1` | | |
| CLD | $D8 impl | `yes` |`v1` | | |
| SED | $F8 impl | `yes` |`v1` | | |
| CLI | $58 impl | `yes` |`v1` | | |
| SEI | $78 impl | `yes` |`v1` | | |
| CLV | $B8 impl | `yes` |`v1` | | |

***Comments***:
- All instructions are copy-paste edits of the CLC implementation. In case of bugs, check that all dependent code is fixed.

## Other

| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| NOP | $EA impl | | | | |

---

## CMOS (65C02 / WDC) — new mnemonics


| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| BRA | $80 rel | | | | |
| STZ | $64 zpg, $74 zpg,X, $9C abs, $9E abs,X | | | | |
| TSB | $04 zpg, $0C abs | | | | |
| TRB | $14 zpg, $1C abs | | | | |
| PHX | $DA impl | | | | |
| PLX | $FA impl | | | | |
| PHY | $5A impl | | | | |
| PLY | $7A impl | | | | |
| WAI | $CB impl | | | | |
| STP | $DB impl | | | | |
| RMB0–RMB7 | $07,$17,$27,$37,$47,$57,$67,$77 (zpg) | | | | |
| SMB0–SMB7 | $87,$97,$A7,$B7,$C7,$D7,$E7,$F7 (zpg) | | | | |
| BBR0–BBR7 | $0F,$1F,$2F,$3F,$4F,$5F,$6F,$7F (zpg,rel) | | | | |
| BBS0–BBS7 | $8F,$9F,$AF,$BF,$CF,$DF,$EF,$FF (zpg,rel) | | | | |

## CMOS (65C02 / WDC) — new addressing modes on existing NMOS mnemonics


| Mnemonic | Opcodes (mode) | Coded | Version | Tested | Comments |
|---|---|---|---|---|---|
| ORA | $12 (zpg) | | | | |
| AND | $32 (zpg) | | | | |
| EOR | $52 (zpg) | | | | |
| ADC | $72 (zpg) | | | | |
| STA | $92 (zpg) | | | | |
| LDA | $B2 (zpg) | | | | |
| CMP | $D2 (zpg) | | | | |
| SBC | $F2 (zpg) | | | | |
| BIT | $89 #, $34 zpg,X, $3C abs,X | | | | |
| INC | $1A A | | | | |
| DEC | $3A A | | | | |
| JMP | $7C (abs,X) | | | | |

---

## Known bugs / cross-cutting issues

- [ ]
- [ ]
- [ ]

## General notes

-