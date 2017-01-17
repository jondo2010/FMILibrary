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

/** \file fmi2_import.h
*  \brief Public interface to the FMI import C-library.
*/

#ifndef FMI2_IMPORT_H_
#define FMI2_IMPORT_H_

#include <stddef.h>
#include <fmilib_config.h>
#include <JM/jm_callbacks.h>
#include <FMI/fmi_import_util.h>
#include <FMI/fmi_import_context.h>
/* #include <FMI2/fmi2_xml_model_description.h> */

#include <FMI2/fmi2_types.h>
#include <FMI2/fmi2_functions.h>
#include <FMI2/fmi2_enums.h>

#include "fmi2_import_type.h"
#include "fmi2_import_unit.h"
#include "fmi2_import_variable.h"
#include "fmi2_import_variable_list.h"

#include "fmi2_import_capi.h"
#include "fmi2_import_convenience.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup  fmi2_import FMI 2.0 import interface
 *  All the structures used in the interfaces are intended to
 *  be treated as opaque objects by the client code.
 @{ 
 */

/**	\addtogroup fmi2_import_init Constuction, destruction and error handling
 * 	\addtogroup fmi2_import_gen General information retrieval
 *	\addtogroup fmi2_import_capi Interface to the standard FMI 2.0 "C" API
 *  \brief Convenient functions for calling the FMI functions. This interface wrappes the "C" API. 
 */
 /** @} */
 /** @} */

/** \addtogroup fmi2_import_init Constuction, destruction and error handling
@{
*/

/**
* \brief Retrieve the last error message.
*
* Error handling:
*
*  Many functions in the library return pointers to struct. An error is indicated by returning NULL/0-pointer.
*  If error is returned than fmi2_import_get_last_error() functions can be used to retrieve the error message.
*  If logging callbacks were specified then the same information is reported via logger.
*  Memory for the error string is allocated and deallocated in the module.
*  Client code should not store the pointer to the string since it can become invalid.
*    @param fmu An FMU object as returned by fmi2_import_parse_xml().
*    @return NULL-terminated string with an error message.
*/
FMILIB_EXPORT const char* fmi2_import_get_last_error(const fmi2_import_t* fmu);

/**
\brief Clear the error message.
* @param fmu An FMU object as returned by fmi2_import_parse_xml().
* @return 0 if further processing is possible. If it returns 1 then the 
*	error was not recoverable. The \p fmu object should then be freed and recreated.
*/
FMILIB_EXPORT int fmi2_import_clear_last_error(const fmi2_import_t* fmu);

/**
\brief Release the memory allocated
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT void fmi2_import_free(fmi2_import_t* fmu);
/** @}
\addtogroup fmi2_import_gen
 * \brief Functions for retrieving general model information. Memory for the strings is allocated and deallocated in the module.
 *   All the functions take an FMU object as returned by fmi2_import_parse_xml() as a parameter. 
 *   The information is retrieved from the XML file.
 * @{
*/
/** 
\brief Get model name. 
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT const char* fmi2_import_get_model_name(const fmi2_import_t* fmu);

/** \brief Retrieve capability flags by ID. */
FMILIB_EXPORT unsigned int fmi2_import_get_capability(const fmi2_import_t* , const fmi2_capabilities_enu_t id);

/** 
\brief Get model identifier for ModelExchange. 
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT const char* fmi2_import_get_model_identifier_ME(const fmi2_import_t* fmu);

/** 
\brief Get model identifier for CoSimulation. 
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT const char* fmi2_import_get_model_identifier_CS(const fmi2_import_t* fmu);

/** 
\brief Get FMU GUID. 
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT const char* fmi2_import_get_GUID(const fmi2_import_t* fmu);

/** 
\brief Get FMU description.
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT const char* fmi2_import_get_description(const fmi2_import_t* fmu);

/** 
\brief Get FMU author. 
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT const char* fmi2_import_get_author(const fmi2_import_t* fmu);

/** 
\brief Get FMU copyright information. 
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT const char* fmi2_import_get_copyright(const fmi2_import_t* fmu);

/** 
\brief Get FMU license information. 
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT const char* fmi2_import_get_license(const fmi2_import_t* fmu);

/** \brief Get FMU version.
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT const char* fmi2_import_get_model_version(const fmi2_import_t* fmu);

/** \brief Get FMI standard version (always 2.0). 
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT const char* fmi2_import_get_model_standard_version(const fmi2_import_t* fmu);

/** \brief Get FMU generation tool. 
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT const char* fmi2_import_get_generation_tool(const fmi2_import_t* fmu);

/** \brief Get FMU generation date and time. 
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT const char* fmi2_import_get_generation_date_and_time(const fmi2_import_t* fmu);

/** \brief Get variable naming convention used. 
@param fmu An fmu object as returned by fmi2_import_parse_xml().
*/
FMILIB_EXPORT fmi2_variable_naming_convension_enu_t fmi2_import_get_naming_convention(const fmi2_import_t* fmu);

/** \brief Get the number of continuous states. 
*/
FMILIB_EXPORT size_t fmi2_import_get_number_of_continuous_states(const fmi2_import_t* fmu);

/** \brief Get the number of event indicators. */
FMILIB_EXPORT size_t fmi2_import_get_number_of_event_indicators(const fmi2_import_t* fmu);

/** \brief Get the start time for default experiment as specified in the XML file. */
FMILIB_EXPORT double fmi2_import_get_default_experiment_start(const fmi2_import_t* fmu);

/** \brief Get the stop time for default experiment as specified in the XML file. */
FMILIB_EXPORT double fmi2_import_get_default_experiment_stop(const fmi2_import_t* fmu);

/** \brief Get the tolerance for default experiment as specified in the XML file. */
FMILIB_EXPORT double fmi2_import_get_default_experiment_tolerance(const fmi2_import_t* fmu);

/** \brief Get the step size for default experiment as specified in the XML file. */
FMILIB_EXPORT double fmi2_import_get_default_experiment_step(const fmi2_import_t* fmu);

/** \brief Get the type of the FMU (model exchange or co-simulation) */
FMILIB_EXPORT fmi2_fmu_kind_enu_t fmi2_import_get_fmu_kind(const fmi2_import_t* fmu);

/** \brief Get the list of all the type definitions in the model*/
FMILIB_EXPORT fmi2_import_type_definitions_t* fmi2_import_get_type_definitions(const fmi2_import_t* );

/** \brief Get a list of all the unit definitions in the model. */
FMILIB_EXPORT fmi2_import_unit_definitions_t* fmi2_import_get_unit_definitions(const fmi2_import_t* fmu);

/** \brief Get the variable with the same value reference that is not an alias*/
FMILIB_EXPORT fmi2_import_variable_t* fmi2_import_get_variable_alias_base(const fmi2_import_t* fmu,fmi2_import_variable_t*);

/**
    Get the list of all the variables aliased to the given one (including the base one).

    Note that the list is ordered: base variable, aliases, negated aliases.
*/
FMILIB_EXPORT fmi2_import_variable_list_t* fmi2_import_get_variable_aliases(const fmi2_import_t* fmu,const fmi2_import_variable_t*);

/** \brief Get the list of all the variables in the model.
* @param fmu An FMU object as returned by fmi2_import_parse_xml().
* @param sortOrder Specifies the order of the variables in the list: 
		0 - original order as found in the XML file; 1 - sorted alfabetically by variable name; 2 sorted by types/value references.
* @return a variable list with all the variables in the model.
*
* Note that variable lists are allocated dynamically and must be freed when not needed any longer.
*/
FMILIB_EXPORT fmi2_import_variable_list_t* fmi2_import_get_variable_list(const fmi2_import_t* fmu, int sortOrder);

/** \brief Create a variable list with a single variable.
  
\param fmu An FMU object that this variable list will reference.
\param v A variable.
*/
FMILIB_EXPORT fmi2_import_variable_list_t* fmi2_import_create_var_list(const fmi2_import_t* fmu,const fmi2_import_variable_t* v);

/** \brief Get the number of vendors that had annotations in the XML*/
FMILIB_EXPORT size_t fmi2_import_get_vendors_num(const fmi2_import_t* fmu);

/** \brief Get the name of the vendor with that had annotations in the XML by index */
FMILIB_EXPORT const char* fmi2_import_get_vendor_name(const fmi2_import_t* fmu, const size_t index);

/** \brief Get the number of log categories defined in the XML */
FMILIB_EXPORT size_t fmi2_import_get_log_categories_num(const fmi2_import_t* fmu);

/** \brief Get the log category by index */
FMILIB_EXPORT const char* fmi2_import_get_log_category(const fmi2_import_t* fmu, const size_t index);

/** \brief Get the log category description by index */
FMILIB_EXPORT const char* fmi2_import_get_log_category_description(const fmi2_import_t* fmu, const size_t index);

/** \brief Get the number of source files for ME defined in the XML */
FMILIB_EXPORT size_t fmi2_import_get_source_files_me_num(const fmi2_import_t* fmu);

/** \brief Get the ME source file by index */
FMILIB_EXPORT const char* fmi2_import_get_source_file_me(const fmi2_import_t* fmu, const size_t index);

/** \brief Get the number of source files for CS defined in the XML */
FMILIB_EXPORT size_t fmi2_import_get_source_files_cs_num(const fmi2_import_t* fmu);

/** \brief Get the CS source file by index */
FMILIB_EXPORT const char* fmi2_import_get_source_file_cs(const fmi2_import_t* fmu, const size_t index);

/**
	\brief Get variable by variable name.
	\param fmu - An fmu object as returned by fmi2_import_parse_xml().
	\param name - variable name
	\return variable pointer.
*/
FMILIB_EXPORT fmi2_import_variable_t* fmi2_import_get_variable_by_name(const fmi2_import_t* fmu, const char* name);

/**
	\brief Get variable by value reference.
	\param fmu - An fmu object as returned by fmi2_import_parse_xml().
	\param baseType - basic data type
	\param vr - value reference
	\return variable pointer.
*/
FMILIB_EXPORT fmi2_import_variable_t* fmi2_import_get_variable_by_vr(const fmi2_import_t* fmu, fmi2_base_type_enu_t baseType, fmi2_value_reference_t vr);

/** \brief Get the list of all the output variables in the model.
* @param fmu An FMU object as returned by fmi2_import_parse_xml().
* @return a variable list with all the output variables in the model.
*
* Note that variable lists are allocated dynamically and must be freed when not needed any longer.
*/
FMILIB_EXPORT fmi2_import_variable_list_t* fmi2_import_get_outputs_list(const fmi2_import_t* fmu);

/** \brief Get the list of all the derivative variables in the model.
* @param fmu An FMU object as returned by fmi2_import_parse_xml().
* @return a variable list with all the continuous state derivatives in the model.
*
* Note that variable lists are allocated dynamically and must be freed when not needed any longer.
*/
FMILIB_EXPORT fmi2_import_variable_list_t* fmi2_import_get_derivatives_list(const fmi2_import_t* fmu);

/** \brief Get the list of all the discrete state variables in the model.
* @param fmu An FMU object as returned by fmi2_import_parse_xml().
* @return a variable list with all the discrete state variables in the model.
*
* Note that variable lists are allocated dynamically and must be freed when not needed any longer.
*/
FMILIB_EXPORT fmi2_import_variable_list_t* fmi2_import_get_discrete_states_list(const fmi2_import_t* fmu);

/** \brief Get the list of all the initial unknown variables in the model.
* @param fmu An FMU object as returned by fmi2_import_parse_xml().
* @return a variable list with all the initial unknowns in the model.
*
* Note that variable lists are allocated dynamically and must be freed when not needed any longer.
*/
FMILIB_EXPORT fmi2_import_variable_list_t* fmi2_import_get_initial_unknowns_list(const fmi2_import_t* fmu);

/** \brief Get dependency information in row-compressed format. 
 * @param fmu An FMU object as returned by fmi2_import_parse_xml(). 
 * @param startIndex - outputs a pointer to an array of start indices (size of array is number of outputs + 1).
 *                     First element is zero, last is equal to the number of elements in the dependency and factor arrays. 
 *                     NULL pointer is returned if no dependency information was provided in the XML. 
 * @param dependency - outputs a pointer to the dependency index data. Indices are 1-based. Index equals to zero  
 *                     means "depends on all" (no information in the XML). 
 * @param factorKind - outputs a pointer to the factor kind data. The values can be converted to ::fmi2_dependency_factor_kind_enu_t 
 */ 
FMILIB_EXPORT void fmi2_import_get_outputs_dependencies(const fmi2_import_t* fmu, size_t** startIndex, size_t** dependency, char** factorKind);
 
/** \brief Get dependency information in row-compressed format. 
 * @param fmu An FMU object as returned by fmi2_import_parse_xml(). 
 * @param startIndex - outputs a pointer to an array of start indices (size of array is number of derivatives + 1).
 *                     First element is zero, last is equal to the number of elements in the dependency and factor arrays. 
 *                     NULL pointer is returned if no dependency information was provided in the XML. 
 * @param dependency - outputs a pointer to the dependency index data. Indices are 1-based. Index equals to zero  
 *                     means "depends on all" (no information in the XML). 
 * @param factorKind - outputs a pointer to the factor kind data. The values can be converted to ::fmi2_dependency_factor_kind_enu_t 
 */ 
FMILIB_EXPORT void fmi2_import_get_derivatives_dependencies(fmi2_import_t* fmu, size_t** startIndex, size_t** dependency, char** factorKind);

/** \brief Get dependency information in row-compressed format. 
 * @param fmu An FMU object as returned by fmi2_import_parse_xml(). 
 * @param startIndex - outputs a pointer to an array of start indices (size of array is number of discrete states + 1).
 *                     First element is zero, last is equal to the number of elements in the dependency and factor arrays. 
 *                     NULL pointer is returned if no dependency information was provided in the XML. 
 * @param dependency - outputs a pointer to the dependency index data. Indices are 1-based. Index equals to zero  
 *                     means "depends on all" (no information in the XML). 
 * @param factorKind - outputs a pointer to the factor kind data. The values can be converted to ::fmi2_dependency_factor_kind_enu_t 
 */ 
FMILIB_EXPORT void fmi2_import_get_discrete_states_dependencies(fmi2_import_t* fmu, size_t** startIndex, size_t** dependency, char** factorKind);
 
/** \brief Get dependency information in row-compressed format. 
 * @param fmu An FMU object as returned by fmi2_import_parse_xml(). 
 * @param startIndex - outputs a pointer to an array of start indices (size of array is number of initial unknowns + 1).
 *                     First element is zero, last is equal to the number of elements in the dependency and factor arrays. 
 *                     NULL pointer is returned if no dependency information was provided in the XML. 
 * @param dependency - outputs a pointer to the dependency index data. Indices are 1-based. Index equals to zero  
 *                     means "depends on all" (no information in the XML). 
 * @param factorKind - outputs a pointer to the factor kind data. The values can be converted to ::fmi2_dependency_factor_kind_enu_t 
 */ 
FMILIB_EXPORT void fmi2_import_get_initial_unknowns_dependencies(fmi2_import_t* fmu, size_t** startIndex, size_t** dependency, char** factorKind);
 
/**@} */

#ifdef __cplusplus
}
#endif

#endif
