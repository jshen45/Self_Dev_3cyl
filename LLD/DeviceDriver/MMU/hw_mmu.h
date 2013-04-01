#ifndef HW_MMU_H
#define HW_MMU_H

#include "reuse.h"

#define MMU_TBL_ENTRIES_MAX   (16)
#define MMU_MAS0_SPR          (624)
#define MMU_MAS1_SPR          (625)
#define MMU_MAS2_SPR          (626)
#define MMU_MAS3_SPR          (627)
#define MMU_MAS4_SPR          (628)
#define MMU_MAS6_SPR          (630)

//=============================================================================
// ID - Process ID Register (PID0)
//
// Base Offset : SPR 48
//
// Reset Value : all zero
//
// Field        Bits     Type   Description
// ========== =========  ==== =================================================
//             32�55          Reserved, should be cleared.
// PID         56-63
//
// The Book E architecture defines that a process ID (PID) value be associated with each
// effective address (instruction or data) generated by the processor. Book E defines one PID
// register that maintains the value of the PID for the current process. The number of PIDs
// implemented is indicated by the value of MMUCFG[NPIDS]. (The e200z6 defines no
// additional PID registers.) PID values are used to construct virtual addresses for accessing
// memory.
//
//=============================================================================
typedef struct MMU_PID_0_F_Tag
{
   bitfield32_t      :  BIT_24;
   bitfield32_t PID  :  BIT_8;

} MMU_PID_0_F_T;

typedef union MMU_PID_0_Tag
{
   MMU_PID_0_F_T   F;
   uint32_t        U32;
   uint16_t        U16[2];
   uint8_t         U8[4];

}MMU_PID_0_T;

//=============================================================================
// ID - MMU Control and Status Register 0 (MMUCSR0)
//
// Base Offset : SPR 1012
//
// Reset Value : all zero
//
// Field        Bits     Type   Description
// ========== =========  ==== =================================================
//             32�61          Reserved, should be cleared.
//
// TLB1_FI     62             TLB1 flash invalidate
//                            0 No flash invalidate
//                            1 TLB1 invalidation operation
//                            TLB1 invalidation operation. Hardware initiates a TLB1 invalidation, 
//                            after which TLB1_FI is cleared.Setting TLB1_FI while an invalidation 
//                            operation is in progress causes an undefined operation. Clearing TLB1_FI 
//                            while an invalidation operation is in progress is ignored. TLB1 
//                            invalidation operations require 3 cycles to complete.
//
//             63             Reserved, should be cleared.
//
//=============================================================================
typedef struct MMU_CSR0_F_Tag
{
   bitfield32_t          :  BIT_30;
   bitfield32_t TLB1_FI  :  BIT_1;
   bitfield32_t          :  BIT_1;

} MMU_CSR0_F_T;

typedef union MMU_CSR0_Tag 
{
   MMU_CSR0_F_T  F;
   uint32_t      U32;
   uint16_t      U16[2];
   uint8_t       U8[4];

}MMU_CSR0_T;
        
//=============================================================================
// ID - MMU Configuration Register (MMUCFG)
//
// Base Offset : SPR 1015
//
// Reset Value : undefined
//
// Field        Bits     Type   Description
// ========== =========  ==== =================================================
//             32�48          Reserved, should be cleared.
//
// NPIDS       49�52          Number of PID registers
//                            0001 This version of the MMU implements one PID 
//                                  register (PID0).
//
// PIDSIZE     53�57          PID register size
//                            00111 PID registers contain 8 bits in this 
//                                  version of the MMU.
//
//             58�59          Reserved, should be cleared.
//
// NTLBS       60�61          Number of TLBs
//                            01 This version of the MMU implements two TLB 
//                               structures: a null TLB0 and a populated TLB1.
//
// MAVN        62�63          MMU architecture version number
//                            00 This version of the MMU implements version 1.0 
//                               of the Motorola Book E MMU architecture.
//
//=============================================================================
typedef struct MMU_CFG_F_Tag
{
   bitfield32_t         :  BIT_17;
   bitfield32_t NPIDS   :  BIT_4;
   bitfield32_t PIDSIZE :  BIT_5;
   bitfield32_t         :  BIT_2;
   bitfield32_t NLTBS   :  BIT_2;
   bitfield32_t MAVN    :  BIT_2;

} MMU_CFG_F_T;

typedef union MMU_CFG_Tag 
{
   MMU_CFG_F_T F;
   uint32_t    U32;
   uint16_t    U16[2];
   uint8_t     U8[4];

}MMU_CFG_T;

