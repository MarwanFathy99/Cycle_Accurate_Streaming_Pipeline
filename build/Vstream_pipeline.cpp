// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vstream_pipeline__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vstream_pipeline::Vstream_pipeline(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vstream_pipeline__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , in_valid{vlSymsp->TOP.in_valid}
    , in_ready{vlSymsp->TOP.in_ready}
    , out_valid{vlSymsp->TOP.out_valid}
    , out_ready{vlSymsp->TOP.out_ready}
    , in_data{vlSymsp->TOP.in_data}
    , out_data{vlSymsp->TOP.out_data}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vstream_pipeline::Vstream_pipeline(const char* _vcname__)
    : Vstream_pipeline(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vstream_pipeline::~Vstream_pipeline() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vstream_pipeline___024root___eval_debug_assertions(Vstream_pipeline___024root* vlSelf);
#endif  // VL_DEBUG
void Vstream_pipeline___024root___eval_static(Vstream_pipeline___024root* vlSelf);
void Vstream_pipeline___024root___eval_initial(Vstream_pipeline___024root* vlSelf);
void Vstream_pipeline___024root___eval_settle(Vstream_pipeline___024root* vlSelf);
void Vstream_pipeline___024root___eval(Vstream_pipeline___024root* vlSelf);

void Vstream_pipeline::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vstream_pipeline::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vstream_pipeline___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vstream_pipeline___024root___eval_static(&(vlSymsp->TOP));
        Vstream_pipeline___024root___eval_initial(&(vlSymsp->TOP));
        Vstream_pipeline___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vstream_pipeline___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vstream_pipeline::eventsPending() { return false; }

uint64_t Vstream_pipeline::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vstream_pipeline::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vstream_pipeline___024root___eval_final(Vstream_pipeline___024root* vlSelf);

VL_ATTR_COLD void Vstream_pipeline::final() {
    Vstream_pipeline___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vstream_pipeline::hierName() const { return vlSymsp->name(); }
const char* Vstream_pipeline::modelName() const { return "Vstream_pipeline"; }
unsigned Vstream_pipeline::threads() const { return 1; }
void Vstream_pipeline::prepareClone() const { contextp()->prepareClone(); }
void Vstream_pipeline::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vstream_pipeline::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vstream_pipeline___024root__trace_decl_types(VerilatedVcd* tracep);

void Vstream_pipeline___024root__trace_init_top(Vstream_pipeline___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vstream_pipeline___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vstream_pipeline___024root*>(voidSelf);
    Vstream_pipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vstream_pipeline___024root__trace_decl_types(tracep);
    Vstream_pipeline___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vstream_pipeline___024root__trace_register(Vstream_pipeline___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vstream_pipeline::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vstream_pipeline::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vstream_pipeline___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
