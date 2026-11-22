/*
 * RunPositionController1.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "RunPositionController1".
 *
 * Model version              : 1.16
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Fri Oct 16 11:04:53 2026
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "RunPositionController1.h"
#include "RunPositionController1_private.h"
#include "RunPositionController1_dt.h"

/* options for Simulink Desktop Real-Time board 0 */
static double SLDRTBoardOptions0[] = {
  0.0,
  1.0,
  0.0,
  2.0,
  3.0,
  0.0,
  0.0,
};

/* list of Simulink Desktop Real-Time timers */
const int SLDRTTimerCount = 1;
const double SLDRTTimers[2] = {
  0.0001, 0.0,
};

/* list of Simulink Desktop Real-Time boards */
const int SLDRTBoardCount = 1;
SLDRTBOARD SLDRTBoards[1] = {
  { "National_Instruments/PCIe-6321", 4294967295U, 7, SLDRTBoardOptions0 },
};

/* Block signals (default storage) */
B_RunPositionController1_T RunPositionController1_B;

/* Continuous states */
X_RunPositionController1_T RunPositionController1_X;

/* Block states (default storage) */
DW_RunPositionController1_T RunPositionController1_DW;

/* Real-time model */
static RT_MODEL_RunPositionController1_T RunPositionController1_M_;
RT_MODEL_RunPositionController1_T *const RunPositionController1_M =
  &RunPositionController1_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  RunPositionController1_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  RunPositionController1_output();
  RunPositionController1_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  RunPositionController1_output();
  RunPositionController1_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void RunPositionController1_output(void)
{
  /* local block i/o variables */
  real_T rtb_EncoderInput;
  real_T rtb_IntegralGain;
  real_T rtb_SignPreSat;
  real_T rtb_ZeroGain;
  boolean_T rtb_NotEqual;
  if (rtmIsMajorTimeStep(RunPositionController1_M)) {
    /* set solver stop time */
    if (!(RunPositionController1_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&RunPositionController1_M->solverInfo,
                            ((RunPositionController1_M->Timing.clockTickH0 + 1) *
        RunPositionController1_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&RunPositionController1_M->solverInfo,
                            ((RunPositionController1_M->Timing.clockTick0 + 1) *
        RunPositionController1_M->Timing.stepSize0 +
        RunPositionController1_M->Timing.clockTickH0 *
        RunPositionController1_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(RunPositionController1_M)) {
    RunPositionController1_M->Timing.t[0] = rtsiGetT
      (&RunPositionController1_M->solverInfo);
  }

  /* Sin: '<Root>/Sine Wave' */
  RunPositionController1_B.SineWave = sin(RunPositionController1_P.SineWave_Freq
    * RunPositionController1_M->Timing.t[0] +
    RunPositionController1_P.SineWave_Phase) *
    RunPositionController1_P.SineWave_Amp +
    RunPositionController1_P.SineWave_Bias;

  /* TransferFcn: '<Root>/Transfer Fcn' */
  RunPositionController1_B.TransferFcn = 0.0;
  RunPositionController1_B.TransferFcn += RunPositionController1_P.TransferFcn_C
    * RunPositionController1_X.TransferFcn_CSTATE;

  /* Sum: '<Root>/Sum' */
  RunPositionController1_B.error = RunPositionController1_B.SineWave -
    RunPositionController1_B.TransferFcn;

  /* Gain: '<S1>/Gain1' */
  rtb_IntegralGain = RunPositionController1_P.Gain1_Gain *
    RunPositionController1_B.error;

  /* Gain: '<S40>/Filter Coefficient' incorporates:
   *  Gain: '<S31>/Derivative Gain'
   *  Integrator: '<S32>/Filter'
   *  Sum: '<S32>/SumD'
   */
  RunPositionController1_B.FilterCoefficient =
    (RunPositionController1_P.PIDController_D * rtb_IntegralGain -
     RunPositionController1_X.Filter_CSTATE) *
    RunPositionController1_P.PIDController_N;

  /* Sum: '<S46>/Sum' incorporates:
   *  Gain: '<S42>/Proportional Gain'
   *  Integrator: '<S37>/Integrator'
   */
  rtb_SignPreSat = (RunPositionController1_P.PIDController_P * rtb_IntegralGain
                    + RunPositionController1_X.Integrator_CSTATE) +
    RunPositionController1_B.FilterCoefficient;

  /* Saturate: '<S44>/Saturation' */
  if (rtb_SignPreSat >
      RunPositionController1_P.PIDController_UpperSaturationLimit) {
    /* Saturate: '<S44>/Saturation' */
    RunPositionController1_B.Saturation =
      RunPositionController1_P.PIDController_UpperSaturationLimit;
  } else if (rtb_SignPreSat <
             RunPositionController1_P.PIDController_LowerSaturationLimit) {
    /* Saturate: '<S44>/Saturation' */
    RunPositionController1_B.Saturation =
      RunPositionController1_P.PIDController_LowerSaturationLimit;
  } else {
    /* Saturate: '<S44>/Saturation' */
    RunPositionController1_B.Saturation = rtb_SignPreSat;
  }

  /* End of Saturate: '<S44>/Saturation' */

  /* Switch: '<Root>/Switch' */
  if (RunPositionController1_B.Saturation >
      RunPositionController1_P.Switch_Threshold) {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/CW'
     */
    RunPositionController1_B.Switch = RunPositionController1_P.CW_Value;
  } else {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/CCW'
     */
    RunPositionController1_B.Switch = RunPositionController1_P.CCW_Value;
  }

  /* End of Switch: '<Root>/Switch' */

  /* Abs: '<Root>/Abs' */
  rtb_ZeroGain = fabs(RunPositionController1_B.Saturation);

  /* Saturate: '<Root>/Saturation' */
  if (rtb_ZeroGain > RunPositionController1_P.Saturation_UpperSat) {
    rtb_ZeroGain = RunPositionController1_P.Saturation_UpperSat;
  } else {
    if (rtb_ZeroGain < RunPositionController1_P.Saturation_LowerSat) {
      rtb_ZeroGain = RunPositionController1_P.Saturation_LowerSat;
    }
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Gain: '<Root>/Gain' */
  RunPositionController1_B.Gain = RunPositionController1_P.Gain_Gain *
    rtb_ZeroGain;
  if (rtmIsMajorTimeStep(RunPositionController1_M)) {
    /* S-Function (sldrtdo): '<Root>/Digital Output1' */
    /* S-Function Block: <Root>/Digital Output1 */
    {
      RTBIO_DriverIO(0, DIGITALOUTPUT, IOWRITE, 1,
                     &RunPositionController1_P.DigitalOutput1_Channels, ((real_T*)
        (&RunPositionController1_B.Switch)),
                     &RunPositionController1_P.DigitalOutput1_BitMode);
    }

    /* S-Function (sldrtqo): '<Root>/Frequency Output' */
    /* S-Function Block: <Root>/Frequency Output */
    {
      {
        RTBIO_DriverIO(0, FREQUENCYOUTPUT, IOWRITE, 1,
                       &RunPositionController1_P.FrequencyOutput_Channels,
                       &RunPositionController1_P.FrequencyOutput_Frequency,
                       ((real_T*) (&RunPositionController1_B.Gain)));
      }
    }

    /* S-Function (sldrtei): '<Root>/Encoder Input' */
    /* S-Function Block: <Root>/Encoder Input */
    {
      ENCODERINPARM parm;
      parm.quad = (QUADMODE) 2;
      parm.index = (INDEXPULSE) 0;
      parm.infilter = RunPositionController1_P.EncoderInput_InputFilter;
      RTBIO_DriverIO(0, ENCODERINPUT, IOREAD, 1,
                     &RunPositionController1_P.EncoderInput_Channels,
                     &rtb_EncoderInput, &parm);
    }

    /* MATLAB Function: '<Root>/MATLAB Function' */
    if (rtb_EncoderInput > 2.147483648E+9) {
      RunPositionController1_B.ENCODER_DEGREE = (rtb_EncoderInput -
        4.294967296E+9) * 360.0 / 2000.0;
    } else {
      RunPositionController1_B.ENCODER_DEGREE = rtb_EncoderInput * 360.0 /
        2000.0;
    }

    /* End of MATLAB Function: '<Root>/MATLAB Function' */
  }

  /* Gain: '<S28>/ZeroGain' */
  rtb_ZeroGain = RunPositionController1_P.ZeroGain_Gain * rtb_SignPreSat;

  /* DeadZone: '<S30>/DeadZone' */
  if (rtb_SignPreSat >
      RunPositionController1_P.PIDController_UpperSaturationLimit) {
    rtb_SignPreSat -=
      RunPositionController1_P.PIDController_UpperSaturationLimit;
  } else if (rtb_SignPreSat >=
             RunPositionController1_P.PIDController_LowerSaturationLimit) {
    rtb_SignPreSat = 0.0;
  } else {
    rtb_SignPreSat -=
      RunPositionController1_P.PIDController_LowerSaturationLimit;
  }

  /* End of DeadZone: '<S30>/DeadZone' */

  /* RelationalOperator: '<S28>/NotEqual' */
  rtb_NotEqual = (rtb_ZeroGain != rtb_SignPreSat);

  /* Signum: '<S28>/SignPreSat' */
  if (rtb_SignPreSat < 0.0) {
    rtb_SignPreSat = -1.0;
  } else if (rtb_SignPreSat > 0.0) {
    rtb_SignPreSat = 1.0;
  } else if (rtb_SignPreSat == 0.0) {
    rtb_SignPreSat = 0.0;
  } else {
    rtb_SignPreSat = (rtNaN);
  }

  /* End of Signum: '<S28>/SignPreSat' */

  /* Gain: '<S34>/Integral Gain' */
  rtb_IntegralGain *= RunPositionController1_P.PIDController_I;

  /* DataTypeConversion: '<S28>/DataTypeConv1' */
  if (rtIsNaN(rtb_SignPreSat)) {
    rtb_SignPreSat = 0.0;
  } else {
    rtb_SignPreSat = fmod(rtb_SignPreSat, 256.0);
  }

  /* Signum: '<S28>/SignPreIntegrator' */
  if (rtb_IntegralGain < 0.0) {
    /* DataTypeConversion: '<S28>/DataTypeConv2' */
    rtb_ZeroGain = -1.0;
  } else if (rtb_IntegralGain > 0.0) {
    /* DataTypeConversion: '<S28>/DataTypeConv2' */
    rtb_ZeroGain = 1.0;
  } else if (rtb_IntegralGain == 0.0) {
    /* DataTypeConversion: '<S28>/DataTypeConv2' */
    rtb_ZeroGain = 0.0;
  } else {
    /* DataTypeConversion: '<S28>/DataTypeConv2' */
    rtb_ZeroGain = (rtNaN);
  }

  /* End of Signum: '<S28>/SignPreIntegrator' */

  /* DataTypeConversion: '<S28>/DataTypeConv2' */
  if (rtIsNaN(rtb_ZeroGain)) {
    rtb_ZeroGain = 0.0;
  } else {
    rtb_ZeroGain = fmod(rtb_ZeroGain, 256.0);
  }

  /* Logic: '<S28>/AND3' incorporates:
   *  DataTypeConversion: '<S28>/DataTypeConv1'
   *  DataTypeConversion: '<S28>/DataTypeConv2'
   *  RelationalOperator: '<S28>/Equal1'
   */
  RunPositionController1_B.AND3 = (rtb_NotEqual && ((rtb_SignPreSat < 0.0 ?
    (int32_T)(int8_T)-(int8_T)(uint8_T)-rtb_SignPreSat : (int32_T)(int8_T)
    (uint8_T)rtb_SignPreSat) == (rtb_ZeroGain < 0.0 ? (int32_T)(int8_T)-(int8_T)
    (uint8_T)-rtb_ZeroGain : (int32_T)(int8_T)(uint8_T)rtb_ZeroGain)));
  if (rtmIsMajorTimeStep(RunPositionController1_M)) {
    /* Memory: '<S28>/Memory' */
    RunPositionController1_B.Memory =
      RunPositionController1_DW.Memory_PreviousInput;
  }

  /* Switch: '<S28>/Switch' */
  if (RunPositionController1_B.Memory) {
    /* Switch: '<S28>/Switch' incorporates:
     *  Constant: '<S28>/Constant1'
     */
    RunPositionController1_B.Switch_l = RunPositionController1_P.Constant1_Value;
  } else {
    /* Switch: '<S28>/Switch' */
    RunPositionController1_B.Switch_l = rtb_IntegralGain;
  }

  /* End of Switch: '<S28>/Switch' */
}

/* Model update function */
void RunPositionController1_update(void)
{
  if (rtmIsMajorTimeStep(RunPositionController1_M)) {
    /* Update for Memory: '<S28>/Memory' */
    RunPositionController1_DW.Memory_PreviousInput =
      RunPositionController1_B.AND3;
  }

  if (rtmIsMajorTimeStep(RunPositionController1_M)) {
    rt_ertODEUpdateContinuousStates(&RunPositionController1_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++RunPositionController1_M->Timing.clockTick0)) {
    ++RunPositionController1_M->Timing.clockTickH0;
  }

  RunPositionController1_M->Timing.t[0] = rtsiGetSolverStopTime
    (&RunPositionController1_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.0001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++RunPositionController1_M->Timing.clockTick1)) {
      ++RunPositionController1_M->Timing.clockTickH1;
    }

    RunPositionController1_M->Timing.t[1] =
      RunPositionController1_M->Timing.clockTick1 *
      RunPositionController1_M->Timing.stepSize1 +
      RunPositionController1_M->Timing.clockTickH1 *
      RunPositionController1_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void RunPositionController1_derivatives(void)
{
  XDot_RunPositionController1_T *_rtXdot;
  _rtXdot = ((XDot_RunPositionController1_T *) RunPositionController1_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += RunPositionController1_P.TransferFcn_A *
    RunPositionController1_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += RunPositionController1_B.ENCODER_DEGREE;

  /* Derivatives for Integrator: '<S37>/Integrator' */
  _rtXdot->Integrator_CSTATE = RunPositionController1_B.Switch_l;

  /* Derivatives for Integrator: '<S32>/Filter' */
  _rtXdot->Filter_CSTATE = RunPositionController1_B.FilterCoefficient;
}

/* Model initialize function */
void RunPositionController1_initialize(void)
{
  /* Start for S-Function (sldrtdo): '<Root>/Digital Output1' */

  /* S-Function Block: <Root>/Digital Output1 */
  {
    RTBIO_DriverIO(0, DIGITALOUTPUT, IOWRITE, 1,
                   &RunPositionController1_P.DigitalOutput1_Channels,
                   &RunPositionController1_P.DigitalOutput1_InitialValue,
                   &RunPositionController1_P.DigitalOutput1_BitMode);
  }

  /* Start for S-Function (sldrtqo): '<Root>/Frequency Output' */

  /* S-Function Block: <Root>/Frequency Output */
  {
    {
      RTBIO_DriverIO(0, FREQUENCYOUTPUT, IOWRITE, 1,
                     &RunPositionController1_P.FrequencyOutput_Channels,
                     &RunPositionController1_P.FrequencyOutput_Frequency,
                     &RunPositionController1_P.FrequencyOutput_Duty);
    }
  }

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  RunPositionController1_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S37>/Integrator' */
  RunPositionController1_X.Integrator_CSTATE =
    RunPositionController1_P.PIDController_InitialConditionForIntegrator;

  /* InitializeConditions for Integrator: '<S32>/Filter' */
  RunPositionController1_X.Filter_CSTATE =
    RunPositionController1_P.PIDController_InitialConditionForFilter;

  /* InitializeConditions for S-Function (sldrtei): '<Root>/Encoder Input' */

  /* S-Function Block: <Root>/Encoder Input */
  {
    ENCODERINPARM parm;
    parm.quad = (QUADMODE) 2;
    parm.index = (INDEXPULSE) 0;
    parm.infilter = RunPositionController1_P.EncoderInput_InputFilter;
    RTBIO_DriverIO(0, ENCODERINPUT, IORESET, 1,
                   &RunPositionController1_P.EncoderInput_Channels, NULL, &parm);
  }

  /* InitializeConditions for Memory: '<S28>/Memory' */
  RunPositionController1_DW.Memory_PreviousInput =
    RunPositionController1_P.Memory_InitialCondition;
}

/* Model terminate function */
void RunPositionController1_terminate(void)
{
  /* Terminate for S-Function (sldrtdo): '<Root>/Digital Output1' */

  /* S-Function Block: <Root>/Digital Output1 */
  {
    RTBIO_DriverIO(0, DIGITALOUTPUT, IOWRITE, 1,
                   &RunPositionController1_P.DigitalOutput1_Channels,
                   &RunPositionController1_P.DigitalOutput1_FinalValue,
                   &RunPositionController1_P.DigitalOutput1_BitMode);
  }

  /* Terminate for S-Function (sldrtqo): '<Root>/Frequency Output' */

  /* S-Function Block: <Root>/Frequency Output */
  {
    {
      RTBIO_DriverIO(0, FREQUENCYOUTPUT, IOWRITE, 1,
                     &RunPositionController1_P.FrequencyOutput_Channels,
                     &RunPositionController1_P.FrequencyOutput_Frequency,
                     &RunPositionController1_P.FrequencyOutput_DutyFinalValue);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  RunPositionController1_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  RunPositionController1_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  RunPositionController1_initialize();
}

void MdlTerminate(void)
{
  RunPositionController1_terminate();
}

/* Registration function */
RT_MODEL_RunPositionController1_T *RunPositionController1(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  RunPositionController1_P.EncoderInput_InputFilter = rtInf;

  /* initialize real-time model */
  (void) memset((void *)RunPositionController1_M, 0,
                sizeof(RT_MODEL_RunPositionController1_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&RunPositionController1_M->solverInfo,
                          &RunPositionController1_M->Timing.simTimeStep);
    rtsiSetTPtr(&RunPositionController1_M->solverInfo, &rtmGetTPtr
                (RunPositionController1_M));
    rtsiSetStepSizePtr(&RunPositionController1_M->solverInfo,
                       &RunPositionController1_M->Timing.stepSize0);
    rtsiSetdXPtr(&RunPositionController1_M->solverInfo,
                 &RunPositionController1_M->derivs);
    rtsiSetContStatesPtr(&RunPositionController1_M->solverInfo, (real_T **)
                         &RunPositionController1_M->contStates);
    rtsiSetNumContStatesPtr(&RunPositionController1_M->solverInfo,
      &RunPositionController1_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&RunPositionController1_M->solverInfo,
      &RunPositionController1_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&RunPositionController1_M->solverInfo,
      &RunPositionController1_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&RunPositionController1_M->solverInfo,
      &RunPositionController1_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&RunPositionController1_M->solverInfo,
                          (&rtmGetErrorStatus(RunPositionController1_M)));
    rtsiSetRTModelPtr(&RunPositionController1_M->solverInfo,
                      RunPositionController1_M);
  }

  rtsiSetSimTimeStep(&RunPositionController1_M->solverInfo, MAJOR_TIME_STEP);
  RunPositionController1_M->intgData.y = RunPositionController1_M->odeY;
  RunPositionController1_M->intgData.f[0] = RunPositionController1_M->odeF[0];
  RunPositionController1_M->intgData.f[1] = RunPositionController1_M->odeF[1];
  RunPositionController1_M->intgData.f[2] = RunPositionController1_M->odeF[2];
  RunPositionController1_M->contStates = ((real_T *) &RunPositionController1_X);
  rtsiSetSolverData(&RunPositionController1_M->solverInfo, (void *)
                    &RunPositionController1_M->intgData);
  rtsiSetSolverName(&RunPositionController1_M->solverInfo,"ode3");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = RunPositionController1_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    RunPositionController1_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    RunPositionController1_M->Timing.sampleTimes =
      (&RunPositionController1_M->Timing.sampleTimesArray[0]);
    RunPositionController1_M->Timing.offsetTimes =
      (&RunPositionController1_M->Timing.offsetTimesArray[0]);

    /* task periods */
    RunPositionController1_M->Timing.sampleTimes[0] = (0.0);
    RunPositionController1_M->Timing.sampleTimes[1] = (0.0001);

    /* task offsets */
    RunPositionController1_M->Timing.offsetTimes[0] = (0.0);
    RunPositionController1_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(RunPositionController1_M, &RunPositionController1_M->Timing.tArray
             [0]);

  {
    int_T *mdlSampleHits = RunPositionController1_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    RunPositionController1_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(RunPositionController1_M, 10.0);
  RunPositionController1_M->Timing.stepSize0 = 0.0001;
  RunPositionController1_M->Timing.stepSize1 = 0.0001;

  /* External mode info */
  RunPositionController1_M->Sizes.checksums[0] = (660050114U);
  RunPositionController1_M->Sizes.checksums[1] = (1402314751U);
  RunPositionController1_M->Sizes.checksums[2] = (2231075092U);
  RunPositionController1_M->Sizes.checksums[3] = (4258182839U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    RunPositionController1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(RunPositionController1_M->extModeInfo,
      &RunPositionController1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(RunPositionController1_M->extModeInfo,
                        RunPositionController1_M->Sizes.checksums);
    rteiSetTPtr(RunPositionController1_M->extModeInfo, rtmGetTPtr
                (RunPositionController1_M));
  }

  RunPositionController1_M->solverInfoPtr =
    (&RunPositionController1_M->solverInfo);
  RunPositionController1_M->Timing.stepSize = (0.0001);
  rtsiSetFixedStepSize(&RunPositionController1_M->solverInfo, 0.0001);
  rtsiSetSolverMode(&RunPositionController1_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  RunPositionController1_M->blockIO = ((void *) &RunPositionController1_B);
  (void) memset(((void *) &RunPositionController1_B), 0,
                sizeof(B_RunPositionController1_T));

  /* parameters */
  RunPositionController1_M->defaultParam = ((real_T *)&RunPositionController1_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &RunPositionController1_X;
    RunPositionController1_M->contStates = (x);
    (void) memset((void *)&RunPositionController1_X, 0,
                  sizeof(X_RunPositionController1_T));
  }

  /* states (dwork) */
  RunPositionController1_M->dwork = ((void *) &RunPositionController1_DW);
  (void) memset((void *)&RunPositionController1_DW, 0,
                sizeof(DW_RunPositionController1_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    RunPositionController1_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  RunPositionController1_M->Sizes.numContStates = (3);/* Number of continuous states */
  RunPositionController1_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  RunPositionController1_M->Sizes.numY = (0);/* Number of model outputs */
  RunPositionController1_M->Sizes.numU = (0);/* Number of model inputs */
  RunPositionController1_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  RunPositionController1_M->Sizes.numSampTimes = (2);/* Number of sample times */
  RunPositionController1_M->Sizes.numBlocks = (37);/* Number of blocks */
  RunPositionController1_M->Sizes.numBlockIO = (11);/* Number of block outputs */
  RunPositionController1_M->Sizes.numBlockPrms = (40);/* Sum of parameter "widths" */
  return RunPositionController1_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