//=============================================================================
// ID - TLB Configuration Register 1 (TLB1CFG)
//
// Base Offset : SPR 689
//
// Reset Value : undefined
//
// Field        Bits     Type   Description
// ========== =========  ==== =================================================
// ASSOC       32�39          Associativity
//                            0x8 - Indicates that TLB1 associativity is 8
//                            0x10 Indicates that TLB1 associativity is 16
//
// MINSIZE     40�43          Minimum page size
//                            0x1 Smallest page size is 4 Kbytes.
//
// MAXSIZE     44�47          Maximum page size
//                            0x9 Largest page size is 256 Mbytes.
//                            0xb - Largest page size is 4 Gbytes.
//
// IPROT       48             Invalidate protect capability
//                            1 Invalidate protect capability is supported in TLB1.
//
// AVAIL       49             Page size availability
//                            1 All page sizes between MINSIZE and MAXSIZE are 
//                               supported.
//
//             50�51          Reserved, should be cleared.
//
// NENTRY      52�63          Number of entries
//                            0x8 - TLB1 contains 8 entries.
//                            0x010 TLB1 contains 16 entries.
//
//=============================================================================
typedef struct MMU_TLB1_CFG_F_Tag
{
   bitfield32_t ASSOC   :  BIT_8;
   bitfield32_t MINSIZE :  BIT_4;
   bitfield32_t MAXSIZE :  BIT_4;
   bitfield32_t IPROT   :  BIT_1;
   bitfield32_t AVAIL   :  BIT_1;
   bitfield32_t         :  BIT_2;
   bitfield32_t NENTRY  :  BIT_12;

} MMU_TLB1_CFG_F_T;

typedef union MMU_TLB1_CFG_Tag 
{
   MMU_TLB1_CFG_F_T   F;
   uint32_t           U32;
   uint16_t           U16[2];
   uint8_t            U8[4];

}MMU_TLB1_CFG_T;

//=============================================================================
// ID - MAS0 � MMU Read/Write and Replacement Control
//
// Base Offset : SPR 624
//
// Reset Value : undefined
//
// Field        Bits     Type   Description
// ========== =========  ==== =================================================
//            32�33           Reserved, should be cleared.
//
// TLBSEL     34�35           Selects TLB for access
//                            01 TLB1 (ignored by the e200z3, should be 
//                            written to 01 for future compatibility)
//
//            36�42           Reserved, should be cleared.
//
// ESEL       43�47           Entry select for TLB1
//
//            48�59           Reserved, should be cleared.
//
// NV         60�63           Next replacement victim for TLB1 (software managed). 
//                            Software updates this field; it is copied to the ESEL 
//                            field on a TLB error
//
//=============================================================================
typedef struct MMU_MAS0_F_Tag
{
   bitfield32_t         :  BIT_2;
   bitfield32_t TLBSEL  :  BIT_2;
   bitfield32_t         :  BIT_7;
   bitfield32_t ESEL    :  BIT_5;
   bitfield32_t         :  BIT_12;
   bitfield32_t NV      :  BIT_4;

} MMU_MAS0_F_T;

typedef union MMU_MAS0_Tag 
{
   MMU_MAS0_F_T   F;
   uint32_t       U32;
   uint16_t       U16[2];
   uint8_t        U8[4];

}MMU_MAS0_T;

//=============================================================================
// ID - MAS1 � Descriptor Context and Configuration Control
//
// Base Offset : SPR 625
//
// Reset Value : undefined
//
// Field        Bits     Type   Description
// ========== =========  ==== =================================================
// VALID       32             TLB entry valid
//                            0 This TLB entry is invalid.
//                            1 This TLB entry is valid.
//
// IPROT       33             Invalidation protect
//                            0 Entry is not protected from invalidation.
//                            1 Entry is protected from invalidation as described 
//                              in Section 6.3.1, �IPROT Invalidation Protection
//                              in TLB1.�
//                            Protects TLB entry from invalidation by tlbivax (TLB1 only), 
//                            or flash invalidates through MMUCSR0[TLB1_FI].
//
//            34�39           Reserved, should be cleared.
//
// TID        40�47           Translation ID bits
//                            This field is compared with the current process IDs 
//                            of the effective address to be translated. A TID value 
//                            of 0 defines an entry as global and matches with all 
//                            process IDs.
//
//            48�50           Reserved, should be cleared.
//
// TS         51              Translation address space
//                            This bit is compared with the IS or DS fields of the 
//                            MSR (depending on the type of access) to determine if this 
//                            TLB entry may be used for translation.
//
// TSIZE      52�55           Entry page size
//                            Supported page sizes are:
//                            0b0001 4 Kbytes 0b0110 4 Mbytes
//                            0b0010 16 Kbytes 0b0111 16 Mbytes
//                            0b0011 64 Kbytes 0b1000 64 Mbytes
//                            0b0100 256 Kbytes 0b1001 256 Mbytes
//                            0b0101 1 Mbyte     1010 1 GB (e200z335 only)
//                                                1011 4 GB (e200z335 only)
//                            All other values are undefined.
//
//            56�63           Reserved, should be cleared.
//
//=============================================================================
typedef struct MMU_MAS1_F_Tag
{
   bitfield32_t VALID   :  BIT_1;
   bitfield32_t IPROT   :  BIT_1;
   bitfield32_t         :  BIT_6;
   bitfield32_t TID     :  BIT_8;
   bitfield32_t         :  BIT_3;
   bitfield32_t TS      :  BIT_1;
   bitfield32_t TSIZE   :  BIT_4;
   bitfield32_t         :  BIT_8;

} MMU_MAS1_F_T;

