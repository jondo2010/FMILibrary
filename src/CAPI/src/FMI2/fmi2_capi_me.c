/*
    Copyright (C) 2012 Modelon AB

    This program is free software: you can redistribute it and/or modify
    it under the terms of the BSD style license.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    FMILIB_License.txt file for more details.

    You should have received a copy of the FMILIB_License.txt file
    along with this program. If not, contact Modelon AB <http://www.modelon.com>.
*/

#include <assert.h>
#include <FMI2/fmi2_capi.h>
#include <FMI2/fmi2_capi_impl.h>


fmi2_status_t fmi2_capi_enter_event_mode(const fmi2_capi_t* fmu, fmi2_component_t c)
{
    assert(fmu); assert(c);
    jm_log_verbose(fmu->callbacks, FMI_CAPI_MODULE_NAME, "Calling fmi2EnterEventMode");
    return fmu->fmi2EnterEventMode(c);
}

fmi2_status_t fmi2_capi_new_discrete_states(const fmi2_capi_t* fmu, fmi2_component_t c, fmi2_event_info_t* eventInfo)
{
    assert(fmu); assert(c);
    jm_log_verbose(fmu->callbacks, FMI_CAPI_MODULE_NAME, "Calling fmi2NewDiscreteStates");
    return fmu->fmi2NewDiscreteStates(c, eventInfo);
}

fmi2_status_t fmi2_capi_enter_continuous_time_mode(const fmi2_capi_t* fmu, fmi2_component_t c)
{
    assert(fmu); assert(c);
    jm_log_verbose(fmu->callbacks, FMI_CAPI_MODULE_NAME, "Calling fmi2EnterContinuousTimeMode");
    return fmu->fmi2EnterContinuousTimeMode(c);
}

fmi2_status_t fmi2_capi_set_time(const fmi2_capi_t* fmu, fmi2_component_t c, fmi2_real_t time)
{
	assert(fmu); assert(c);
	jm_log_debug(fmu->callbacks, FMI_CAPI_MODULE_NAME, "Calling fmi2SetTime");
	return fmu->fmi2SetTime(c, time);
}

fmi2_status_t fmi2_capi_set_continuous_states(const fmi2_capi_t* fmu, fmi2_component_t c, const fmi2_real_t x[], size_t nx)
{
	assert(fmu); assert(c);
	jm_log_debug(fmu->callbacks, FMI_CAPI_MODULE_NAME, "Calling fmi2SetContinuousStates");
	return fmu->fmi2SetContinuousStates(c, x, nx);
}

fmi2_status_t fmi2_capi_completed_integrator_step(const fmi2_capi_t* fmu, fmi2_component_t c,
  fmi2_boolean_t noSetFMUStatePriorToCurrentPoint,
  fmi2_boolean_t* enterEventMode, fmi2_boolean_t* terminateSimulation)
{
    assert(fmu); assert(c);
    jm_log_debug(fmu->callbacks, FMI_CAPI_MODULE_NAME, "Calling fmi2CompletedIntegratorStep");
    return fmu->fmi2CompletedIntegratorStep(c, noSetFMUStatePriorToCurrentPoint,
                                           enterEventMode, terminateSimulation);
}

fmi2_status_t fmi2_capi_get_derivatives(const fmi2_capi_t* fmu, fmi2_component_t c, fmi2_real_t derivatives[], size_t nx)
{
	assert(fmu); assert(c);
	jm_log_debug(fmu->callbacks, FMI_CAPI_MODULE_NAME, "Calling fmi2GetDerivatives");
	return fmu->fmi2GetDerivatives(c, derivatives, nx);
}

fmi2_status_t fmi2_capi_get_event_indicators(const fmi2_capi_t* fmu, fmi2_component_t c, fmi2_real_t eventIndicators[], size_t ni)
{
	assert(fmu); assert(c);
	jm_log_debug(fmu->callbacks, FMI_CAPI_MODULE_NAME, "Calling fmi2GetEventIndicators");
	return fmu->fmi2GetEventIndicators(c, eventIndicators, ni);
}

fmi2_status_t fmi2_capi_get_continuous_states(const fmi2_capi_t* fmu, fmi2_component_t c, fmi2_real_t states[], size_t nx)
{
	assert(fmu); assert(c);
	jm_log_debug(fmu->callbacks, FMI_CAPI_MODULE_NAME, "Calling fmi2GetContinuousStates");
	return fmu->fmi2GetContinuousStates(c, states, nx);
}

fmi2_status_t fmi2_capi_get_nominals_of_continuous_states(const fmi2_capi_t* fmu, fmi2_component_t c, fmi2_real_t x_nominal[], size_t nx)
{
	assert(fmu); assert(c);
	jm_log_debug(fmu->callbacks, FMI_CAPI_MODULE_NAME, "Calling fmi2GetNominalsOfContinuousStates");
	return fmu->fmi2GetNominalsOfContinuousStates(c, x_nominal, nx);
}
