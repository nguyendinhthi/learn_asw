/* ----------------------------------------------------------------------
******************************************************************************
* @file    version.h
* @author  Central LAB
* @version V2.0.0
* @date    22-June-2016
* @brief   Header for main.c module
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/
#ifndef STM_X_CLOUD_AWS_VERSION_H_
#define STM_X_CLOUD_AWS_VERSION_H_

/**
 * @brief MAJOR version, incremented when Major Features added.
 */
#define STM_X_CLOUD_AWS_VERSION_MAJOR 1
/**
 * @brief MINOR version when Minor Features added.
 */
#define STM_X_CLOUD_AWS_VERSION_MINOR 0
/**
 * @brief PATCH version when bug fixes are made.
 */
#define STM_X_CLOUD_AWS_VERSION_PATCH 0
/**
 * @brief TAG is an (optional) tag appended to the version for Internal Review.
 */
#define STM_X_CLOUD_AWS_VERSION_TAG ""

/**
* @brief Banner Information about the package
* @param None
* @retval None
*/
#define version_banner()\
{\
  printf("\r\n\n/********************************************************\n");\
  printf("\r *                                                      *\n");\
  printf("\r * FP-CLD-AWS1 Software v%d.%d.%d                          *\n",\
  STM_X_CLOUD_AWS_VERSION_MAJOR, STM_X_CLOUD_AWS_VERSION_MINOR, STM_X_CLOUD_AWS_VERSION_PATCH);\
  printf("\r *                                                      *\n");\
  printf("\r *******************************************************/\n");\
}

#endif /* STM_X_CLOUD_AWS_VERSION_H_ */