typedef union MMU_MAS1_Tag 
{
   MMU_MAS1_F_T   F;
   uint32_t       U32;
   uint16_t       U16[2];
   uint8_t        U8[4];

} MMU_MAS1_T;

//=============================================================================
// ID - MAS2 � EPN and Page Attributes
//
// Base Offset : SPR 626
//
// Reset Value : undefined
//
// Field        Bits     Type   Description
// ========== =========  ==== =================================================
// EPN         32�51          Effective page number
//
//             52�57          Reserved, should be cleared.
//
//             58             VLE mode.
//                            Identifies pages that contain instructions from 
//                            the VLE APU. VLE is implemented only if the processor
//                            supports the VLE APU. Setting both the VLE and E 
//                            fields is a programming error; an attempt to fetch
//                            instructions from a page so marked produces an ISI byte
//                            ordering exception and sets ESR[BO].
//                            0 - Instructions fetched from the page are decoded 
//                                and executed as PowerPC or EIS instructions.
//                            1 - Instructions fetched from the page are decoded and 
//                                executed as VLE or EIS instructions. Implementation-
//                                dependent page attribute.
//
// W           59             Write-through required
//                            0 This page is a write-back with respect to the caches 
//                              in the system.
//                            1 All stores performed to this page are written 
//                              through to main memory.
//
// I           60             Cache inhibited
//                            0 This page is cacheable.
//                            1 This page is cache-inhibited.
//
// M           61             Memory coherence required.The e200z3 does not 
//                            support the memory coherence required attribute,
//                            and thus it is ignored.
//                            0 Memory coherence is not required.
//                            1 Memory coherence is required.
//
// G           62             Guarded. The e200z3 ignores the guarded attribute 
//                            (other than for generation of the p_hprot[4:2]
//                            attributes on an external access), since no speculative 
//                            or out-of-order processing is performed.
//                            0 Access to this page are not guarded, and can be 
//                               performed before it is known if they are required
//                               by the sequential execution model.
//                            1 All loads and stores to this page are performed 
//                               without speculation (that is, they are known to be
//                               required).
//
// E           63             Endianness. Determines endianness for the corresponding 
//                            page.
//                            0 The page is accessed in big-endian byte order.
//                            1 The page is accessed in true little-endian byte order.
//
//=============================================================================
typedef struct MMU_MAS2_F_Tag
{
   bitfield32_t EPN  :  BIT_20;    /* Effective Page Number            */
   bitfield32_t      :  BIT_6;
   bitfield32_t VLE  :  BIT_1;     /* PowerPC VLE;0=standard BookE page*/
                                   /*  1=PowerPC VLE page              */
   bitfield32_t W    :  BIT_1;     /* Write through required;          */
                                   /*  0=write back; 1=write through   */
   bitfield32_t I    :  BIT_1;     /* Cache Inhibit; 0=not inhibited   */
   bitfield32_t M    :  BIT_1;     /* Memory coherence; 0=not required */
   bitfield32_t G    :  BIT_1;     /* Gaurded; 0=not gaurded           */
   bitfield32_t E    :  BIT_1;     /* Endianess; 0=Big; 1=Little       */

} MMU_MAS2_F_T;

typedef union MMU_MAS2_Tag
{
   MMU_MAS2_F_T   F;
   uint32_t       U32;
   uint16_t       U16[2];
   uint8_t        U8[4];

}MMU_MAS2_T;

