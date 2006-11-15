/* Generated by: ../../genfft/gen_twiddle_c -standalone -fma -reorder-insns -simd -compact -variables 100000 -include fftw-spu.h -trivial-stores -n 12 -name X(spu_t1fv_12) */

/*
 * This function contains 59 FP additions, 42 FP multiplications,
 * (or, 41 additions, 24 multiplications, 18 fused multiply/add),
 * 75 stack variables, and 24 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: algsimp.ml,v 1.9 2006-02-12 23:34:12 athena Exp $
 * $Id: fft.ml,v 1.4 2006-01-05 03:04:27 stevenj Exp $
 * $Id: gen_twiddle_c.ml,v 1.14 2006-02-12 23:34:12 athena Exp $
 */

#include "fftw-spu.h"

const R *X(spu_t1fv_12) (R *ri, R *ii, const R *W, stride ios, INT m, INT dist) {
     DVK(KP866025403, +0.866025403784438646763723170752936183471402627);
     DVK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT i;
     R *x;
     x = ri;
     for (i = m; i > 0; i = i - VL, x = x + (VL * dist), W = W + (TWVL * 22), MAKE_VOLATILE_STRIDE(ios)) {
	  V TY, T7, Tf, TZ, TE, TQ, T11, Tw, TA, T12, Tr, TP, T1, T3, Td;
	  V Tb, T9, T5, T2, Tc, Ta, T8, T4, TC, T6, TD, Te, Ti, Tk, Ty;
	  V Tu, Tp, Tn, Th, Tj, Tx, Tt, To, Tm, Tl, Tv, Tq, Tz, T16, T17;
	  V T14, T15, T10, T13, T18, T19, TM, TN, TI, Ts, TF, TJ, Tg, TB, TH;
	  V TK, TG, TL, TR, TV, TO, TU, TT, TW, TS, TX;
	  T1 = LD(&(x[0]), dist, &(x[0]));
	  T2 = LD(&(x[WS(ios, 4)]), dist, &(x[0]));
	  T3 = BYTWJ(&(W[TWVL * 6]), T2);
	  Tc = LD(&(x[WS(ios, 2)]), dist, &(x[0]));
	  Td = BYTWJ(&(W[TWVL * 2]), Tc);
	  Ta = LD(&(x[WS(ios, 10)]), dist, &(x[0]));
	  Tb = BYTWJ(&(W[TWVL * 18]), Ta);
	  T8 = LD(&(x[WS(ios, 6)]), dist, &(x[0]));
	  T9 = BYTWJ(&(W[TWVL * 10]), T8);
	  T4 = LD(&(x[WS(ios, 8)]), dist, &(x[0]));
	  T5 = BYTWJ(&(W[TWVL * 14]), T4);
	  T6 = VADD(T3, T5);
	  TC = VSUB(T5, T3);
	  TY = VADD(T1, T6);
	  T7 = VFNMS(LDK(KP500000000), T6, T1);
	  TD = VSUB(Td, Tb);
	  Te = VADD(Tb, Td);
	  Tf = VFNMS(LDK(KP500000000), Te, T9);
	  TZ = VADD(T9, Te);
	  TE = VSUB(TC, TD);
	  TQ = VADD(TC, TD);
	  Th = LD(&(x[WS(ios, 11)]), dist, &(x[WS(ios, 1)]));
	  Ti = BYTWJ(&(W[TWVL * 20]), Th);
	  Tj = LD(&(x[WS(ios, 7)]), dist, &(x[WS(ios, 1)]));
	  Tk = BYTWJ(&(W[TWVL * 12]), Tj);
	  Tx = LD(&(x[WS(ios, 9)]), dist, &(x[WS(ios, 1)]));
	  Ty = BYTWJ(&(W[TWVL * 16]), Tx);
	  Tt = LD(&(x[WS(ios, 3)]), dist, &(x[WS(ios, 1)]));
	  Tu = BYTWJ(&(W[TWVL * 4]), Tt);
	  To = LD(&(x[WS(ios, 5)]), dist, &(x[WS(ios, 1)]));
	  Tp = BYTWJ(&(W[TWVL * 8]), To);
	  Tm = LD(&(x[WS(ios, 1)]), dist, &(x[WS(ios, 1)]));
	  Tn = BYTWJ(&(W[0]), Tm);
	  Tv = VADD(Tk, Ti);
	  Tl = VSUB(Ti, Tk);
	  T11 = VADD(Tu, Tv);
	  Tw = VFNMS(LDK(KP500000000), Tv, Tu);
	  Tq = VSUB(Tn, Tp);
	  Tz = VADD(Tn, Tp);
	  TA = VFNMS(LDK(KP500000000), Tz, Ty);
	  T12 = VADD(Ty, Tz);
	  Tr = VADD(Tl, Tq);
	  TP = VSUB(Tl, Tq);
	  T10 = VSUB(TY, TZ);
	  T16 = VADD(TY, TZ);
	  T17 = VADD(T11, T12);
	  T13 = VSUB(T11, T12);
	  T14 = VFNMSI(T13, T10);
	  T15 = VFMAI(T13, T10);
	  ST(&(x[WS(ios, 9)]), T14, dist, &(x[WS(ios, 1)]));
	  ST(&(x[WS(ios, 3)]), T15, dist, &(x[WS(ios, 1)]));
	  T18 = VSUB(T16, T17);
	  T19 = VADD(T16, T17);
	  ST(&(x[WS(ios, 6)]), T18, dist, &(x[0]));
	  ST(&(x[0]), T19, dist, &(x[0]));
	  Tg = VSUB(T7, Tf);
	  TM = VADD(T7, Tf);
	  TI = VFNMS(LDK(KP866025403), Tr, Tg);
	  Ts = VFMA(LDK(KP866025403), Tr, Tg);
	  TN = VADD(Tw, TA);
	  TB = VSUB(Tw, TA);
	  TF = VFNMS(LDK(KP866025403), TE, TB);
	  TJ = VFMA(LDK(KP866025403), TE, TB);
	  TG = VFNMSI(TF, Ts);
	  TH = VFMAI(TF, Ts);
	  ST(&(x[WS(ios, 1)]), TG, dist, &(x[WS(ios, 1)]));
	  TL = VFMAI(TJ, TI);
	  TK = VFNMSI(TJ, TI);
	  ST(&(x[WS(ios, 7)]), TL, dist, &(x[WS(ios, 1)]));
	  ST(&(x[WS(ios, 11)]), TH, dist, &(x[WS(ios, 1)]));
	  ST(&(x[WS(ios, 5)]), TK, dist, &(x[WS(ios, 1)]));
	  TR = VMUL(LDK(KP866025403), VSUB(TP, TQ));
	  TV = VMUL(LDK(KP866025403), VADD(TQ, TP));
	  TO = VSUB(TM, TN);
	  TU = VADD(TM, TN);
	  TS = VFMAI(TR, TO);
	  TT = VFNMSI(TR, TO);
	  ST(&(x[WS(ios, 2)]), TS, dist, &(x[0]));
	  TX = VFNMSI(TV, TU);
	  TW = VFMAI(TV, TU);
	  ST(&(x[WS(ios, 8)]), TX, dist, &(x[0]));
	  ST(&(x[WS(ios, 10)]), TT, dist, &(x[0]));
	  ST(&(x[WS(ios, 4)]), TW, dist, &(x[0]));
     }
     return W;
}
