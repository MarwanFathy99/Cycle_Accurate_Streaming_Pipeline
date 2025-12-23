// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vstream_pipeline.h for the primary calling header

#include "Vstream_pipeline__pch.h"

void Vstream_pipeline___024root___ctor_var_reset(Vstream_pipeline___024root* vlSelf);

Vstream_pipeline___024root::Vstream_pipeline___024root(Vstream_pipeline__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vstream_pipeline___024root___ctor_var_reset(this);
}

void Vstream_pipeline___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vstream_pipeline___024root::~Vstream_pipeline___024root() {
}
