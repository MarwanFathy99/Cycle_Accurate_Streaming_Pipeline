// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vstream_pipeline__Syms.h"


void Vstream_pipeline___024root__trace_chg_0_sub_0(Vstream_pipeline___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vstream_pipeline___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstream_pipeline___024root__trace_chg_0\n"); );
    // Body
    Vstream_pipeline___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vstream_pipeline___024root*>(voidSelf);
    Vstream_pipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vstream_pipeline___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vstream_pipeline___024root__trace_chg_0_sub_0(Vstream_pipeline___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstream_pipeline___024root__trace_chg_0_sub_0\n"); );
    Vstream_pipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    bufp->chgBit(oldp+0,(vlSelfRef.clk));
    bufp->chgBit(oldp+1,(vlSelfRef.rst));
    bufp->chgIData(oldp+2,(vlSelfRef.in_data),32);
    bufp->chgBit(oldp+3,(vlSelfRef.in_valid));
    bufp->chgBit(oldp+4,(vlSelfRef.in_ready));
    bufp->chgIData(oldp+5,(vlSelfRef.out_data),32);
    bufp->chgBit(oldp+6,(vlSelfRef.out_valid));
    bufp->chgBit(oldp+7,(vlSelfRef.out_ready));
}

void Vstream_pipeline___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstream_pipeline___024root__trace_cleanup\n"); );
    // Locals
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    Vstream_pipeline___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vstream_pipeline___024root*>(voidSelf);
    Vstream_pipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
