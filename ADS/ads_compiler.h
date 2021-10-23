/*
 * ads © 2021 by Kilian Jugie is licensed under Attribution 4.0 International.
 * To view a copy of this license, visit http ://creativecommons.org/licenses/by/4.0/
 */

#pragma once

#ifdef _MSC_VER
#define ADS_C_MSC
#elif defined(__GNUC__)
#define ADS_C_GCC
#else
#define ADS_C_OTHER
#endif

#ifdef ADS_C_MSC
#define ADS_FORCEINLINE __forceinline
#elif defined(ADS_C_GCC)
#define ADS_FORCEINLINE __attribute__((always_inline))
#elif defined(ADS_C_OTHER)
#define ADS_FORCEINLINE inline
#else
#error ADS_C_X must be defined
#endif // ADS_C_MSC

#if defined(ADS_C_MSC) || defined(ADS_C_GCC)
#define ADS_COUNTER __COUNTER__
#else
extern unsigned __ads_counter;
#define ADS_COUNTER ++__ads_counter;
#endif // 

