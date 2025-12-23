// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vstream_pipeline.h for the primary calling header

#ifndef VERILATED_VSTREAM_PIPELINE___024ROOT_H_
#define VERILATED_VSTREAM_PIPELINE___024ROOT_H_  // guard

#include "verilated.h"


class Vstream_pipeline__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vstream_pipeline___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(in_valid,0,0);
    VL_OUT8(in_ready,0,0);
    VL_OUT8(out_valid,0,0);
    VL_IN8(out_ready,0,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    VL_IN(in_data,31,0);
    VL_OUT(out_data,31,0);
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vstream_pipeline__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vstream_pipeline___024root(Vstream_pipeline__Syms* symsp, const char* v__name);
    ~Vstream_pipeline___024root();
    VL_UNCOPYABLE(Vstream_pipeline___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
