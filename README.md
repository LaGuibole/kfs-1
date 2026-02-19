## La GDT : Global Descriptor Table : 

Implementation de la GDT selon OSDev : 

Offset                  Entree                  Access Byte                 Flags
___
`0x0000`                Null Descriptor        `0x00`                       `0x0`
___
`0x0008`                Kernel Code(ring 0)    `0x9A`                       `0xC`
___
`0x0010`                Kernel Datae(ring 0)   `0x92`                       `0xC`
___
`0x0018`                User Code(ring 3)      `0xFA`                       `0xC`
___
`0x0020`                User Data(ring 3)      `0xF2`                       `0xC`
___
`0x0028`                TSS                    `0x89`                       `0x0`
___

Pour KFS-1 on a pas besoin ni du UserMode, ni TSS, on va se concentrer sur les 3 premieres entrees

___

**Structure d'un descripteur**

Un descripteur fait `8 octets`

```
Byte 0-1 : Limit [15:0]
Byte 2-4 : Base  [23:0]
Byte 5   : Access Byte
Byte 6   : Flags (bits 7:4) + Limit [19:16] (bits 3:0)
Byte 7   : Base  [31:24]
```

**Access Byte decompose**

```
Bit 7 : Present (P)     → 1 si le segment est valide
Bit 6-5 : DPL           → privilege level (0=kernel, 3=user)
Bit 4 : Descriptor Type → 1 pour code/data, 0 pour système
Bit 3 : Executable      → 1 pour code, 0 pour data
Bit 2 : Direction/Conforming
Bit 1 : Readable/Writable
Bit 0 : Accessed        → mis à 1 par le CPU automatiquement
```

*Par exemple*

`0x9A` = `1001 1010` = Present + DPL0 + Type=1 + Executable + Readable
`0x92` = `1001 0010` = Present + DPL0 + Type=1 + Data + Wrtiable

**Les flags**

```
Bit 3 : Granularity → 1 = limite en pages de 4KB (donc limit 0xFFFFF = 4GB)
Bit 2 : Size        → 1 = 32-bit protected mode
Bit 1 : Long mode   → 1 pour 64-bit (et Size doit être 0)
Bit 0 : AVL         → dispo pour l'OS
```

`0xC` = `1100` = Granularite + 32-bit
