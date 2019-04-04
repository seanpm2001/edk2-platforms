/** @file
  CPU Power Managment Custom Config Block.

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#ifndef _CPU_POWER_MGMT_CUSTOM_CONFIG_H_
#define _CPU_POWER_MGMT_CUSTOM_CONFIG_H_

#define CPU_POWER_MGMT_CUSTOM_CONFIG_REVISION 1

extern EFI_GUID gCpuPowerMgmtCustomConfigGuid;

#pragma pack (push,1)

///
/// Defines the maximum number of custom ratio states supported.
///
#define MAX_CUSTOM_RATIO_TABLE_ENTRIES 40

///
/// Defines the maximum number of custom ConfigTdp entries supported.
/// @warning: Changing this define would cause DWORD alignment issues in policy structures.
///
#define MAX_CUSTOM_CTDP_ENTRIES 3

///
/// This structure is used to describe the custom processor ratio table desired by the platform.
///
typedef struct {
  UINT16 MaxRatio;                                   ///< The maximum ratio of the custom ratio table.
  UINT8  NumberOfEntries;                            ///< The number of custom ratio state entries, ranges from 2 to 16 for a valid custom ratio table.
  UINT8  Rsvd0;                                      ///< Reserved for DWORD alignment.
  UINT32 Cpuid;                                      ///< The CPU ID for which this custom ratio table applies.
  UINT16 StateRatio[MAX_CUSTOM_RATIO_TABLE_ENTRIES]; ///< The processor ratios in the custom ratio table.
#if (MAX_CUSTOM_RATIO_TABLE_ENTRIES % 2)
  UINT16 Rsvd1;                                      ///< If there is an odd number of array entries, add padding for dword alignment.
#endif
} PPM_CUSTOM_RATIO_TABLE;

///
/// PPM Custom ConfigTdp Settings
///
typedef struct _PPM_CUSTOM_CTDP_TABLE {
  UINT32 CustomPowerLimit1Time      :  8;            ///< Short term Power Limit time window value for custom cTDP level.
  UINT32 CustomTurboActivationRatio :  8;            ///< Turbo Activation Ratio for custom cTDP level.
  UINT32 RsvdBits                   : 16;            ///< Bits reserved for DWORD alignment.
  UINT16 CustomPowerLimit1;                          ///< Short term Power Limit value for custom cTDP level. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.
  UINT16 CustomPowerLimit2;                          ///< Long term Power Limit value for custom cTDP level. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.
} PPM_CUSTOM_CTDP_TABLE;

/**
  CPU Power Management Custom Configuration Structure.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                                                  ///< Config Block Header
  PPM_CUSTOM_RATIO_TABLE CustomRatioTable;                                      ///< Custom Processor Ration Table Instance
  PPM_CUSTOM_CTDP_TABLE  CustomConfigTdpTable[MAX_CUSTOM_CTDP_ENTRIES];         ///< Custom ConfigTdp Settings Instance
  UINT32 ConfigTdpLock           : 1;                                           ///< Lock the ConfigTdp mode settings from runtime changes; <b>0: Disable</b>; 1: Enable.
  UINT32 ConfigTdpBios           : 1;                                           ///< Configure whether to load Configurable TDP SSDT; <b>0: Disable</b>; 1: Enable.
  UINT32 RsvdBits                : 30;                                          ///< Reserved for future use
} CPU_POWER_MGMT_CUSTOM_CONFIG;

#pragma pack (pop)

#endif // _CPU_POWER_MGMT_CUSTOM_CONFIG_H_