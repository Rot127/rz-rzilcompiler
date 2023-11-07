#define fREAD_IREG(VAL) (fSXTN(11,64,(((VAL) & 0xf0000000)>>21) | ((VAL>>17)&0x7f) ))
#define fPM_CIRR(REG, VAL, MVAL) do { fcirc_add(bundle, REG,VAL,MuV); } while (0)
#define fPM_CIRI(REG, IMM, MVAL) do { fcirc_add(bundle, REG,IMM,MuV); } while (0)
#define fWRITE_LC0(VAL) (HEX_REG_LC0 = VAL)
#define fSTORE_LOCKED(NUM, SIZE, EA, SRC, PRED)     gen_store_conditional##SIZE(ctx, PRED, EA, SRC);
#define fLOAD_LOCKED(NUM, SIZE, SIGN, EA, DST)     gen_load_locked##SIZE##SIGN(DST, EA, ctx->mem_idx);
#define PRED_LOAD_CANCEL(PRED, EA)     gen_pred_cancel(PRED, insn->is_endloop ? 4 : insn->slot)
#define fREAD_NPC() (get_npc(pkt) & (0xfffffffe))
#define HEX_REG_UTIMERHI   HEX_REG_ALIAS_UTIMERHI
#define HEX_REG_UTIMERLO   HEX_REG_ALIAS_UTIMERLO
#define HEX_REG_PKTCNTHI   HEX_REG_ALIAS_PKTCNTHI
#define HEX_REG_PKTCNTLO   HEX_REG_ALIAS_PKTCNTLO
#define HEX_REG_FRAMEKEY   HEX_REG_ALIAS_FRAMEKEY
#define HEX_REG_FRAMELIMIT   HEX_REG_ALIAS_FRAMELIMIT
#define HEX_REG_UPCYCLEHI   HEX_REG_ALIAS_UPCYCLEHI
#define HEX_REG_UPCYCLELO   HEX_REG_ALIAS_UPCYCLELO
#define HEX_REG_CS1   HEX_REG_ALIAS_CS1
#define HEX_REG_CS0   HEX_REG_ALIAS_CS0
#define HEX_REG_GP   HEX_REG_ALIAS_GP
#define HEX_REG_UGP   HEX_REG_ALIAS_UGP
#define HEX_REG_PC   HEX_REG_ALIAS_PC
#define HEX_REG_USR   HEX_REG_ALIAS_USR
#define HEX_REG_M1   HEX_REG_ALIAS_M1
#define HEX_REG_M0   HEX_REG_ALIAS_M0
#define HEX_REG_P3_0   HEX_REG_ALIAS_P3_0
#define HEX_REG_LC1   HEX_REG_ALIAS_LC1
#define HEX_REG_SA1   HEX_REG_ALIAS_SA1
#define HEX_REG_LC0   HEX_REG_ALIAS_LC0
#define HEX_REG_FP   HEX_REG_ALIAS_FP
#define HEX_REG_SP   HEX_REG_ALIAS_SP
#define HEX_REG_SA0   HEX_REG_ALIAS_SA0
#define HEX_REG_R31   R31
#define HEX_REG_LR   HEX_REG_ALIAS_LR
#define PC HEX_REG_ALIAS_PC
#define WRITE_PREG(NUM, VAL)             READ_PREG(NUM) = VAL
#define WRITE_RREG(NUM, VAL)             (NUM = VAL);
#define READ_PREG(NUM)                   P##NUM
#define READ_REG(NUM)                    NUM
#define RF_OFFSET HEX_RF_OFFSET
#define RF_WIDTH HEX_RF_WIDTH
#define DEF_SHORTCODE(TAG, SHORTCODE) insn(TAG, SHORTCODE)
#define fLSBOLD(VAL) (fGETBIT(0, VAL))
#define fSATH(VAL) fSATN(16, VAL)
#define fSATUH(VAL) fSATUN(16, VAL)
#define fVSATH(VAL) fVSATN(16, VAL)
#define fVSATUH(VAL) fVSATUN(16, VAL)
#define fSATUB(VAL) fSATUN(8, VAL)
#define fSATB(VAL) fSATN(8, VAL)
#define fVSATUB(VAL) fVSATUN(8, VAL)
#define fVSATB(VAL) fVSATN(8, VAL)
#define fCALL(A) fWRITE_LR(fREAD_NPC()); fWRITE_NPC(A);
#define fCALLR(A) fWRITE_LR(fREAD_NPC()); fWRITE_NPC(A);
#define fCAST2_8s(A) fSXTN(16, 64, A)
#define fCAST2_8u(A) fZXTN(16, 64, A)
#define fVSATW(A) fVSATN(32, fCAST8_8s(A))
#define fSATW(A) fSATN(32, fCAST8_8s(A))
#define fVSAT(A) fVSATN(32, A)
#define fSAT(A) fSATN(32, A)
#define f8BITSOF(VAL) ((VAL) ? 0xff : 0x00)
#define fREAD_GP() HEX_REG_GP
#define fCLIP(DST, SRC, U) (DST = fMIN((1 << U) - 1, fMAX(SRC, -(1 << U))))
#define fBIDIR_ASHIFTL(SRC, SHAMT, REGSTYPE)    ((SHAMT > 0) ?     (fCAST##REGSTYPE##s(SRC) << SHAMT) :     (fCAST##REGSTYPE##s(SRC) >> -SHAMT))
#define fBIDIR_LSHIFTL(SRC, SHAMT, REGSTYPE)    ((SHAMT > 0) ?     (fCAST##REGSTYPE##u(SRC) << SHAMT) :     (fCAST##REGSTYPE##u(SRC) >>> -SHAMT))
#define fBIDIR_ASHIFTR(SRC, SHAMT, REGSTYPE)    ((SHAMT > 0) ?     (fCAST##REGSTYPE##s(SRC) >> SHAMT) :     (fCAST##REGSTYPE##s(SRC) << -SHAMT))
#define fBIDIR_SHIFTR(SRC, SHAMT, REGSTYPE)    (((SHAMT) < 0) ? ((fCAST##REGSTYPE(SRC) << ((-(SHAMT)) - 1)) << 1)                   : (fCAST##REGSTYPE(SRC) >> (SHAMT)))
#define fBIDIR_LSHIFTR(SRC, SHAMT, REGSTYPE)    fBIDIR_SHIFTR(SRC, SHAMT, REGSTYPE##u)
#define fSATVALN(N, VAL)    fSET_OVERFLOW(        ((VAL) < 0) ? (-(1LL << ((N) - 1))) : ((1LL << ((N) - 1)) - 1)    )
#define fSAT_ORIG_SHL(A, ORIG_REG)    (((fCAST4s((fSAT(A)) ^ (fCAST4s(ORIG_REG)))) < 0)        ? fSATVALN(32, (fCAST4s(ORIG_REG)))        : ((((ORIG_REG) > 0) && ((A) == 0)) ? fSATVALN(32, (ORIG_REG))                                            : fSAT(A)))
#define fBIDIR_ASHIFTR_SAT(SRC, SHAMT, REGSTYPE)    (((SHAMT) < 0) ? fSAT_ORIG_SHL((fCAST##REGSTYPE##s(SRC)                        << ((-(SHAMT)) - 1)) << 1, (SRC))                   : (fCAST##REGSTYPE##s(SRC) >> (SHAMT)))
#define fBIDIR_ASHIFTL_SAT(SRC, SHAMT, REGSTYPE)    (((SHAMT) < 0)     ? ((fCAST##REGSTYPE##s(SRC) >> ((-(SHAMT)) - 1)) >> 1)     : fSAT_ORIG_SHL(fCAST##REGSTYPE##s(SRC) << (SHAMT), (SRC)))
#define fEXTRACTU_BIDIR(INREG, WIDTH, OFFSET)    (fZXTN(WIDTH, 32, fBIDIR_LSHIFTR((INREG), (OFFSET), 4_8)))
#define fLSBNEW0        (P0_NEW & 1)
#define fLSBNEW1        (P1_NEW & 1)
#define fLSBOLDNOT(VAL) fGETBIT(0, ~VAL)
#define fLSBNEWNOT(PRED) (fLSBNEW(~PRED))
#define fLSBNEW0NOT fLSBNEW(~P0N)
#define fLSBNEW1NOT fLSBNEW(~P1N)
#define fPCALIGN(IMM) (IMM = IMM & ~3)
#define fWRITE_LR(A) (HEX_REG_ALIAS_LR = A)
#define fWRITE_FP(A) (HEX_REG_ALIAS_FP = A)
#define fWRITE_SP(A) (HEX_REG_ALIAS_SP = A)
#define fWRITE_LOOP_REGS0(START, COUNT) HEX_REG_ALIAS_SA0 = START; (HEX_REG_ALIAS_LC0 = COUNT)
#define fWRITE_LOOP_REGS1(START, COUNT) HEX_REG_ALIAS_SA1 = START; (HEX_REG_ALIAS_LC1 = COUNT)
#define fWRITE_LC1(VAL) (HEX_REG_ALIAS_LC1 = VAL)
#define fSET_LPCFG(VAL) SET_USR_FIELD(LPCFG, VAL)
#define fWRITE_P0(VAL) P0 = VAL;
#define fWRITE_P1(VAL) P1 = VAL;
#define fWRITE_P3(VAL) P3 = VAL;
#define fEA_RI(REG, IMM) (EA = REG + IMM)
#define fEA_RRs(REG, REG2, SCALE) (EA = REG + (REG2 << SCALE))
#define fEA_IRs(IMM, REG, SCALE) (EA = IMM + (REG << SCALE))
#define fEA_IMM(IMM) (EA = IMM)
#define fEA_REG(REG) (EA = REG)
#define fEA_BREVR(REG) (EA = fbrev(REG))
#define fEA_GPI(IMM) (EA = fREAD_GP() + IMM)
#define fPM_I(REG, IMM) (REG = REG + IMM)
#define fPM_M(REG, MVAL) (REG = REG + MVAL)
#define fROUND(A) (A + 0x8000)
#define fSCALE(N, A) (A << N)
#define fASHIFTR(SRC, SHAMT, REGSTYPE) (fCAST##REGSTYPE##s(SRC) >> SHAMT)
#define fLSHIFTR(SRC, SHAMT, REGSTYPE) (SRC >>> SHAMT)
#define fROTL(SRC, SHAMT, REGSTYPE) fROTL(SRC, SHAMT)
#define fASHIFTL(SRC, SHAMT, REGSTYPE) (fCAST##REGSTYPE##s(SRC) << SHAMT)
#define fHIDE(A) A
#define fBRANCH_SPECULATE_STALL(A, B, C, D, E)
#define HEXAGON_MACROS_H
#define PCALIGN 4
#define PCALIGN_MASK (PCALIGN - 1)
#define GET_FIELD(FIELD, REGIN)     fEXTRACTU_BITS(REGIN, REGFIELD(RF_WIDTH, HEX_REG_FIELD_##FIELD),                    REGFIELD(RF_OFFSET, HEX_REG_FIELD_##FIELD))
#define GET_USR_FIELD(FIELD) get_usr_field(bundle, HEX_REG_FIELD_##FIELD)
#define SET_USR_FIELD(FIELD, VAL) set_usr_field(bundle, HEX_REG_FIELD_##FIELD, (VAL))
#define MEM_LOAD1s(VA) (mem_load_s8(VA))
#define MEM_LOAD1u(VA) (mem_load_u8(VA))
#define MEM_LOAD2s(VA) (mem_load_s16(VA))
#define MEM_LOAD2u(VA) (mem_load_u16(VA))
#define MEM_LOAD4s(VA) (mem_load_s32(VA))
#define MEM_LOAD4u(VA) (mem_load_u32(VA))
#define MEM_LOAD8s(VA) (mem_load_s64(VA))
#define MEM_LOAD8u(VA) (mem_load_u64(VA))
#define MEM_STORE1(VA, DATA, SLOT) mem_store_u8(VA, DATA)
#define MEM_STORE2(VA, DATA, SLOT) mem_store_u16(VA, DATA)
#define MEM_STORE4(VA, DATA, SLOT) mem_store_u32(VA, DATA)
#define MEM_STORE8(VA, DATA, SLOT) mem_store_u64(VA, DATA)
#define CANCEL cancel_slot
#define LOAD_CANCEL(EA) do { CANCEL; } while (0)
#define STORE_CANCEL(EA) { STORE_SLOT_CANCELLED(pkt, slot); }
#define fMAX(A, B) (((A) > (B)) ? (A) : (B))
#define fMIN(A, B) (((A) < (B)) ? (A) : (B))
#define fABS(A) (((A) < 0) ? (-(A)) : (A))
#define fINSERT_BITS(REG, WIDTH, OFFSET, INVAL)    REG = ((WIDTH) ? deposit64(REG, (OFFSET), (WIDTH), (INVAL)) : REG)
#define fEXTRACTU_BITS(INREG, WIDTH, OFFSET)    ((WIDTH) ? extract64((INREG), (OFFSET), (WIDTH)) : 0LL)
#define fEXTRACTU_BIDIR(INREG, WIDTH, OFFSET)    (fZXTN(WIDTH, 32, fBIDIR_LSHIFTR((INREG), (OFFSET), 4_8)))
#define fEXTRACTU_RANGE(INREG, HIBIT, LOWBIT)    (((HIBIT) - (LOWBIT) + 1) ?        extract64((INREG), (LOWBIT), ((HIBIT) - (LOWBIT) + 1)) :        0LL)
#define fINSERT_RANGE(INREG, HIBIT, LOWBIT, INVAL)    do {        int width = ((HIBIT) - (LOWBIT) + 1);        INREG = (width >= 0 ?            deposit64((INREG), (LOWBIT), width, (INVAL)) :            INREG);    } while (0)
#define f8BITSOF(VAL) ((VAL) ? 0xff : 0x00)
#define fLSBOLD(VAL)  ((VAL) & 1)
#define fLSBNEW(PVAL)   ((PVAL) & 1)
#define fLSBNEWNOT(PNUM) (!fLSBNEW(PNUM))
#define fLSBOLDNOT(VAL) (!fLSBOLD(VAL))
#define fLSBNEW0NOT (!fLSBNEW0)
#define fLSBNEW1NOT (!fLSBNEW1)
#define fNEWREG(VAL) ((int32_t)(VAL))
#define fNEWREG_ST(VAL) (VAL)
#define fVSATUVALN(N, VAL)    ({        (((int64_t)(VAL)) < 0) ? 0 : ((1LL << (N)) - 1);    })
#define fSATUVALN(N, VAL)    ({        fSET_OVERFLOW();        ((VAL) < 0) ? 0 : ((1LL << (N)) - 1);    })
#define fSATVALN(N, VAL)    ({        fSET_OVERFLOW();        ((VAL) < 0) ? (-(1LL << ((N) - 1))) : ((1LL << ((N) - 1)) - 1);    })
#define fVSATVALN(N, VAL)    ({        ((VAL) < 0) ? (-(1LL << ((N) - 1))) : ((1LL << ((N) - 1)) - 1);    })
#define fZXTN(N, M, VAL) (((N) != 0) ? extract64((VAL), 0, (N)) : 0LL)
#define fSXTN(N, M, VAL) (((N) != 0) ? sextract64((VAL), 0, (N)) : 0LL)
#define fSATN(N, VAL)    ((fSXTN(N, 64, VAL) == (VAL)) ? (VAL) : fSATVALN(N, VAL))
#define fVSATN(N, VAL)    ((fSXTN(N, 64, VAL) == (VAL)) ? (VAL) : fVSATVALN(N, VAL))
#define fADDSAT64(DST, A, B)    do {        uint64_t __a = fCAST8u(A);        uint64_t __b = fCAST8u(B);        uint64_t __sum = __a + __b;        uint64_t __xor = __a ^ __b;        const uint64_t __mask = 0x8000000000000000ULL;        if (__xor & __mask) {            DST = __sum;        }        else if ((__a ^ __sum) & __mask) {            if (__sum & __mask) {                DST = 0x7FFFFFFFFFFFFFFFLL;                fSET_OVERFLOW();            } else {                DST = 0x8000000000000000LL;                fSET_OVERFLOW();            }        } else {            DST = __sum;        }    } while (0)
#define fVSATUN(N, VAL)    ((fZXTN(N, 64, VAL) == (VAL)) ? (VAL) : fVSATUVALN(N, VAL))
#define fSATUN(N, VAL)    ((fZXTN(N, 64, VAL) == (VAL)) ? (VAL) : fSATUVALN(N, VAL))
#define fSATH(VAL) (fSATN(16, VAL))
#define fSATUH(VAL) (fSATUN(16, VAL))
#define fVSATH(VAL) (fVSATN(16, VAL))
#define fVSATUH(VAL) (fVSATUN(16, VAL))
#define fSATUB(VAL) (fSATUN(8, VAL))
#define fSATB(VAL) (fSATN(8, VAL))
#define fVSATUB(VAL) (fVSATUN(8, VAL))
#define fVSATB(VAL) (fVSATN(8, VAL))
#define fIMMEXT(IMM) (IMM)
#define fMUST_IMMEXT(IMM) fIMMEXT(IMM)
#define fPCALIGN(IMM) IMM = (IMM & ~PCALIGN_MASK)
#define fREAD_LR() (READ_REG(HEX_REG_LR))
#define fREAD_SP() (READ_REG(HEX_REG_SP))
#define fREAD_LC0 (READ_REG(HEX_REG_LC0))
#define fREAD_LC1 (READ_REG(HEX_REG_LC1))
#define fREAD_SA0 (READ_REG(HEX_REG_SA0))
#define fREAD_SA1 (READ_REG(HEX_REG_SA1))
#define fREAD_FP() (READ_REG(HEX_REG_FP))
#define fREAD_PC() (PC)
#define fREAD_P0() READ_PREG(0)
#define fCHECK_PCALIGN(A)
#define fWRITE_NPC(A) JUMP(A)
#define fBRANCH(LOC, TYPE)          fWRITE_NPC(LOC)
#define fJUMPR(REGNO, TARGET, TYPE) fBRANCH(TARGET, COF_TYPE_JUMPR)
#define fHINTJR(TARGET) { /* Not modelled in qemu */}
#define fSET_OVERFLOW() SET_USR_FIELD(USR_OVF, 1)
#define fGET_LPCFG (GET_USR_FIELD(USR_LPCFG))
#define fPART1(WORK) __COMPOUND_PART1__{ WORK; }__COMPOUND_PART1__
#define fCAST4u(A) ((uint32_t)(A))
#define fCAST4s(A) ((int32_t)(A))
#define fCAST8u(A) ((uint64_t)(A))
#define fCAST8s(A) ((int64_t)(A))
#define fCAST2_2s(A) ((int16_t)(A))
#define fCAST2_2u(A) ((uint16_t)(A))
#define fCAST4_4s(A) ((int32_t)(A))
#define fCAST4_4u(A) ((uint32_t)(A))
#define fCAST4_8s(A) ((int64_t)((int32_t)(A)))
#define fCAST4_8u(A) ((uint64_t)((uint32_t)(A)))
#define fCAST8_8s(A) ((int64_t)(A))
#define fCAST8_8u(A) ((uint64_t)(A))
#define fCAST2_8s(A) ((int64_t)((int16_t)(A)))
#define fCAST2_8u(A) ((uint64_t)((uint16_t)(A)))
#define fZE8_16(A) ((int16_t)((uint8_t)(A)))
#define fSE8_16(A) ((int16_t)((int8_t)(A)))
#define fSE16_32(A) ((int32_t)((int16_t)(A)))
#define fZE16_32(A) ((uint32_t)((uint16_t)(A)))
#define fSE32_64(A) ((int64_t)((int32_t)(A)))
#define fZE32_64(A) ((uint64_t)((uint32_t)(A)))
#define fSE8_32(A) ((int32_t)((int8_t)(A)))
#define fZE8_32(A) ((int32_t)((uint8_t)(A)))
#define fMPY8UU(A, B) (int)(fZE8_16(A) * fZE8_16(B))
#define fMPY8US(A, B) (int)(fZE8_16(A) * fSE8_16(B))
#define fMPY8SU(A, B) (int)(fSE8_16(A) * fZE8_16(B))
#define fMPY8SS(A, B) (int)((short)(A) * (short)(B))
#define fMPY16SS(A, B) fSE32_64(fSE16_32(A) * fSE16_32(B))
#define fMPY16UU(A, B) fZE32_64(fZE16_32(A) * fZE16_32(B))
#define fMPY16SU(A, B) fSE32_64(fSE16_32(A) * fZE16_32(B))
#define fMPY16US(A, B) fMPY16SU(B, A)
#define fMPY32SS(A, B) (fSE32_64(A) * fSE32_64(B))
#define fMPY32UU(A, B) (fZE32_64(A) * fZE32_64(B))
#define fMPY32SU(A, B) (fSE32_64(A) * fZE32_64(B))
#define fMPY3216SS(A, B) (fSE32_64(A) * fSXTN(16, 64, B))
#define fMPY3216SU(A, B) (fSE32_64(A) * fZXTN(16, 64, B))
#define fROUND(A) (A + 0x8000)
#define fCLIP(DST, SRC, U)    do {        int32_t maxv = (1 << U) - 1;        int32_t minv = -(1 << U);        DST = fMIN(maxv, fMAX(SRC, minv));    } while (0)
#define fCRND(A) ((((A) & 0x3) == 0x3) ? ((A) + 1) : ((A)))
#define fRNDN(A, N) ((((N) == 0) ? (A) : (((fSE32_64(A)) + (1 << ((N) - 1))))))
#define fCRNDN(A, N) (conv_round(A, N))
#define fADD128(A, B) (int128_add(A, B))
#define fSUB128(A, B) (int128_sub(A, B))
#define fSHIFTR128(A, B) (int128_rshift(A, B))
#define fSHIFTL128(A, B) (int128_lshift(A, B))
#define fAND128(A, B) (int128_and(A, B))
#define fCAST8S_16S(A) (int128_exts64(A))
#define fCAST16S_8S(A) (int128_getlo(A))
#define fEA_RI(REG, IMM)    do {        EA = REG + IMM;    } while (0)
#define fEA_RRs(REG, REG2, SCALE)    do {        EA = REG + (REG2 << SCALE);    } while (0)
#define fEA_IRs(IMM, REG, SCALE)    do {        EA = IMM + (REG << SCALE);    } while (0)
#define fEA_IMM(IMM)        do { EA = (IMM); } while (0)
#define fEA_REG(REG)        do { EA = (REG); } while (0)
#define fEA_GPI(IMM)        do { EA = (fREAD_GP() + (IMM)); } while (0)
#define fPM_I(REG, IMM)     do { REG = REG + (IMM); } while (0)
#define fPM_M(REG, MVAL)    do { REG = REG + (MVAL); } while (0)
#define fSCALE(N, A) (((int64_t)(A)) << N)
#define fVSATW(A) fVSATN(32, ((long long)A))
#define fSATW(A) fSATN(32, ((long long)A))
#define fVSAT(A) fVSATN(32, (A))
#define fSAT(A) fSATN(32, (A))
#define fSAT_ORIG_SHL(A, ORIG_REG)    ((((int32_t)((fSAT(A)) ^ ((int32_t)(ORIG_REG)))) < 0)        ? fSATVALN(32, ((int32_t)(ORIG_REG)))        : ((((ORIG_REG) > 0) && ((A) == 0)) ? fSATVALN(32, (ORIG_REG))                                            : fSAT(A)))
#define fPASS(A) A
#define fBIDIR_SHIFTL(SRC, SHAMT, REGSTYPE)    (((SHAMT) < 0) ? ((fCAST##REGSTYPE(SRC) >> ((-(SHAMT)) - 1)) >> 1)                   : (fCAST##REGSTYPE(SRC) << (SHAMT)))
#define fBIDIR_ASHIFTL(SRC, SHAMT, REGSTYPE)    fBIDIR_SHIFTL(SRC, SHAMT, REGSTYPE##s)
#define fBIDIR_LSHIFTL(SRC, SHAMT, REGSTYPE)    fBIDIR_SHIFTL(SRC, SHAMT, REGSTYPE##u)
#define fBIDIR_ASHIFTL_SAT(SRC, SHAMT, REGSTYPE)    (((SHAMT) < 0) ? ((fCAST##REGSTYPE##s(SRC) >> ((-(SHAMT)) - 1)) >> 1)                   : fSAT_ORIG_SHL(fCAST##REGSTYPE##s(SRC) << (SHAMT), (SRC)))
#define fBIDIR_SHIFTR(SRC, SHAMT, REGSTYPE)    (((SHAMT) < 0) ? ((fCAST##REGSTYPE(SRC) << ((-(SHAMT)) - 1)) << 1)                   : (fCAST##REGSTYPE(SRC) >> (SHAMT)))
#define fBIDIR_ASHIFTR(SRC, SHAMT, REGSTYPE)    fBIDIR_SHIFTR(SRC, SHAMT, REGSTYPE##s)
#define fBIDIR_LSHIFTR(SRC, SHAMT, REGSTYPE)    fBIDIR_SHIFTR(SRC, SHAMT, REGSTYPE##u)
#define fBIDIR_ASHIFTR_SAT(SRC, SHAMT, REGSTYPE)    (((SHAMT) < 0) ? fSAT_ORIG_SHL((fCAST##REGSTYPE##s(SRC)                        << ((-(SHAMT)) - 1)) << 1, (SRC))                   : (fCAST##REGSTYPE##s(SRC) >> (SHAMT)))
#define fASHIFTR(SRC, SHAMT, REGSTYPE) (fCAST##REGSTYPE##s(SRC) >> (SHAMT))
#define fLSHIFTR(SRC, SHAMT, REGSTYPE)    (((SHAMT) >= (sizeof(SRC) * 8)) ? 0 : (fCAST##REGSTYPE##u(SRC) >> (SHAMT)))
#define fROTL(SRC, SHAMT, REGSTYPE)    (((SHAMT) == 0) ? (SRC) : ((fCAST##REGSTYPE##u(SRC) << (SHAMT)) |                              ((fCAST##REGSTYPE##u(SRC) >>                                 ((sizeof(SRC) * 8) - (SHAMT))))))
#define fROTR(SRC, SHAMT, REGSTYPE)    (((SHAMT) == 0) ? (SRC) : ((fCAST##REGSTYPE##u(SRC) >> (SHAMT)) |                              ((fCAST##REGSTYPE##u(SRC) <<                                 ((sizeof(SRC) * 8) - (SHAMT))))))
#define fASHIFTL(SRC, SHAMT, REGSTYPE)    (((SHAMT) >= (sizeof(SRC) * 8)) ? 0 : (fCAST##REGSTYPE##s(SRC) << (SHAMT)))
#define fLOAD(NUM, SIZE, SIGN, EA, DST)    DST = (size##SIZE##SIGN##_t)MEM_LOAD##SIZE##SIGN(EA)
#define fMEMOP(NUM, SIZE, SIGN, EA, FNTYPE, VALUE)
#define fGET_FRAMEKEY() (READ_REG(HEX_REG_FRAMEKEY))
#define fFRAME_SCRAMBLE(VAL) ((VAL) ^ (fCAST8u(fGET_FRAMEKEY()) << 32))
#define fFRAME_UNSCRAMBLE(VAL) fFRAME_SCRAMBLE(VAL)
#define fFRAMECHECK(ADDR, EA)
#define fSTORE(NUM, SIZE, EA, SRC) MEM_STORE##SIZE(EA, SRC, INSN_SLOT)
#define fGETBYTE(N, SRC) ((int8_t)((SRC >> ((N) * 8)) & 0xff))
#define fGETUBYTE(N, SRC) ((uint8_t)((SRC >> ((N) * 8)) & 0xff))
#define fSETBYTE(N, DST, VAL)    do {        DST = (DST & ~(0x0ffLL << ((N) * 8))) |        (((uint64_t)((VAL) & 0x0ffLL)) << ((N) * 8));    } while (0)
#define fGETHALF(N, SRC) ((int16_t)((SRC >> ((N) * 16)) & 0xffff))
#define fGETUHALF(N, SRC) ((uint16_t)((SRC >> ((N) * 16)) & 0xffff))
#define fSETHALF(N, DST, VAL)    do {        DST = (DST & ~(0x0ffffLL << ((N) * 16))) |        (((uint64_t)((VAL) & 0x0ffff)) << ((N) * 16));    } while (0)
#define fSETHALFw fSETHALF
#define fSETHALFd fSETHALF
#define fGETWORD(N, SRC)    ((int64_t)((int32_t)((SRC >> ((N) * 32)) & 0x0ffffffffLL)))
#define fGETUWORD(N, SRC)    ((uint64_t)((uint32_t)((SRC >> ((N) * 32)) & 0x0ffffffffLL)))
#define fSETWORD(N, DST, VAL)    do {        DST = (DST & ~(0x0ffffffffLL << ((N) * 32))) |              (((VAL) & 0x0ffffffffLL) << ((N) * 32));    } while (0)
#define fSETBIT(N, DST, VAL)    do {        DST = (DST & ~(1ULL << (N))) | (((uint64_t)(VAL)) << (N));    } while (0)
#define fGETBIT(N, SRC) (((SRC) >> N) & 1)
#define fSETBITS(HI, LO, DST, VAL)    do {        int j;        for (j = LO; j <= HI; j++) {            fSETBIT(j, DST, VAL);        }    } while (0)
#define fCOUNTONES_2(VAL) ctpop16(VAL)
#define fCOUNTONES_4(VAL) ctpop32(VAL)
#define fCOUNTONES_8(VAL) ctpop64(VAL)
#define fBREV_8(VAL) revbit64(VAL)
#define fBREV_4(VAL) revbit32(VAL)
#define fCL1_8(VAL) clo64(VAL)
#define fCL1_4(VAL) clo32(VAL)
#define fCL1_2(VAL) (clz32(~(uint16_t)(VAL) & 0xffff) - 16)
#define fINTERLEAVE(ODD, EVEN) interleave(ODD, EVEN)
#define fDEINTERLEAVE(MIXED) deinterleave(MIXED)
#define fHIDE(A) A
#define fCONSTLL(A) A##LL
#define fECHO(A) (A)
#define fTRAP(TRAPTYPE, IMM) trap(TRAPTYPE, IMM)
#define fPAUSE(IMM)
#define fALIGN_REG_FIELD_VALUE(FIELD, VAL)     ((VAL) << REGFIELD(RF_OFFSET, HEX_REG_FIELD_##FIELD))
#define fGET_REG_FIELD_MASK(FIELD)     (((1 << REGFIELD(RF_WIDTH, HEX_REG_FIELD_##FIELD)) - 1) << REGFIELD(RF_OFFSET, HEX_REG_FIELD_##FIELD))
#define fREAD_REG_FIELD(REG, FIELD)     fEXTRACTU_BITS(READ_REG(REG),                    REGFIELD(RF_WIDTH, HEX_REG_FIELD_##FIELD),                    REGFIELD(RF_OFFSET, HEX_REG_FIELD_##FIELD))
#define fBRANCH_SPECULATE_STALL(DOTNEWVAL, JUMP_COND, SPEC_DIR, HINTBITNUM,                                STRBITNUM) /* Nothing */
#define HEXAGON_MMVEC_MACROS_H
#define VdV      (*(MMVector *)(VdV_void))
#define VsV      (*(MMVector *)(VsV_void))
#define VuV      (*(MMVector *)(VuV_void))
#define VvV      (*(MMVector *)(VvV_void))
#define VwV      (*(MMVector *)(VwV_void))
#define VxV      (*(MMVector *)(VxV_void))
#define VyV      (*(MMVector *)(VyV_void))
#define VddV     (*(MMVectorPair *)(VddV_void))
#define VuuV     (*(MMVectorPair *)(VuuV_void))
#define VvvV     (*(MMVectorPair *)(VvvV_void))
#define VxxV     (*(MMVectorPair *)(VxxV_void))
#define QeV      (*(MMQReg *)(QeV_void))
#define QdV      (*(MMQReg *)(QdV_void))
#define QsV      (*(MMQReg *)(QsV_void))
#define QtV      (*(MMQReg *)(QtV_void))
#define QuV      (*(MMQReg *)(QuV_void))
#define QvV      (*(MMQReg *)(QvV_void))
#define QxV      (*(MMQReg *)(QxV_void))
#define LOG_VTCM_BYTE(VA, MASK, VAL, IDX)    do {        env->vtcm_log.data.ub[IDX] = (VAL);        if (MASK) {            set_bit((IDX), env->vtcm_log.mask);        } else {            clear_bit((IDX), env->vtcm_log.mask);        }        env->vtcm_log.va[IDX] = (VA);    } while (0)
#define fNOTQ(VAL)    ({        MMQReg _ret;        int _i_;        for (_i_ = 0; _i_ < fVECSIZE() / 64; _i_++) {            _ret.ud[_i_] = ~VAL.ud[_i_];        }        _ret;     })
#define fGETQBITS(REG, WIDTH, MASK, BITNO)    ((MASK) & (REG.w[(BITNO) >> 5] >> ((BITNO) & 0x1f)))
#define fGETQBIT(REG, BITNO) fGETQBITS(REG, 1, 1, BITNO)
#define fGENMASKW(QREG, IDX)    (((fGETQBIT(QREG, (IDX * 4 + 0)) ? 0xFF : 0x0) << 0)  |     ((fGETQBIT(QREG, (IDX * 4 + 1)) ? 0xFF : 0x0) << 8)  |     ((fGETQBIT(QREG, (IDX * 4 + 2)) ? 0xFF : 0x0) << 16) |     ((fGETQBIT(QREG, (IDX * 4 + 3)) ? 0xFF : 0x0) << 24))
#define fGETNIBBLE(IDX, SRC) (fSXTN(4, 8, (SRC >> (4 * IDX)) & 0xF))
#define fGETCRUMB(IDX, SRC) (fSXTN(2, 8, (SRC >> (2 * IDX)) & 0x3))
#define fGETCRUMB_SYMMETRIC(IDX, SRC)    ((fGETCRUMB(IDX, SRC) >= 0 ? (2 - fGETCRUMB(IDX, SRC))                               : fGETCRUMB(IDX, SRC)))
#define fGENMASKH(QREG, IDX)    (((fGETQBIT(QREG, (IDX * 2 + 0)) ? 0xFF : 0x0) << 0) |     ((fGETQBIT(QREG, (IDX * 2 + 1)) ? 0xFF : 0x0) << 8))
#define fGETMASKW(VREG, QREG, IDX) (VREG.w[IDX] & fGENMASKW((QREG), IDX))
#define fGETMASKH(VREG, QREG, IDX) (VREG.h[IDX] & fGENMASKH((QREG), IDX))
#define fCONDMASK8(QREG, IDX, YESVAL, NOVAL)    (fGETQBIT(QREG, IDX) ? (YESVAL) : (NOVAL))
#define fCONDMASK16(QREG, IDX, YESVAL, NOVAL)    ((fGENMASKH(QREG, IDX) & (YESVAL)) |     (fGENMASKH(fNOTQ(QREG), IDX) & (NOVAL)))
#define fCONDMASK32(QREG, IDX, YESVAL, NOVAL)    ((fGENMASKW(QREG, IDX) & (YESVAL)) |     (fGENMASKW(fNOTQ(QREG), IDX) & (NOVAL)))
#define fSETQBITS(REG, WIDTH, MASK, BITNO, VAL)    do {        uint32_t __TMP = (VAL);        REG.w[(BITNO) >> 5] &= ~((MASK) << ((BITNO) & 0x1f));        REG.w[(BITNO) >> 5] |= (((__TMP) & (MASK)) << ((BITNO) & 0x1f));    } while (0)
#define fSETQBIT(REG, BITNO, VAL) fSETQBITS(REG, 1, 1, BITNO, VAL)
#define fVBYTES() (fVECSIZE())
#define fVALIGN(ADDR, LOG2_ALIGNMENT) (ADDR = ADDR & ~(LOG2_ALIGNMENT - 1))
#define fVLASTBYTE(ADDR, LOG2_ALIGNMENT) (ADDR = ADDR | (LOG2_ALIGNMENT - 1))
#define fVELEM(WIDTH) ((fVECSIZE() * 8) / WIDTH)
#define fVECLOGSIZE() (7)
#define fVECSIZE() (1 << fVECLOGSIZE())
#define fSWAPB(A, B) do { uint8_t tmp = A; A = B; B = tmp; } while (0)
#define fV_AL_CHECK(EA, MASK)    if ((EA) & (MASK)) {        warn("aligning misaligned vector. EA=%08x", (EA));    }
#define fSCATTER_INIT(REGION_START, LENGTH, ELEMENT_SIZE)    mem_vector_scatter_init(env)
#define fGATHER_INIT(REGION_START, LENGTH, ELEMENT_SIZE)    mem_vector_gather_init(env)
#define fSCATTER_FINISH(OP)
#define fGATHER_FINISH()
#define fLOG_SCATTER_OP(SIZE)    do {        env->vtcm_log.op = true;        env->vtcm_log.op_size = SIZE;    } while (0)
#define fVLOG_VTCM_WORD_INCREMENT(EA, OFFSET, INC, IDX, ALIGNMENT, LEN)    do {        int log_byte = 0;        target_ulong va = EA;        target_ulong va_high = EA + LEN;        for (int i0 = 0; i0 < 4; i0++) {            log_byte = (va + i0) <= va_high;            LOG_VTCM_BYTE(va + i0, log_byte, INC. ub[4 * IDX + i0],                          4 * IDX + i0);        }    } while (0)
#define fVLOG_VTCM_HALFWORD_INCREMENT(EA, OFFSET, INC, IDX, ALIGNMENT, LEN)    do {        int log_byte = 0;        target_ulong va = EA;        target_ulong va_high = EA + LEN;        for (int i0 = 0; i0 < 2; i0++) {            log_byte = (va + i0) <= va_high;            LOG_VTCM_BYTE(va + i0, log_byte, INC.ub[2 * IDX + i0],                          2 * IDX + i0);        }    } while (0)
#define fVLOG_VTCM_HALFWORD_INCREMENT_DV(EA, OFFSET, INC, IDX, IDX2, IDX_H,                                         ALIGNMENT, LEN)    do {        int log_byte = 0;        target_ulong va = EA;        target_ulong va_high = EA + LEN;        for (int i0 = 0; i0 < 2; i0++) {            log_byte = (va + i0) <= va_high;            LOG_VTCM_BYTE(va + i0, log_byte, INC.ub[2 * IDX + i0],                          2 * IDX + i0);        }    } while (0)
#define GATHER_FUNCTION(EA, OFFSET, IDX, LEN, ELEMENT_SIZE, BANK_IDX, QVAL)    do {        int i0;        target_ulong va = EA;        target_ulong va_high = EA + LEN;        uintptr_t ra = GETPC();        int log_byte = 0;        for (i0 = 0; i0 < ELEMENT_SIZE; i0++) {            log_byte = ((va + i0) <= va_high) && QVAL;            uint8_t B;            B = cpu_ldub_data_ra(env, EA + i0, ra);            env->tmp_VRegs[0].ub[ELEMENT_SIZE * IDX + i0] = B;            LOG_VTCM_BYTE(va + i0, log_byte, B, ELEMENT_SIZE * IDX + i0);        }    } while (0)
#define fVLOG_VTCM_GATHER_WORD(EA, OFFSET, IDX, LEN)    do {        GATHER_FUNCTION(EA, OFFSET, IDX, LEN, 4, IDX, 1);    } while (0)
#define fVLOG_VTCM_GATHER_HALFWORD(EA, OFFSET, IDX, LEN)    do {        GATHER_FUNCTION(EA, OFFSET, IDX, LEN, 2, IDX, 1);    } while (0)
#define fVLOG_VTCM_GATHER_HALFWORD_DV(EA, OFFSET, IDX, IDX2, IDX_H, LEN)    do {        GATHER_FUNCTION(EA, OFFSET, IDX, LEN, 2, (2 * IDX2 + IDX_H), 1);    } while (0)
#define fVLOG_VTCM_GATHER_WORDQ(EA, OFFSET, IDX, Q, LEN)    do {        GATHER_FUNCTION(EA, OFFSET, IDX, LEN, 4, IDX,                        fGETQBIT(QsV, 4 * IDX + i0));    } while (0)
#define fVLOG_VTCM_GATHER_HALFWORDQ(EA, OFFSET, IDX, Q, LEN)    do {        GATHER_FUNCTION(EA, OFFSET, IDX, LEN, 2, IDX,                        fGETQBIT(QsV, 2 * IDX + i0));    } while (0)
#define fVLOG_VTCM_GATHER_HALFWORDQ_DV(EA, OFFSET, IDX, IDX2, IDX_H, Q, LEN)    do {        GATHER_FUNCTION(EA, OFFSET, IDX, LEN, 2, (2 * IDX2 + IDX_H),                        fGETQBIT(QsV, 2 * IDX + i0));    } while (0)
#define SCATTER_OP_WRITE_TO_MEM(TYPE)    do {        uintptr_t ra = GETPC();        for (int i = 0; i < sizeof(MMVector); i += sizeof(TYPE)) {            if (test_bit(i, env->vtcm_log.mask)) {                TYPE dst = 0;                TYPE inc = 0;                for (int j = 0; j < sizeof(TYPE); j++) {                    uint8_t val;                    val = cpu_ldub_data_ra(env, env->vtcm_log.va[i + j], ra);                    dst |= val << (8 * j);                    inc |= env->vtcm_log.data.ub[j + i] << (8 * j);                    clear_bit(j + i, env->vtcm_log.mask);                    env->vtcm_log.data.ub[j + i] = 0;                }                dst += inc;                for (int j = 0; j < sizeof(TYPE); j++) {                    cpu_stb_data_ra(env, env->vtcm_log.va[i + j],                                    (dst >> (8 * j)) & 0xFF, ra);                }            }        }    } while (0)
#define SCATTER_OP_PROBE_MEM(TYPE, MMU_IDX, RETADDR)    do {        for (int i = 0; i < sizeof(MMVector); i += sizeof(TYPE)) {            if (test_bit(i, env->vtcm_log.mask)) {                for (int j = 0; j < sizeof(TYPE); j++) {                    probe_read(env, env->vtcm_log.va[i + j], 1,                               MMU_IDX, RETADDR);                    probe_write(env, env->vtcm_log.va[i + j], 1,                                MMU_IDX, RETADDR);                }            }        }    } while (0)
#define SCATTER_FUNCTION(EA, OFFSET, IDX, LEN, ELEM_SIZE, BANK_IDX, QVAL, IN)    do {        int i0;        target_ulong va = EA;        target_ulong va_high = EA + LEN;        int log_byte = 0;        for (i0 = 0; i0 < ELEM_SIZE; i0++) {            log_byte = ((va + i0) <= va_high) && QVAL;            LOG_VTCM_BYTE(va + i0, log_byte, IN.ub[ELEM_SIZE * IDX + i0],                          ELEM_SIZE * IDX + i0);        }    } while (0)
#define fVLOG_VTCM_HALFWORD(EA, OFFSET, IN, IDX, LEN)    do {        SCATTER_FUNCTION(EA, OFFSET, IDX, LEN, 2, IDX, 1, IN);    } while (0)
#define fVLOG_VTCM_WORD(EA, OFFSET, IN, IDX, LEN)    do {        SCATTER_FUNCTION(EA, OFFSET, IDX, LEN, 4, IDX, 1, IN);    } while (0)
#define fVLOG_VTCM_HALFWORDQ(EA, OFFSET, IN, IDX, Q, LEN)    do {        SCATTER_FUNCTION(EA, OFFSET, IDX, LEN, 2, IDX,                         fGETQBIT(QsV, 2 * IDX + i0), IN);    } while (0)
#define fVLOG_VTCM_WORDQ(EA, OFFSET, IN, IDX, Q, LEN)    do {        SCATTER_FUNCTION(EA, OFFSET, IDX, LEN, 4, IDX,                         fGETQBIT(QsV, 4 * IDX + i0), IN);    } while (0)
#define fVLOG_VTCM_HALFWORD_DV(EA, OFFSET, IN, IDX, IDX2, IDX_H, LEN)    do {        SCATTER_FUNCTION(EA, OFFSET, IDX, LEN, 2,                         (2 * IDX2 + IDX_H), 1, IN);    } while (0)
#define fVLOG_VTCM_HALFWORDQ_DV(EA, OFFSET, IN, IDX, Q, IDX2, IDX_H, LEN)    do {        SCATTER_FUNCTION(EA, OFFSET, IDX, LEN, 2, (2 * IDX2 + IDX_H),                         fGETQBIT(QsV, 2 * IDX + i0), IN);    } while (0)
#define fSTORERELEASE(EA, TYPE)    do {        fV_AL_CHECK(EA, fVECSIZE() - 1);    } while (0)
#define fLOADMMV(EA, DST) gen_vreg_load(ctx, DST##_off, EA, true)
#define fLOADMMVU(EA, DST) gen_vreg_load(ctx, DST##_off, EA, false)
#define fSTOREMMV(EA, SRC)    gen_vreg_store(ctx, EA, SRC##_off, insn->slot, true)
#define fSTOREMMVQ(EA, SRC, MASK)    gen_vreg_masked_store(ctx, EA, SRC##_off, MASK##_off, insn->slot, false)
#define fSTOREMMVNQ(EA, SRC, MASK)     gen_vreg_masked_store(ctx, EA, SRC##_off, MASK##_off, INSN_SLOT, true)
#define fSTOREMMVU(EA, SRC)     gen_vreg_store(ctx, EA, SRC##_off, INSN_SLOT, false)
#define fVFOREACH(WIDTH, VAR) for (VAR = 0; VAR < fVELEM(WIDTH); VAR++)
#define fVARRAY_ELEMENT_ACCESS(ARRAY, TYPE, INDEX)    ARRAY.v[(INDEX) / (fVECSIZE() / (sizeof(ARRAY.TYPE[0])))].TYPE[(INDEX) %    (fVECSIZE() / (sizeof(ARRAY.TYPE[0])))]
#define fVSATDW(U, V) fVSATW(((((long long)U) << 32) | fZXTN(32, 64, V)))
#define fVASL_SATHI(U, V) fVSATW(((U) << 1) | ((V) >> 31))
#define fVUADDSAT(WIDTH, U, V)    fVSATUN(WIDTH, fZXTN(WIDTH, 2 * WIDTH, U) + fZXTN(WIDTH, 2 * WIDTH, V))
#define fVSADDSAT(WIDTH, U, V)    fVSATN(WIDTH, fSXTN(WIDTH, 2 * WIDTH, U) + fSXTN(WIDTH, 2 * WIDTH, V))
#define fVUSUBSAT(WIDTH, U, V)    fVSATUN(WIDTH, fZXTN(WIDTH, 2 * WIDTH, U) - fZXTN(WIDTH, 2 * WIDTH, V))
#define fVSSUBSAT(WIDTH, U, V)    fVSATN(WIDTH, fSXTN(WIDTH, 2 * WIDTH, U) - fSXTN(WIDTH, 2 * WIDTH, V))
#define fVAVGU(WIDTH, U, V)    ((fZXTN(WIDTH, 2 * WIDTH, U) + fZXTN(WIDTH, 2 * WIDTH, V)) >> 1)
#define fVAVGURND(WIDTH, U, V)    ((fZXTN(WIDTH, 2 * WIDTH, U) + fZXTN(WIDTH, 2 * WIDTH, V) + 1) >> 1)
#define fVNAVGU(WIDTH, U, V)    ((fZXTN(WIDTH, 2 * WIDTH, U) - fZXTN(WIDTH, 2 * WIDTH, V)) >> 1)
#define fVNAVGURNDSAT(WIDTH, U, V)    fVSATUN(WIDTH, ((fZXTN(WIDTH, 2 * WIDTH, U) -                     fZXTN(WIDTH, 2 * WIDTH, V) + 1) >> 1))
#define fVAVGS(WIDTH, U, V)    ((fSXTN(WIDTH, 2 * WIDTH, U) + fSXTN(WIDTH, 2 * WIDTH, V)) >> 1)
#define fVAVGSRND(WIDTH, U, V)    ((fSXTN(WIDTH, 2 * WIDTH, U) + fSXTN(WIDTH, 2 * WIDTH, V) + 1) >> 1)
#define fVNAVGS(WIDTH, U, V)    ((fSXTN(WIDTH, 2 * WIDTH, U) - fSXTN(WIDTH, 2 * WIDTH, V)) >> 1)
#define fVNAVGSRND(WIDTH, U, V)    ((fSXTN(WIDTH, 2 * WIDTH, U) - fSXTN(WIDTH, 2 * WIDTH, V) + 1) >> 1)
#define fVNAVGSRNDSAT(WIDTH, U, V)    fVSATN(WIDTH, ((fSXTN(WIDTH, 2 * WIDTH, U) -                    fSXTN(WIDTH, 2 * WIDTH, V) + 1) >> 1))
#define fVNOROUND(VAL, SHAMT) VAL
#define fVNOSAT(VAL) VAL
#define fVROUND(VAL, SHAMT)    ((VAL) + (((SHAMT) > 0) ? (1LL << ((SHAMT) - 1)) : 0))
#define fCARRY_FROM_ADD32(A, B, C)    (((fZXTN(32, 64, A) + fZXTN(32, 64, B) + C) >> 32) & 1)
#define fUARCH_NOTE_PUMP_4X()
#define fUARCH_NOTE_PUMP_2X()
#define IV1DEAD()
#define fGET10BIT(COE, VAL, POS)    do {        COE = (sextract32(VAL, 24 + 2 * POS, 2) << 8) |               extract32(VAL, POS * 8, 8);    } while (0);