//=============================================================================
// ID - MAS3 � RPN and Access Control
//
// Base Offset : SPR 627
//
// Reset Value : undefined
//
// Field        Bits     Type   Description
// ========== =========  ==== =================================================
// RPN         32-51          Real page number
//                            Only bits that correspond to a page number are valid. 
//                            Bits that represent offsets within a page are
//                            ignored and should be zero.
//
//             52-53          Reserved, should be cleared.
//
// U0�U3       54-57          User bits
//
// PERMIS      58-63          Permission bits (UX, SX, UW, SW, UR, SR)
//
//=============================================================================
typedef struct MMU_MAS3_F_Tag
{
   bitfield32_t RPN  :  BIT_20;   /* Real Page Number              */
   bitfield32_t      :  BIT_2;
   bitfield32_t USER :  BIT_4;    /* User bits [0:3]               */
   bitfield32_t UX   :  BIT_1;    /* Permission bits               */
   bitfield32_t SX   :  BIT_1;
   bitfield32_t UW   :  BIT_1;
   bitfield32_t SW   :  BIT_1;
   bitfield32_t UR   :  BIT_1;
   bitfield32_t SR   :  BIT_1;

} MMU_MAS3_F_T;

typedef union MMU_MAS3_Tag 
{
   MMU_MAS3_F_T   F;
   uint32_t       U32;
   uint16_t       U16[2];
   uint8_t        U8[4];

}MMU_MAS3_T;

//=============================================================================
// ID - MAS4 � Hardware Replacement Assist Configuration Register
//
// Base Offset : SPR 628
//
// Reset Value : undefined
//
// Field        Bits     Type   Description
// ========== =========  ==== =================================================
//             32�33          Reserved, should be cleared.
//
// TLBSELD     34�35          Default TLB selected
//                            01 TLB1 (ignored by the e200z3, should be written 
//                            to 01 for future compatibility)
//
//             36�43          Reserved, should be cleared.
//
// TIDSELD     44�47          TID default selection value.
//                            4-bit field that specifies which of the current 
//                            PID registers should be used to load the MAS1[TID] 
//                            field on a TLB miss exception.
//                            The PID registers are addressed as follows:
//                            0000 = PID0 (PID).
//                            0001 = PID1.
//                            ...
//                            1110 = PID14.
//                            A value that references a non-implemented PID
//                            register causes a value of 0 to be placed in MAS1[TID].
//
//             48�51          Reserved, should be cleared.
//
// TSIZED      52�55          Default TSIZE value
//
//             56�57          Reserved, should be cleared.
//
// VLED        58             Default VLE value. Specifies the default value 
//                            loaded into MAS2[VLE] on a TLB miss exception.
//
// DWIMGE      59�63          Default WIMGE values
//
//=============================================================================
typedef struct MMU_MAS4_F_Tag
{
   bitfield32_t         :  BIT_2;
   bitfield32_t TLBSELD :  BIT_2;
   bitfield32_t         :  BIT_8;
   bitfield32_t TIDSELD :  BIT_4;
   bitfield32_t         :  BIT_4;
   bitfield32_t TSIZED  :  BIT_4;
   bitfield32_t         :  BIT_2;
   bitfield32_t VLED    :  BIT_1;
   bitfield32_t WD      :  BIT_1;
   bitfield32_t ID      :  BIT_1;
   bitfield32_t MD      :  BIT_1;
   bitfield32_t GD      :  BIT_1;
   bitfield32_t ED      :  BIT_1;

} MMU_MAS4_F_T;

typedef union MMU_MAS4_Tag
{
   MMU_MAS4_F_T   F;
   uint32_t       U32;
   uint16_t       U16[2];
   uint8_t        U8[4];

}MMU_MAS4_T;

//=============================================================================
// ID - MAS6 � TLB Search Context Register 0
//
// Base Offset : SPR 630
//
// Reset Value : undefined
//
// Field        Bits     Type   Description
// ========== =========  ==== =================================================
//             32�39          Reserved, should be cleared.
//
// SPID        40�47          PID value for searches
//
//             48�62          Reserved, should be cleared.
//
// SAS         63             AS value for searches
//
//=============================================================================
typedef struct MMU_MAS6_F_Tag
{
   bitfield32_t      :  BIT_8;
   bitfield32_t SPID :  BIT_8;
   bitfield32_t      :  BIT_15;
   bitfield32_t SAS  :  BIT_1;

} MMU_MAS6_F_T;

typedef union MMU_MAS6_Tag 
{
   MMU_MAS6_F_T   F;
   uint32_t       U32;
   uint16_t       U16[2];
   uint8_t        U8[4];

}MMU_MAS6_T;


#endif // HW_MMU_H
