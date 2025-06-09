#pragma once

#if defined(RLL_STRINGIFY_EX)
#  undef RLL_STRINGIFY_EX
#endif
#define RLL_STRINGIFY_EX(x) #x

#if defined(RLL_STRINGIFY)
#  undef RLL_STRINGIFY
#endif
#define RLL_STRINGIFY(x) RLL_STRINGIFY_EX(x)

#if defined(RLL_CONCAT_EX)
#  undef RLL_CONCAT_EX
#endif
#define RLL_CONCAT_EX(a,b) a##b

#if defined(RLL_CONCAT)
#  undef RLL_CONCAT
#endif
#define RLL_CONCAT(a,b) RLL_CONCAT_EX(a,b)

#if defined(RLL_CONCAT3_EX)
#  undef RLL_CONCAT3_EX
#endif
#define RLL_CONCAT3_EX(a,b,c) a##b##c

#if defined(RLL_CONCAT3)
#  undef RLL_CONCAT3
#endif
#define RLL_CONCAT3(a,b,c) RLL_CONCAT3_EX(a,b,c)

#if defined(RLL_VERSION_ENCODE)
#  undef RLL_VERSION_ENCODE
#endif
#define RLL_VERSION_ENCODE(major,minor,revision) (((major) * 1000000) + ((minor) * 1000) + (revision))

#if defined(RLL_VERSION_DECODE_MAJOR)
#  undef RLL_VERSION_DECODE_MAJOR
#endif
#define RLL_VERSION_DECODE_MAJOR(version) ((version) / 1000000)

#if defined(RLL_VERSION_DECODE_MINOR)
#  undef RLL_VERSION_DECODE_MINOR
#endif
#define RLL_VERSION_DECODE_MINOR(version) (((version) % 1000000) / 1000)

#if defined(RLL_VERSION_DECODE_REVISION)
#  undef RLL_VERSION_DECODE_REVISION
#endif
#define RLL_VERSION_DECODE_REVISION(version) ((version) % 1000)

#if defined(RLL_GNUC_VERSION)
#  undef RLL_GNUC_VERSION
#endif
#if defined(__GNUC__) && defined(__GNUC_PATCHLEVEL__)
#  define RLL_GNUC_VERSION RLL_VERSION_ENCODE(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#elif defined(__GNUC__)
#  define RLL_GNUC_VERSION RLL_VERSION_ENCODE(__GNUC__, __GNUC_MINOR__, 0)
#endif

#if defined(RLL_GNUC_VERSION_CHECK)
#  undef RLL_GNUC_VERSION_CHECK
#endif
#if defined(RLL_GNUC_VERSION)
#  define RLL_GNUC_VERSION_CHECK(major,minor,patch) (RLL_GNUC_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_GNUC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_MSVC_VERSION)
#  undef RLL_MSVC_VERSION
#endif
#if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 140000000) && !defined(__ICL)
#  define RLL_MSVC_VERSION RLL_VERSION_ENCODE(_MSC_FULL_VER / 10000000, (_MSC_FULL_VER % 10000000) / 100000, (_MSC_FULL_VER % 100000) / 100)
#elif defined(_MSC_FULL_VER) && !defined(__ICL)
#  define RLL_MSVC_VERSION RLL_VERSION_ENCODE(_MSC_FULL_VER / 1000000, (_MSC_FULL_VER % 1000000) / 10000, (_MSC_FULL_VER % 10000) / 10)
#elif defined(_MSC_VER) && !defined(__ICL)
#  define RLL_MSVC_VERSION RLL_VERSION_ENCODE(_MSC_VER / 100, _MSC_VER % 100, 0)
#endif

#if defined(RLL_MSVC_VERSION_CHECK)
#  undef RLL_MSVC_VERSION_CHECK
#endif
#if !defined(RLL_MSVC_VERSION)
#  define RLL_MSVC_VERSION_CHECK(major,minor,patch) (0)
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
#  define RLL_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_FULL_VER >= ((major * 10000000) + (minor * 100000) + (patch)))
#elif defined(_MSC_VER) && (_MSC_VER >= 1200)
#  define RLL_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_FULL_VER >= ((major * 1000000) + (minor * 10000) + (patch)))
#else
#  define RLL_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_VER >= ((major * 100) + (minor)))
#endif

#if defined(RLL_INTEL_VERSION)
#  undef RLL_INTEL_VERSION
#endif
#if defined(__INTEL_COMPILER) && defined(__INTEL_COMPILER_UPDATE) && !defined(__ICL)
#  define RLL_INTEL_VERSION RLL_VERSION_ENCODE(__INTEL_COMPILER / 100, __INTEL_COMPILER % 100, __INTEL_COMPILER_UPDATE)
#elif defined(__INTEL_COMPILER) && !defined(__ICL)
#  define RLL_INTEL_VERSION RLL_VERSION_ENCODE(__INTEL_COMPILER / 100, __INTEL_COMPILER % 100, 0)
#endif

#if defined(RLL_INTEL_VERSION_CHECK)
#  undef RLL_INTEL_VERSION_CHECK
#endif
#if defined(RLL_INTEL_VERSION)
#  define RLL_INTEL_VERSION_CHECK(major,minor,patch) (RLL_INTEL_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_INTEL_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_INTEL_CL_VERSION)
#  undef RLL_INTEL_CL_VERSION
#endif
#if defined(__INTEL_COMPILER) && defined(__INTEL_COMPILER_UPDATE) && defined(__ICL)
#  define RLL_INTEL_CL_VERSION RLL_VERSION_ENCODE(__INTEL_COMPILER, __INTEL_COMPILER_UPDATE, 0)
#endif

#if defined(RLL_INTEL_CL_VERSION_CHECK)
#  undef RLL_INTEL_CL_VERSION_CHECK
#endif
#if defined(RLL_INTEL_CL_VERSION)
#  define RLL_INTEL_CL_VERSION_CHECK(major,minor,patch) (RLL_INTEL_CL_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_INTEL_CL_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_PGI_VERSION)
#  undef RLL_PGI_VERSION
#endif
#if defined(__PGI) && defined(__PGIC__) && defined(__PGIC_MINOR__) && defined(__PGIC_PATCHLEVEL__)
#  define RLL_PGI_VERSION RLL_VERSION_ENCODE(__PGIC__, __PGIC_MINOR__, __PGIC_PATCHLEVEL__)
#endif

#if defined(RLL_PGI_VERSION_CHECK)
#  undef RLL_PGI_VERSION_CHECK
#endif
#if defined(RLL_PGI_VERSION)
#  define RLL_PGI_VERSION_CHECK(major,minor,patch) (RLL_PGI_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_PGI_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_SUNPRO_VERSION)
#  undef RLL_SUNPRO_VERSION
#endif
#if defined(__SUNPRO_C) && (__SUNPRO_C > 0x1000)
#  define RLL_SUNPRO_VERSION RLL_VERSION_ENCODE((((__SUNPRO_C >> 16) & 0xf) * 10) + ((__SUNPRO_C >> 12) & 0xf), (((__SUNPRO_C >> 8) & 0xf) * 10) + ((__SUNPRO_C >> 4) & 0xf), (__SUNPRO_C & 0xf) * 10)
#elif defined(__SUNPRO_C)
#  define RLL_SUNPRO_VERSION RLL_VERSION_ENCODE((__SUNPRO_C >> 8) & 0xf, (__SUNPRO_C >> 4) & 0xf, (__SUNPRO_C) & 0xf)
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC > 0x1000)
#  define RLL_SUNPRO_VERSION RLL_VERSION_ENCODE((((__SUNPRO_CC >> 16) & 0xf) * 10) + ((__SUNPRO_CC >> 12) & 0xf), (((__SUNPRO_CC >> 8) & 0xf) * 10) + ((__SUNPRO_CC >> 4) & 0xf), (__SUNPRO_CC & 0xf) * 10)
#elif defined(__SUNPRO_CC)
#  define RLL_SUNPRO_VERSION RLL_VERSION_ENCODE((__SUNPRO_CC >> 8) & 0xf, (__SUNPRO_CC >> 4) & 0xf, (__SUNPRO_CC) & 0xf)
#endif

#if defined(RLL_SUNPRO_VERSION_CHECK)
#  undef RLL_SUNPRO_VERSION_CHECK
#endif
#if defined(RLL_SUNPRO_VERSION)
#  define RLL_SUNPRO_VERSION_CHECK(major,minor,patch) (RLL_SUNPRO_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_SUNPRO_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_EMSCRIPTEN_VERSION)
#  undef RLL_EMSCRIPTEN_VERSION
#endif
#if defined(__EMSCRIPTEN__)
#  define RLL_EMSCRIPTEN_VERSION RLL_VERSION_ENCODE(__EMSCRIPTEN_major__, __EMSCRIPTEN_minor__, __EMSCRIPTEN_tiny__)
#endif

#if defined(RLL_EMSCRIPTEN_VERSION_CHECK)
#  undef RLL_EMSCRIPTEN_VERSION_CHECK
#endif
#if defined(RLL_EMSCRIPTEN_VERSION)
#  define RLL_EMSCRIPTEN_VERSION_CHECK(major,minor,patch) (RLL_EMSCRIPTEN_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_EMSCRIPTEN_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_ARM_VERSION)
#  undef RLL_ARM_VERSION
#endif
#if defined(__CC_ARM) && defined(__ARMCOMPILER_VERSION)
#  define RLL_ARM_VERSION RLL_VERSION_ENCODE(__ARMCOMPILER_VERSION / 1000000, (__ARMCOMPILER_VERSION % 1000000) / 10000, (__ARMCOMPILER_VERSION % 10000) / 100)
#elif defined(__CC_ARM) && defined(__ARMCC_VERSION)
#  define RLL_ARM_VERSION RLL_VERSION_ENCODE(__ARMCC_VERSION / 1000000, (__ARMCC_VERSION % 1000000) / 10000, (__ARMCC_VERSION % 10000) / 100)
#endif

#if defined(RLL_ARM_VERSION_CHECK)
#  undef RLL_ARM_VERSION_CHECK
#endif
#if defined(RLL_ARM_VERSION)
#  define RLL_ARM_VERSION_CHECK(major,minor,patch) (RLL_ARM_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_ARM_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_IBM_VERSION)
#  undef RLL_IBM_VERSION
#endif
#if defined(__ibmxl__)
#  define RLL_IBM_VERSION RLL_VERSION_ENCODE(__ibmxl_version__, __ibmxl_release__, __ibmxl_modification__)
#elif defined(__xlC__) && defined(__xlC_ver__)
#  define RLL_IBM_VERSION RLL_VERSION_ENCODE(__xlC__ >> 8, __xlC__ & 0xff, (__xlC_ver__ >> 8) & 0xff)
#elif defined(__xlC__)
#  define RLL_IBM_VERSION RLL_VERSION_ENCODE(__xlC__ >> 8, __xlC__ & 0xff, 0)
#endif

#if defined(RLL_IBM_VERSION_CHECK)
#  undef RLL_IBM_VERSION_CHECK
#endif
#if defined(RLL_IBM_VERSION)
#  define RLL_IBM_VERSION_CHECK(major,minor,patch) (RLL_IBM_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_IBM_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_TI_VERSION)
#  undef RLL_TI_VERSION
#endif
#if \
    defined(__TI_COMPILER_VERSION__) && \
    ( \
      defined(__TMS470__) || defined(__TI_ARM__) || \
      defined(__MSP430__) || \
      defined(__TMS320C2000__) \
    )
#  if (__TI_COMPILER_VERSION__ >= 16000000)
#    define RLL_TI_VERSION RLL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#  endif
#endif

#if defined(RLL_TI_VERSION_CHECK)
#  undef RLL_TI_VERSION_CHECK
#endif
#if defined(RLL_TI_VERSION)
#  define RLL_TI_VERSION_CHECK(major,minor,patch) (RLL_TI_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_TI_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_TI_CL2000_VERSION)
#  undef RLL_TI_CL2000_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__TMS320C2000__)
#  define RLL_TI_CL2000_VERSION RLL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(RLL_TI_CL2000_VERSION_CHECK)
#  undef RLL_TI_CL2000_VERSION_CHECK
#endif
#if defined(RLL_TI_CL2000_VERSION)
#  define RLL_TI_CL2000_VERSION_CHECK(major,minor,patch) (RLL_TI_CL2000_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_TI_CL2000_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_TI_CL430_VERSION)
#  undef RLL_TI_CL430_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__MSP430__)
#  define RLL_TI_CL430_VERSION RLL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(RLL_TI_CL430_VERSION_CHECK)
#  undef RLL_TI_CL430_VERSION_CHECK
#endif
#if defined(RLL_TI_CL430_VERSION)
#  define RLL_TI_CL430_VERSION_CHECK(major,minor,patch) (RLL_TI_CL430_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_TI_CL430_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_TI_ARMCL_VERSION)
#  undef RLL_TI_ARMCL_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && (defined(__TMS470__) || defined(__TI_ARM__))
#  define RLL_TI_ARMCL_VERSION RLL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(RLL_TI_ARMCL_VERSION_CHECK)
#  undef RLL_TI_ARMCL_VERSION_CHECK
#endif
#if defined(RLL_TI_ARMCL_VERSION)
#  define RLL_TI_ARMCL_VERSION_CHECK(major,minor,patch) (RLL_TI_ARMCL_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_TI_ARMCL_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_TI_CL6X_VERSION)
#  undef RLL_TI_CL6X_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__TMS320C6X__)
#  define RLL_TI_CL6X_VERSION RLL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(RLL_TI_CL6X_VERSION_CHECK)
#  undef RLL_TI_CL6X_VERSION_CHECK
#endif
#if defined(RLL_TI_CL6X_VERSION)
#  define RLL_TI_CL6X_VERSION_CHECK(major,minor,patch) (RLL_TI_CL6X_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_TI_CL6X_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_TI_CL7X_VERSION)
#  undef RLL_TI_CL7X_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__C7000__)
#  define RLL_TI_CL7X_VERSION RLL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(RLL_TI_CL7X_VERSION_CHECK)
#  undef RLL_TI_CL7X_VERSION_CHECK
#endif
#if defined(RLL_TI_CL7X_VERSION)
#  define RLL_TI_CL7X_VERSION_CHECK(major,minor,patch) (RLL_TI_CL7X_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_TI_CL7X_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_TI_CLPRU_VERSION)
#  undef RLL_TI_CLPRU_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__PRU__)
#  define RLL_TI_CLPRU_VERSION RLL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(RLL_TI_CLPRU_VERSION_CHECK)
#  undef RLL_TI_CLPRU_VERSION_CHECK
#endif
#if defined(RLL_TI_CLPRU_VERSION)
#  define RLL_TI_CLPRU_VERSION_CHECK(major,minor,patch) (RLL_TI_CLPRU_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_TI_CLPRU_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_CRAY_VERSION)
#  undef RLL_CRAY_VERSION
#endif
#if defined(_CRAYC)
#  if defined(_RELEASE_PATCHLEVEL)
#    define RLL_CRAY_VERSION RLL_VERSION_ENCODE(_RELEASE_MAJOR, _RELEASE_MINOR, _RELEASE_PATCHLEVEL)
#  else
#    define RLL_CRAY_VERSION RLL_VERSION_ENCODE(_RELEASE_MAJOR, _RELEASE_MINOR, 0)
#  endif
#endif

#if defined(RLL_CRAY_VERSION_CHECK)
#  undef RLL_CRAY_VERSION_CHECK
#endif
#if defined(RLL_CRAY_VERSION)
#  define RLL_CRAY_VERSION_CHECK(major,minor,patch) (RLL_CRAY_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_CRAY_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_IAR_VERSION)
#  undef RLL_IAR_VERSION
#endif
#if defined(__IAR_SYSTEMS_ICC__)
#  if __VER__ > 1000
#    define RLL_IAR_VERSION RLL_VERSION_ENCODE((__VER__ / 1000000), ((__VER__ / 1000) % 1000), (__VER__ % 1000))
#  else
#    define RLL_IAR_VERSION RLL_VERSION_ENCODE(__VER__ / 100, __VER__ % 100, 0)
#  endif
#endif

#if defined(RLL_IAR_VERSION_CHECK)
#  undef RLL_IAR_VERSION_CHECK
#endif
#if defined(RLL_IAR_VERSION)
#  define RLL_IAR_VERSION_CHECK(major,minor,patch) (RLL_IAR_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_IAR_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_TINYC_VERSION)
#  undef RLL_TINYC_VERSION
#endif
#if defined(__TINYC__)
#  define RLL_TINYC_VERSION RLL_VERSION_ENCODE(__TINYC__ / 1000, (__TINYC__ / 100) % 10, __TINYC__ % 100)
#endif

#if defined(RLL_TINYC_VERSION_CHECK)
#  undef RLL_TINYC_VERSION_CHECK
#endif
#if defined(RLL_TINYC_VERSION)
#  define RLL_TINYC_VERSION_CHECK(major,minor,patch) (RLL_TINYC_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_TINYC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_DMC_VERSION)
#  undef RLL_DMC_VERSION
#endif
#if defined(__DMC__)
#  define RLL_DMC_VERSION RLL_VERSION_ENCODE(__DMC__ >> 8, (__DMC__ >> 4) & 0xf, __DMC__ & 0xf)
#endif

#if defined(RLL_DMC_VERSION_CHECK)
#  undef RLL_DMC_VERSION_CHECK
#endif
#if defined(RLL_DMC_VERSION)
#  define RLL_DMC_VERSION_CHECK(major,minor,patch) (RLL_DMC_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_DMC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_COMPCERT_VERSION)
#  undef RLL_COMPCERT_VERSION
#endif
#if defined(__COMPCERT_VERSION__)
#  define RLL_COMPCERT_VERSION RLL_VERSION_ENCODE(__COMPCERT_VERSION__ / 10000, (__COMPCERT_VERSION__ / 100) % 100, __COMPCERT_VERSION__ % 100)
#endif

#if defined(RLL_COMPCERT_VERSION_CHECK)
#  undef RLL_COMPCERT_VERSION_CHECK
#endif
#if defined(RLL_COMPCERT_VERSION)
#  define RLL_COMPCERT_VERSION_CHECK(major,minor,patch) (RLL_COMPCERT_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_COMPCERT_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_PELLES_VERSION)
#  undef RLL_PELLES_VERSION
#endif
#if defined(__POCC__)
#  define RLL_PELLES_VERSION RLL_VERSION_ENCODE(__POCC__ / 100, __POCC__ % 100, 0)
#endif

#if defined(RLL_PELLES_VERSION_CHECK)
#  undef RLL_PELLES_VERSION_CHECK
#endif
#if defined(RLL_PELLES_VERSION)
#  define RLL_PELLES_VERSION_CHECK(major,minor,patch) (RLL_PELLES_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_PELLES_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_MCST_LCC_VERSION)
#  undef RLL_MCST_LCC_VERSION
#endif
#if defined(__LCC__) && defined(__LCC_MINOR__)
#  define RLL_MCST_LCC_VERSION RLL_VERSION_ENCODE(__LCC__ / 100, __LCC__ % 100, __LCC_MINOR__)
#endif

#if defined(RLL_MCST_LCC_VERSION_CHECK)
#  undef RLL_MCST_LCC_VERSION_CHECK
#endif
#if defined(RLL_MCST_LCC_VERSION)
#  define RLL_MCST_LCC_VERSION_CHECK(major,minor,patch) (RLL_MCST_LCC_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_MCST_LCC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_GCC_VERSION)
#  undef RLL_GCC_VERSION
#endif
#if \
  defined(RLL_GNUC_VERSION) && \
  !defined(__clang__) && \
  !defined(RLL_INTEL_VERSION) && \
  !defined(RLL_PGI_VERSION) && \
  !defined(RLL_ARM_VERSION) && \
  !defined(RLL_CRAY_VERSION) && \
  !defined(RLL_TI_VERSION) && \
  !defined(RLL_TI_ARMCL_VERSION) && \
  !defined(RLL_TI_CL430_VERSION) && \
  !defined(RLL_TI_CL2000_VERSION) && \
  !defined(RLL_TI_CL6X_VERSION) && \
  !defined(RLL_TI_CL7X_VERSION) && \
  !defined(RLL_TI_CLPRU_VERSION) && \
  !defined(__COMPCERT__) && \
  !defined(RLL_MCST_LCC_VERSION)
#  define RLL_GCC_VERSION RLL_GNUC_VERSION
#endif

#if defined(RLL_GCC_VERSION_CHECK)
#  undef RLL_GCC_VERSION_CHECK
#endif
#if defined(RLL_GCC_VERSION)
#  define RLL_GCC_VERSION_CHECK(major,minor,patch) (RLL_GCC_VERSION >= RLL_VERSION_ENCODE(major, minor, patch))
#else
#  define RLL_GCC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(RLL_HAS_ATTRIBUTE)
#  undef RLL_HAS_ATTRIBUTE
#endif
#if \
  defined(__has_attribute) && \
  ( \
    (!defined(RLL_IAR_VERSION) || RLL_IAR_VERSION_CHECK(8,5,9)) \
  )
#  define RLL_HAS_ATTRIBUTE(attribute) __has_attribute(attribute)
#else
#  define RLL_HAS_ATTRIBUTE(attribute) (0)
#endif

#if defined(RLL_GNUC_HAS_ATTRIBUTE)
#  undef RLL_GNUC_HAS_ATTRIBUTE
#endif
#if defined(__has_attribute)
#  define RLL_GNUC_HAS_ATTRIBUTE(attribute,major,minor,patch) RLL_HAS_ATTRIBUTE(attribute)
#else
#  define RLL_GNUC_HAS_ATTRIBUTE(attribute,major,minor,patch) RLL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_GCC_HAS_ATTRIBUTE)
#  undef RLL_GCC_HAS_ATTRIBUTE
#endif
#if defined(__has_attribute)
#  define RLL_GCC_HAS_ATTRIBUTE(attribute,major,minor,patch) RLL_HAS_ATTRIBUTE(attribute)
#else
#  define RLL_GCC_HAS_ATTRIBUTE(attribute,major,minor,patch) RLL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_HAS_CPP_ATTRIBUTE)
#  undef RLL_HAS_CPP_ATTRIBUTE
#endif
#if \
  defined(__has_cpp_attribute) && \
  defined(__cplusplus) && \
  (!defined(RLL_SUNPRO_VERSION) || RLL_SUNPRO_VERSION_CHECK(5,15,0))
#  define RLL_HAS_CPP_ATTRIBUTE(attribute) __has_cpp_attribute(attribute)
#else
#  define RLL_HAS_CPP_ATTRIBUTE(attribute) (0)
#endif

#if defined(RLL_HAS_CPP_ATTRIBUTE_NS)
#  undef RLL_HAS_CPP_ATTRIBUTE_NS
#endif
#if !defined(__cplusplus) || !defined(__has_cpp_attribute)
#  define RLL_HAS_CPP_ATTRIBUTE_NS(ns,attribute) (0)
#elif \
  !defined(RLL_PGI_VERSION) && \
  !defined(RLL_IAR_VERSION) && \
  (!defined(RLL_SUNPRO_VERSION) || RLL_SUNPRO_VERSION_CHECK(5,15,0)) && \
  (!defined(RLL_MSVC_VERSION) || RLL_MSVC_VERSION_CHECK(19,20,0))
#  define RLL_HAS_CPP_ATTRIBUTE_NS(ns,attribute) RLL_HAS_CPP_ATTRIBUTE(ns::attribute)
#else
#  define RLL_HAS_CPP_ATTRIBUTE_NS(ns,attribute) (0)
#endif

#if defined(RLL_GNUC_HAS_CPP_ATTRIBUTE)
#  undef RLL_GNUC_HAS_CPP_ATTRIBUTE
#endif
#if defined(__has_cpp_attribute) && defined(__cplusplus)
#  define RLL_GNUC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) __has_cpp_attribute(attribute)
#else
#  define RLL_GNUC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) RLL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_GCC_HAS_CPP_ATTRIBUTE)
#  undef RLL_GCC_HAS_CPP_ATTRIBUTE
#endif
#if defined(__has_cpp_attribute) && defined(__cplusplus)
#  define RLL_GCC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) __has_cpp_attribute(attribute)
#else
#  define RLL_GCC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) RLL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_HAS_BUILTIN)
#  undef RLL_HAS_BUILTIN
#endif
#if defined(__has_builtin)
#  define RLL_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
#  define RLL_HAS_BUILTIN(builtin) (0)
#endif

#if defined(RLL_GNUC_HAS_BUILTIN)
#  undef RLL_GNUC_HAS_BUILTIN
#endif
#if defined(__has_builtin)
#  define RLL_GNUC_HAS_BUILTIN(builtin,major,minor,patch) __has_builtin(builtin)
#else
#  define RLL_GNUC_HAS_BUILTIN(builtin,major,minor,patch) RLL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_GCC_HAS_BUILTIN)
#  undef RLL_GCC_HAS_BUILTIN
#endif
#if defined(__has_builtin)
#  define RLL_GCC_HAS_BUILTIN(builtin,major,minor,patch) __has_builtin(builtin)
#else
#  define RLL_GCC_HAS_BUILTIN(builtin,major,minor,patch) RLL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_HAS_FEATURE)
#  undef RLL_HAS_FEATURE
#endif
#if defined(__has_feature)
#  define RLL_HAS_FEATURE(feature) __has_feature(feature)
#else
#  define RLL_HAS_FEATURE(feature) (0)
#endif

#if defined(RLL_GNUC_HAS_FEATURE)
#  undef RLL_GNUC_HAS_FEATURE
#endif
#if defined(__has_feature)
#  define RLL_GNUC_HAS_FEATURE(feature,major,minor,patch) __has_feature(feature)
#else
#  define RLL_GNUC_HAS_FEATURE(feature,major,minor,patch) RLL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_GCC_HAS_FEATURE)
#  undef RLL_GCC_HAS_FEATURE
#endif
#if defined(__has_feature)
#  define RLL_GCC_HAS_FEATURE(feature,major,minor,patch) __has_feature(feature)
#else
#  define RLL_GCC_HAS_FEATURE(feature,major,minor,patch) RLL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_HAS_EXTENSION)
#  undef RLL_HAS_EXTENSION
#endif
#if defined(__has_extension)
#  define RLL_HAS_EXTENSION(extension) __has_extension(extension)
#else
#  define RLL_HAS_EXTENSION(extension) (0)
#endif

#if defined(RLL_GNUC_HAS_EXTENSION)
#  undef RLL_GNUC_HAS_EXTENSION
#endif
#if defined(__has_extension)
#  define RLL_GNUC_HAS_EXTENSION(extension,major,minor,patch) __has_extension(extension)
#else
#  define RLL_GNUC_HAS_EXTENSION(extension,major,minor,patch) RLL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_GCC_HAS_EXTENSION)
#  undef RLL_GCC_HAS_EXTENSION
#endif
#if defined(__has_extension)
#  define RLL_GCC_HAS_EXTENSION(extension,major,minor,patch) __has_extension(extension)
#else
#  define RLL_GCC_HAS_EXTENSION(extension,major,minor,patch) RLL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_HAS_DECLSPEC_ATTRIBUTE)
#  undef RLL_HAS_DECLSPEC_ATTRIBUTE
#endif
#if defined(__has_declspec_attribute)
#  define RLL_HAS_DECLSPEC_ATTRIBUTE(attribute) __has_declspec_attribute(attribute)
#else
#  define RLL_HAS_DECLSPEC_ATTRIBUTE(attribute) (0)
#endif

#if defined(RLL_GNUC_HAS_DECLSPEC_ATTRIBUTE)
#  undef RLL_GNUC_HAS_DECLSPEC_ATTRIBUTE
#endif
#if defined(__has_declspec_attribute)
#  define RLL_GNUC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) __has_declspec_attribute(attribute)
#else
#  define RLL_GNUC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) RLL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_GCC_HAS_DECLSPEC_ATTRIBUTE)
#  undef RLL_GCC_HAS_DECLSPEC_ATTRIBUTE
#endif
#if defined(__has_declspec_attribute)
#  define RLL_GCC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) __has_declspec_attribute(attribute)
#else
#  define RLL_GCC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) RLL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_HAS_WARNING)
#  undef RLL_HAS_WARNING
#endif
#if defined(__has_warning)
#  define RLL_HAS_WARNING(warning) __has_warning(warning)
#else
#  define RLL_HAS_WARNING(warning) (0)
#endif

#if defined(RLL_GNUC_HAS_WARNING)
#  undef RLL_GNUC_HAS_WARNING
#endif
#if defined(__has_warning)
#  define RLL_GNUC_HAS_WARNING(warning,major,minor,patch) __has_warning(warning)
#else
#  define RLL_GNUC_HAS_WARNING(warning,major,minor,patch) RLL_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_GCC_HAS_WARNING)
#  undef RLL_GCC_HAS_WARNING
#endif
#if defined(__has_warning)
#  define RLL_GCC_HAS_WARNING(warning,major,minor,patch) __has_warning(warning)
#else
#  define RLL_GCC_HAS_WARNING(warning,major,minor,patch) RLL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if \
  (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || \
  defined(__clang__) || \
  RLL_GCC_VERSION_CHECK(3,0,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_IAR_VERSION_CHECK(8,0,0) || \
  RLL_PGI_VERSION_CHECK(18,4,0) || \
  RLL_ARM_VERSION_CHECK(4,1,0) || \
  RLL_TI_VERSION_CHECK(15,12,0) || \
  RLL_TI_ARMCL_VERSION_CHECK(4,7,0) || \
  RLL_TI_CL430_VERSION_CHECK(2,0,1) || \
  RLL_TI_CL2000_VERSION_CHECK(6,1,0) || \
  RLL_TI_CL6X_VERSION_CHECK(7,0,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  RLL_CRAY_VERSION_CHECK(5,0,0) || \
  RLL_TINYC_VERSION_CHECK(0,9,17) || \
  RLL_SUNPRO_VERSION_CHECK(8,0,0) || \
  (RLL_IBM_VERSION_CHECK(10,1,0) && defined(__C99_PRAGMA_OPERATOR))
#  define RLL_PRAGMA(value) _Pragma(#value)
#elif RLL_MSVC_VERSION_CHECK(15,0,0)
#  define RLL_PRAGMA(value) __pragma(value)
#else
#  define RLL_PRAGMA(value)
#endif

#if defined(RLL_DIAGNOSTIC_PUSH)
#  undef RLL_DIAGNOSTIC_PUSH
#endif
#if defined(RLL_DIAGNOSTIC_POP)
#  undef RLL_DIAGNOSTIC_POP
#endif
#if defined(__clang__)
#  define RLL_DIAGNOSTIC_PUSH _Pragma("clang diagnostic push")
#  define RLL_DIAGNOSTIC_POP _Pragma("clang diagnostic pop")
#elif RLL_INTEL_VERSION_CHECK(13,0,0)
#  define RLL_DIAGNOSTIC_PUSH _Pragma("warning(push)")
#  define RLL_DIAGNOSTIC_POP _Pragma("warning(pop)")
#elif RLL_GCC_VERSION_CHECK(4,6,0)
#  define RLL_DIAGNOSTIC_PUSH _Pragma("GCC diagnostic push")
#  define RLL_DIAGNOSTIC_POP _Pragma("GCC diagnostic pop")
#elif \
  RLL_MSVC_VERSION_CHECK(15,0,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_DIAGNOSTIC_PUSH __pragma(warning(push))
#  define RLL_DIAGNOSTIC_POP __pragma(warning(pop))
#elif RLL_ARM_VERSION_CHECK(5,6,0)
#  define RLL_DIAGNOSTIC_PUSH _Pragma("push")
#  define RLL_DIAGNOSTIC_POP _Pragma("pop")
#elif \
    RLL_TI_VERSION_CHECK(15,12,0) || \
    RLL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
    RLL_TI_CL430_VERSION_CHECK(4,4,0) || \
    RLL_TI_CL6X_VERSION_CHECK(8,1,0) || \
    RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
    RLL_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define RLL_DIAGNOSTIC_PUSH _Pragma("diag_push")
#  define RLL_DIAGNOSTIC_POP _Pragma("diag_pop")
#elif RLL_PELLES_VERSION_CHECK(2,90,0)
#  define RLL_DIAGNOSTIC_PUSH _Pragma("warning(push)")
#  define RLL_DIAGNOSTIC_POP _Pragma("warning(pop)")
#else
#  define RLL_DIAGNOSTIC_PUSH
#  define RLL_DIAGNOSTIC_POP
#endif

/* RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_ is for
   RLL INTERNAL USE ONLY.  API subject to change without notice. */
#if defined(RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_)
#  undef RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_
#endif
#if defined(__cplusplus)
#  if RLL_HAS_WARNING("-Wc++98-compat")
#    if RLL_HAS_WARNING("-Wc++17-extensions")
#      if RLL_HAS_WARNING("-Wc++1z-extensions")
#        define RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(xpr) \
           RLL_DIAGNOSTIC_PUSH \
           _Pragma("clang diagnostic ignored \"-Wc++98-compat\"") \
           _Pragma("clang diagnostic ignored \"-Wc++17-extensions\"") \
           _Pragma("clang diagnostic ignored \"-Wc++1z-extensions\"") \
           xpr \
           RLL_DIAGNOSTIC_POP
#      else
#        define RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(xpr) \
           RLL_DIAGNOSTIC_PUSH \
           _Pragma("clang diagnostic ignored \"-Wc++98-compat\"") \
           _Pragma("clang diagnostic ignored \"-Wc++17-extensions\"") \
           xpr \
           RLL_DIAGNOSTIC_POP
#      endif
#    else
#      define RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(xpr) \
         RLL_DIAGNOSTIC_PUSH \
         _Pragma("clang diagnostic ignored \"-Wc++98-compat\"") \
         xpr \
         RLL_DIAGNOSTIC_POP
#    endif
#  endif
#endif
#if !defined(RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_)
#  define RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(x) x
#endif

#if defined(RLL_CONST_CAST)
#  undef RLL_CONST_CAST
#endif
#if defined(__cplusplus)
#  define RLL_CONST_CAST(T, expr) (const_cast<T>(expr))
#elif \
  RLL_HAS_WARNING("-Wcast-qual") || \
  RLL_GCC_VERSION_CHECK(4,6,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0)
#  define RLL_CONST_CAST(T, expr) (__extension__ ({ \
      RLL_DIAGNOSTIC_PUSH \
      RLL_DIAGNOSTIC_DISABLE_CAST_QUAL \
      ((T) (expr)); \
      RLL_DIAGNOSTIC_POP \
    }))
#else
#  define RLL_CONST_CAST(T, expr) ((T) (expr))
#endif

#if defined(RLL_REINTERPRET_CAST)
#  undef RLL_REINTERPRET_CAST
#endif
#if defined(__cplusplus)
#  define RLL_REINTERPRET_CAST(T, expr) (reinterpret_cast<T>(expr))
#else
#  define RLL_REINTERPRET_CAST(T, expr) ((T) (expr))
#endif

#if defined(RLL_STATIC_CAST)
#  undef RLL_STATIC_CAST
#endif
#if defined(__cplusplus)
#  define RLL_STATIC_CAST(T, expr) (static_cast<T>(expr))
#else
#  define RLL_STATIC_CAST(T, expr) ((T) (expr))
#endif

#if defined(RLL_CPP_CAST)
#  undef RLL_CPP_CAST
#endif
#if defined(__cplusplus)
#  if RLL_HAS_WARNING("-Wold-style-cast")
#    define RLL_CPP_CAST(T, expr) \
       RLL_DIAGNOSTIC_PUSH \
       _Pragma("clang diagnostic ignored \"-Wold-style-cast\"") \
       ((T) (expr)) \
       RLL_DIAGNOSTIC_POP
#  elif RLL_IAR_VERSION_CHECK(8,3,0)
#    define RLL_CPP_CAST(T, expr) \
       RLL_DIAGNOSTIC_PUSH \
       _Pragma("diag_suppress=Pe137") \
       RLL_DIAGNOSTIC_POP
#  else
#    define RLL_CPP_CAST(T, expr) ((T) (expr))
#  endif
#else
#  define RLL_CPP_CAST(T, expr) (expr)
#endif

#if defined(RLL_DIAGNOSTIC_DISABLE_DEPRECATED)
#  undef RLL_DIAGNOSTIC_DISABLE_DEPRECATED
#endif
#if RLL_HAS_WARNING("-Wdeprecated-declarations")
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#elif RLL_INTEL_VERSION_CHECK(13,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("warning(disable:1478 1786)")
#elif RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED __pragma(warning(disable:1478 1786))
#elif RLL_PGI_VERSION_CHECK(20,7,0)
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress 1215,1216,1444,1445")
#elif RLL_PGI_VERSION_CHECK(17,10,0)
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress 1215,1444")
#elif RLL_GCC_VERSION_CHECK(4,3,0)
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#elif RLL_MSVC_VERSION_CHECK(15,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED __pragma(warning(disable:4996))
#elif RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress 1215,1444")
#elif \
    RLL_TI_VERSION_CHECK(15,12,0) || \
    (RLL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
    RLL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
    (RLL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
    RLL_TI_CL2000_VERSION_CHECK(6,4,0) || \
    (RLL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
    RLL_TI_CL430_VERSION_CHECK(4,3,0) || \
    (RLL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
    RLL_TI_CL6X_VERSION_CHECK(7,5,0) || \
    RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
    RLL_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress 1291,1718")
#elif RLL_SUNPRO_VERSION_CHECK(5,13,0) && !defined(__cplusplus)
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("error_messages(off,E_DEPRECATED_ATT,E_DEPRECATED_ATT_MESS)")
#elif RLL_SUNPRO_VERSION_CHECK(5,13,0) && defined(__cplusplus)
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("error_messages(off,symdeprecated,symdeprecated2)")
#elif RLL_IAR_VERSION_CHECK(8,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress=Pe1444,Pe1215")
#elif RLL_PELLES_VERSION_CHECK(2,90,0)
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("warn(disable:2241)")
#else
#  define RLL_DIAGNOSTIC_DISABLE_DEPRECATED
#endif

#if defined(RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS)
#  undef RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS
#endif
#if RLL_HAS_WARNING("-Wunknown-pragmas")
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("clang diagnostic ignored \"-Wunknown-pragmas\"")
#elif RLL_INTEL_VERSION_CHECK(13,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("warning(disable:161)")
#elif RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS __pragma(warning(disable:161))
#elif RLL_PGI_VERSION_CHECK(17,10,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 1675")
#elif RLL_GCC_VERSION_CHECK(4,3,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("GCC diagnostic ignored \"-Wunknown-pragmas\"")
#elif RLL_MSVC_VERSION_CHECK(15,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS __pragma(warning(disable:4068))
#elif \
    RLL_TI_VERSION_CHECK(16,9,0) || \
    RLL_TI_CL6X_VERSION_CHECK(8,0,0) || \
    RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
    RLL_TI_CLPRU_VERSION_CHECK(2,3,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 163")
#elif RLL_TI_CL6X_VERSION_CHECK(8,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 163")
#elif RLL_IAR_VERSION_CHECK(8,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress=Pe161")
#elif RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 161")
#else
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS
#endif

#if defined(RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES)
#  undef RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES
#endif
#if RLL_HAS_WARNING("-Wunknown-attributes")
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("clang diagnostic ignored \"-Wunknown-attributes\"")
#elif RLL_GCC_VERSION_CHECK(4,6,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#elif RLL_INTEL_VERSION_CHECK(17,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("warning(disable:1292)")
#elif RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES __pragma(warning(disable:1292))
#elif RLL_MSVC_VERSION_CHECK(19,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES __pragma(warning(disable:5030))
#elif RLL_PGI_VERSION_CHECK(20,7,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress 1097,1098")
#elif RLL_PGI_VERSION_CHECK(17,10,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress 1097")
#elif RLL_SUNPRO_VERSION_CHECK(5,14,0) && defined(__cplusplus)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("error_messages(off,attrskipunsup)")
#elif \
    RLL_TI_VERSION_CHECK(18,1,0) || \
    RLL_TI_CL6X_VERSION_CHECK(8,3,0) || \
    RLL_TI_CL7X_VERSION_CHECK(1,2,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress 1173")
#elif RLL_IAR_VERSION_CHECK(8,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress=Pe1097")
#elif RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress 1097")
#else
#  define RLL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES
#endif

#if defined(RLL_DIAGNOSTIC_DISABLE_CAST_QUAL)
#  undef RLL_DIAGNOSTIC_DISABLE_CAST_QUAL
#endif
#if RLL_HAS_WARNING("-Wcast-qual")
#  define RLL_DIAGNOSTIC_DISABLE_CAST_QUAL _Pragma("clang diagnostic ignored \"-Wcast-qual\"")
#elif RLL_INTEL_VERSION_CHECK(13,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_CAST_QUAL _Pragma("warning(disable:2203 2331)")
#elif RLL_GCC_VERSION_CHECK(3,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_CAST_QUAL _Pragma("GCC diagnostic ignored \"-Wcast-qual\"")
#else
#  define RLL_DIAGNOSTIC_DISABLE_CAST_QUAL
#endif

#if defined(RLL_DIAGNOSTIC_DISABLE_UNUSED_FUNCTION)
#  undef RLL_DIAGNOSTIC_DISABLE_UNUSED_FUNCTION
#endif
#if RLL_HAS_WARNING("-Wunused-function")
#  define RLL_DIAGNOSTIC_DISABLE_UNUSED_FUNCTION _Pragma("clang diagnostic ignored \"-Wunused-function\"")
#elif RLL_GCC_VERSION_CHECK(3,4,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNUSED_FUNCTION _Pragma("GCC diagnostic ignored \"-Wunused-function\"")
#elif RLL_MSVC_VERSION_CHECK(1,0,0)
#  define RLL_DIAGNOSTIC_DISABLE_UNUSED_FUNCTION __pragma(warning(disable:4505))
#elif RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_DIAGNOSTIC_DISABLE_UNUSED_FUNCTION _Pragma("diag_suppress 3142")
#else
#  define RLL_DIAGNOSTIC_DISABLE_UNUSED_FUNCTION
#endif

#if defined(RLL_DEPRECATED)
#  undef RLL_DEPRECATED
#endif
#if defined(RLL_DEPRECATED_FOR)
#  undef RLL_DEPRECATED_FOR
#endif
#if \
  RLL_MSVC_VERSION_CHECK(14,0,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_DEPRECATED(since) __declspec(deprecated("Since " # since))
#  define RLL_DEPRECATED_FOR(since, replacement) __declspec(deprecated("Since " #since "; use " #replacement))
#elif \
  (RLL_HAS_EXTENSION(attribute_deprecated_with_message) && !defined(RLL_IAR_VERSION)) || \
  RLL_GCC_VERSION_CHECK(4,5,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_ARM_VERSION_CHECK(5,6,0) || \
  RLL_SUNPRO_VERSION_CHECK(5,13,0) || \
  RLL_PGI_VERSION_CHECK(17,10,0) || \
  RLL_TI_VERSION_CHECK(18,1,0) || \
  RLL_TI_ARMCL_VERSION_CHECK(18,1,0) || \
  RLL_TI_CL6X_VERSION_CHECK(8,3,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,3,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_DEPRECATED(since) __attribute__((__deprecated__("Since " #since)))
#  define RLL_DEPRECATED_FOR(since, replacement) __attribute__((__deprecated__("Since " #since "; use " #replacement)))
#elif defined(__cplusplus) && (__cplusplus >= 201402L)
#  define RLL_DEPRECATED(since) RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[deprecated("Since " #since)]])
#  define RLL_DEPRECATED_FOR(since, replacement) RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[deprecated("Since " #since "; use " #replacement)]])
#elif \
  RLL_HAS_ATTRIBUTE(deprecated) || \
  RLL_GCC_VERSION_CHECK(3,1,0) || \
  RLL_ARM_VERSION_CHECK(4,1,0) || \
  RLL_TI_VERSION_CHECK(15,12,0) || \
  (RLL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (RLL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (RLL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (RLL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10) || \
  RLL_IAR_VERSION_CHECK(8,10,0)
#  define RLL_DEPRECATED(since) __attribute__((__deprecated__))
#  define RLL_DEPRECATED_FOR(since, replacement) __attribute__((__deprecated__))
#elif \
  RLL_MSVC_VERSION_CHECK(13,10,0) || \
  RLL_PELLES_VERSION_CHECK(6,50,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_DEPRECATED(since) __declspec(deprecated)
#  define RLL_DEPRECATED_FOR(since, replacement) __declspec(deprecated)
#elif RLL_IAR_VERSION_CHECK(8,0,0)
#  define RLL_DEPRECATED(since) _Pragma("deprecated")
#  define RLL_DEPRECATED_FOR(since, replacement) _Pragma("deprecated")
#else
#  define RLL_DEPRECATED(since)
#  define RLL_DEPRECATED_FOR(since, replacement)
#endif

#if defined(RLL_UNAVAILABLE)
#  undef RLL_UNAVAILABLE
#endif
#if \
  RLL_HAS_ATTRIBUTE(warning) || \
  RLL_GCC_VERSION_CHECK(4,3,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_UNAVAILABLE(available_since) __attribute__((__warning__("Not available until " #available_since)))
#else
#  define RLL_UNAVAILABLE(available_since)
#endif

#if defined(RLL_WARN_UNUSED_RESULT)
#  undef RLL_WARN_UNUSED_RESULT
#endif
#if defined(RLL_WARN_UNUSED_RESULT_MSG)
#  undef RLL_WARN_UNUSED_RESULT_MSG
#endif
#if \
  RLL_HAS_ATTRIBUTE(warn_unused_result) || \
  RLL_GCC_VERSION_CHECK(3,4,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_TI_VERSION_CHECK(15,12,0) || \
  (RLL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (RLL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (RLL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (RLL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  (RLL_SUNPRO_VERSION_CHECK(5,15,0) && defined(__cplusplus)) || \
  RLL_PGI_VERSION_CHECK(17,10,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#  define RLL_WARN_UNUSED_RESULT_MSG(msg) __attribute__((__warn_unused_result__))
#elif (RLL_HAS_CPP_ATTRIBUTE(nodiscard) >= 201907L)
#  define RLL_WARN_UNUSED_RESULT RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard]])
#  define RLL_WARN_UNUSED_RESULT_MSG(msg) RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard(msg)]])
#elif RLL_HAS_CPP_ATTRIBUTE(nodiscard)
#  define RLL_WARN_UNUSED_RESULT RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard]])
#  define RLL_WARN_UNUSED_RESULT_MSG(msg) RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard]])
#elif defined(_Check_return_) /* SAL */
#  define RLL_WARN_UNUSED_RESULT _Check_return_
#  define RLL_WARN_UNUSED_RESULT_MSG(msg) _Check_return_
#else
#  define RLL_WARN_UNUSED_RESULT
#  define RLL_WARN_UNUSED_RESULT_MSG(msg)
#endif

#if defined(RLL_SENTINEL)
#  undef RLL_SENTINEL
#endif
#if \
  RLL_HAS_ATTRIBUTE(sentinel) || \
  RLL_GCC_VERSION_CHECK(4,0,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_ARM_VERSION_CHECK(5,4,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_SENTINEL(position) __attribute__((__sentinel__(position)))
#else
#  define RLL_SENTINEL(position)
#endif

#if defined(RLL_NO_RETURN)
#  undef RLL_NO_RETURN
#endif
#if RLL_IAR_VERSION_CHECK(8,0,0)
#  define RLL_NO_RETURN __noreturn
#elif \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_NO_RETURN __attribute__((__noreturn__))
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#  define RLL_NO_RETURN _Noreturn
#elif defined(__cplusplus) && (__cplusplus >= 201103L)
#  define RLL_NO_RETURN RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[noreturn]])
#elif \
  RLL_HAS_ATTRIBUTE(noreturn) || \
  RLL_GCC_VERSION_CHECK(3,2,0) || \
  RLL_SUNPRO_VERSION_CHECK(5,11,0) || \
  RLL_ARM_VERSION_CHECK(4,1,0) || \
  RLL_IBM_VERSION_CHECK(10,1,0) || \
  RLL_TI_VERSION_CHECK(15,12,0) || \
  (RLL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (RLL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (RLL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (RLL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  RLL_IAR_VERSION_CHECK(8,10,0)
#  define RLL_NO_RETURN __attribute__((__noreturn__))
#elif RLL_SUNPRO_VERSION_CHECK(5,10,0)
#  define RLL_NO_RETURN _Pragma("does_not_return")
#elif \
  RLL_MSVC_VERSION_CHECK(13,10,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_NO_RETURN __declspec(noreturn)
#elif RLL_TI_CL6X_VERSION_CHECK(6,0,0) && defined(__cplusplus)
#  define RLL_NO_RETURN _Pragma("FUNC_NEVER_RETURNS;")
#elif RLL_COMPCERT_VERSION_CHECK(3,2,0)
#  define RLL_NO_RETURN __attribute((noreturn))
#elif RLL_PELLES_VERSION_CHECK(9,0,0)
#  define RLL_NO_RETURN __declspec(noreturn)
#else
#  define RLL_NO_RETURN
#endif

#if defined(RLL_NO_ESCAPE)
#  undef RLL_NO_ESCAPE
#endif
#if RLL_HAS_ATTRIBUTE(noescape)
#  define RLL_NO_ESCAPE __attribute__((__noescape__))
#else
#  define RLL_NO_ESCAPE
#endif

#if defined(RLL_UNREACHABLE)
#  undef RLL_UNREACHABLE
#endif
#if defined(RLL_UNREACHABLE_RETURN)
#  undef RLL_UNREACHABLE_RETURN
#endif
#if defined(RLL_ASSUME)
#  undef RLL_ASSUME
#endif
#if \
  RLL_MSVC_VERSION_CHECK(13,10,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_ASSUME(expr) __assume(expr)
#elif RLL_HAS_BUILTIN(__builtin_assume)
#  define RLL_ASSUME(expr) __builtin_assume(expr)
#elif \
    RLL_TI_CL2000_VERSION_CHECK(6,2,0) || \
    RLL_TI_CL6X_VERSION_CHECK(4,0,0)
#  if defined(__cplusplus)
#    define RLL_ASSUME(expr) std::_nassert(expr)
#  else
#    define RLL_ASSUME(expr) _nassert(expr)
#  endif
#endif
#if \
  (RLL_HAS_BUILTIN(__builtin_unreachable) && (!defined(RLL_ARM_VERSION))) || \
  RLL_GCC_VERSION_CHECK(4,5,0) || \
  RLL_PGI_VERSION_CHECK(18,10,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_IBM_VERSION_CHECK(13,1,5) || \
  RLL_CRAY_VERSION_CHECK(10,0,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_UNREACHABLE() __builtin_unreachable()
#elif defined(RLL_ASSUME)
#  define RLL_UNREACHABLE() RLL_ASSUME(0)
#endif
#if !defined(RLL_ASSUME)
#  if defined(RLL_UNREACHABLE)
#    define RLL_ASSUME(expr) RLL_STATIC_CAST(void, ((expr) ? 1 : (RLL_UNREACHABLE(), 1)))
#  else
#    define RLL_ASSUME(expr) RLL_STATIC_CAST(void, expr)
#  endif
#endif
#if defined(RLL_UNREACHABLE)
#  if  \
      RLL_TI_CL2000_VERSION_CHECK(6,2,0) || \
      RLL_TI_CL6X_VERSION_CHECK(4,0,0)
#    define RLL_UNREACHABLE_RETURN(value) return (RLL_STATIC_CAST(void, RLL_ASSUME(0)), (value))
#  else
#    define RLL_UNREACHABLE_RETURN(value) RLL_UNREACHABLE()
#  endif
#else
#  define RLL_UNREACHABLE_RETURN(value) return (value)
#endif
#if !defined(RLL_UNREACHABLE)
#  define RLL_UNREACHABLE() RLL_ASSUME(0)
#endif

RLL_DIAGNOSTIC_PUSH
#if RLL_HAS_WARNING("-Wpedantic")
#  pragma clang diagnostic ignored "-Wpedantic"
#endif
#if RLL_HAS_WARNING("-Wc++98-compat-pedantic") && defined(__cplusplus)
#  pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#endif
#if RLL_GCC_HAS_WARNING("-Wvariadic-macros",4,0,0)
#  if defined(__clang__)
#    pragma clang diagnostic ignored "-Wvariadic-macros"
#  elif defined(RLL_GCC_VERSION)
#    pragma GCC diagnostic ignored "-Wvariadic-macros"
#  endif
#endif
#if defined(RLL_NON_NULL)
#  undef RLL_NON_NULL
#endif
#if \
  RLL_HAS_ATTRIBUTE(nonnull) || \
  RLL_GCC_VERSION_CHECK(3,3,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_ARM_VERSION_CHECK(4,1,0)
#  define RLL_NON_NULL(...) __attribute__((__nonnull__(__VA_ARGS__)))
#else
#  define RLL_NON_NULL(...)
#endif
RLL_DIAGNOSTIC_POP

#if defined(RLL_PRINTF_FORMAT)
#  undef RLL_PRINTF_FORMAT
#endif
#if defined(__MINGW32__) && RLL_GCC_HAS_ATTRIBUTE(format,4,4,0) && !defined(__USE_MINGW_ANSI_STDIO)
#  define RLL_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(ms_printf, string_idx, first_to_check)))
#elif defined(__MINGW32__) && RLL_GCC_HAS_ATTRIBUTE(format,4,4,0) && defined(__USE_MINGW_ANSI_STDIO)
#  define RLL_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(gnu_printf, string_idx, first_to_check)))
#elif \
  RLL_HAS_ATTRIBUTE(format) || \
  RLL_GCC_VERSION_CHECK(3,1,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_ARM_VERSION_CHECK(5,6,0) || \
  RLL_IBM_VERSION_CHECK(10,1,0) || \
  RLL_TI_VERSION_CHECK(15,12,0) || \
  (RLL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (RLL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (RLL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (RLL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(__printf__, string_idx, first_to_check)))
#elif RLL_PELLES_VERSION_CHECK(6,0,0)
#  define RLL_PRINTF_FORMAT(string_idx,first_to_check) __declspec(vaformat(printf,string_idx,first_to_check))
#else
#  define RLL_PRINTF_FORMAT(string_idx,first_to_check)
#endif

#if defined(RLL_CONSTEXPR)
#  undef RLL_CONSTEXPR
#endif
#if defined(__cplusplus)
#  if __cplusplus >= 201103L
#    define RLL_CONSTEXPR RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(constexpr)
#  endif
#endif
#if !defined(RLL_CONSTEXPR)
#  define RLL_CONSTEXPR
#endif

#if defined(RLL_PREDICT)
#  undef RLL_PREDICT
#endif
#if defined(RLL_LIKELY)
#  undef RLL_LIKELY
#endif
#if defined(RLL_UNLIKELY)
#  undef RLL_UNLIKELY
#endif
#if defined(RLL_UNPREDICTABLE)
#  undef RLL_UNPREDICTABLE
#endif
#if RLL_HAS_BUILTIN(__builtin_unpredictable)
#  define RLL_UNPREDICTABLE(expr) __builtin_unpredictable((expr))
#endif
#if \
  (RLL_HAS_BUILTIN(__builtin_expect_with_probability) && !defined(RLL_PGI_VERSION)) || \
  RLL_GCC_VERSION_CHECK(9,0,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_PREDICT(expr, value, probability) __builtin_expect_with_probability(  (expr), (value), (probability))
#  define RLL_PREDICT_TRUE(expr, probability)   __builtin_expect_with_probability(!!(expr),    1   , (probability))
#  define RLL_PREDICT_FALSE(expr, probability)  __builtin_expect_with_probability(!!(expr),    0   , (probability))
#  define RLL_LIKELY(expr)                      __builtin_expect                 (!!(expr),    1                  )
#  define RLL_UNLIKELY(expr)                    __builtin_expect                 (!!(expr),    0                  )
#elif \
  (RLL_HAS_BUILTIN(__builtin_expect) && !defined(RLL_INTEL_CL_VERSION)) || \
  RLL_GCC_VERSION_CHECK(3,0,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  (RLL_SUNPRO_VERSION_CHECK(5,15,0) && defined(__cplusplus)) || \
  RLL_ARM_VERSION_CHECK(4,1,0) || \
  RLL_IBM_VERSION_CHECK(10,1,0) || \
  RLL_TI_VERSION_CHECK(15,12,0) || \
  RLL_TI_ARMCL_VERSION_CHECK(4,7,0) || \
  RLL_TI_CL430_VERSION_CHECK(3,1,0) || \
  RLL_TI_CL2000_VERSION_CHECK(6,1,0) || \
  RLL_TI_CL6X_VERSION_CHECK(6,1,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  RLL_TINYC_VERSION_CHECK(0,9,27) || \
  RLL_CRAY_VERSION_CHECK(8,1,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_PREDICT(expr, expected, probability) \
     (((probability) >= 0.9) ? __builtin_expect((expr), (expected)) : (RLL_STATIC_CAST(void, expected), (expr)))
#  define RLL_PREDICT_TRUE(expr, probability) \
     (__extension__ ({ \
       double RLL_probability_ = (probability); \
       ((RLL_probability_ >= 0.9) ? __builtin_expect(!!(expr), 1) : ((RLL_probability_ <= 0.1) ? __builtin_expect(!!(expr), 0) : !!(expr))); \
     }))
#  define RLL_PREDICT_FALSE(expr, probability) \
     (__extension__ ({ \
       double RLL_probability_ = (probability); \
       ((RLL_probability_ >= 0.9) ? __builtin_expect(!!(expr), 0) : ((RLL_probability_ <= 0.1) ? __builtin_expect(!!(expr), 1) : !!(expr))); \
     }))
#  define RLL_LIKELY(expr)   __builtin_expect(!!(expr), 1)
#  define RLL_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#else
#  define RLL_PREDICT(expr, expected, probability) (RLL_STATIC_CAST(void, expected), (expr))
#  define RLL_PREDICT_TRUE(expr, probability) (!!(expr))
#  define RLL_PREDICT_FALSE(expr, probability) (!!(expr))
#  define RLL_LIKELY(expr) (!!(expr))
#  define RLL_UNLIKELY(expr) (!!(expr))
#endif
#if !defined(RLL_UNPREDICTABLE)
#  define RLL_UNPREDICTABLE(expr) RLL_PREDICT(expr, 1, 0.5)
#endif

#if defined(RLL_MALLOC)
#  undef RLL_MALLOC
#endif
#if \
  RLL_HAS_ATTRIBUTE(malloc) || \
  RLL_GCC_VERSION_CHECK(3,1,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_SUNPRO_VERSION_CHECK(5,11,0) || \
  RLL_ARM_VERSION_CHECK(4,1,0) || \
  RLL_IBM_VERSION_CHECK(12,1,0) || \
  RLL_TI_VERSION_CHECK(15,12,0) || \
  (RLL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (RLL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (RLL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (RLL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_MALLOC __attribute__((__malloc__))
#elif RLL_SUNPRO_VERSION_CHECK(5,10,0)
#  define RLL_MALLOC _Pragma("returns_new_memory")
#elif \
  RLL_MSVC_VERSION_CHECK(14,0,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_MALLOC __declspec(restrict)
#else
#  define RLL_MALLOC
#endif

#if defined(RLL_PURE)
#  undef RLL_PURE
#endif
#if \
  RLL_HAS_ATTRIBUTE(pure) || \
  RLL_GCC_VERSION_CHECK(2,96,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_SUNPRO_VERSION_CHECK(5,11,0) || \
  RLL_ARM_VERSION_CHECK(4,1,0) || \
  RLL_IBM_VERSION_CHECK(10,1,0) || \
  RLL_TI_VERSION_CHECK(15,12,0) || \
  (RLL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (RLL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (RLL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (RLL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  RLL_PGI_VERSION_CHECK(17,10,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_PURE __attribute__((__pure__))
#elif RLL_SUNPRO_VERSION_CHECK(5,10,0)
#  define RLL_PURE _Pragma("does_not_write_global_data")
#elif defined(__cplusplus) && \
    ( \
      RLL_TI_CL430_VERSION_CHECK(2,0,1) || \
      RLL_TI_CL6X_VERSION_CHECK(4,0,0) || \
      RLL_TI_CL7X_VERSION_CHECK(1,2,0) \
    )
#  define RLL_PURE _Pragma("FUNC_IS_PURE;")
#else
#  define RLL_PURE
#endif

#if defined(RLL_CONST)
#  undef RLL_CONST
#endif
#if \
  RLL_HAS_ATTRIBUTE(const) || \
  RLL_GCC_VERSION_CHECK(2,5,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_SUNPRO_VERSION_CHECK(5,11,0) || \
  RLL_ARM_VERSION_CHECK(4,1,0) || \
  RLL_IBM_VERSION_CHECK(10,1,0) || \
  RLL_TI_VERSION_CHECK(15,12,0) || \
  (RLL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (RLL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (RLL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (RLL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  RLL_PGI_VERSION_CHECK(17,10,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_CONST __attribute__((__const__))
#elif \
  RLL_SUNPRO_VERSION_CHECK(5,10,0)
#  define RLL_CONST _Pragma("no_side_effect")
#else
#  define RLL_CONST RLL_PURE
#endif

#if defined(RLL_RESTRICT)
#  undef RLL_RESTRICT
#endif
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && !defined(__cplusplus)
#  define RLL_RESTRICT restrict
#elif \
  RLL_GCC_VERSION_CHECK(3,1,0) || \
  RLL_MSVC_VERSION_CHECK(14,0,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0) || \
  RLL_ARM_VERSION_CHECK(4,1,0) || \
  RLL_IBM_VERSION_CHECK(10,1,0) || \
  RLL_PGI_VERSION_CHECK(17,10,0) || \
  RLL_TI_CL430_VERSION_CHECK(4,3,0) || \
  RLL_TI_CL2000_VERSION_CHECK(6,2,4) || \
  RLL_TI_CL6X_VERSION_CHECK(8,1,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  (RLL_SUNPRO_VERSION_CHECK(5,14,0) && defined(__cplusplus)) || \
  RLL_IAR_VERSION_CHECK(8,0,0) || \
  defined(__clang__) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_RESTRICT __restrict
#elif RLL_SUNPRO_VERSION_CHECK(5,3,0) && !defined(__cplusplus)
#  define RLL_RESTRICT _Restrict
#else
#  define RLL_RESTRICT
#endif

#if defined(RLL_INLINE)
#  undef RLL_INLINE
#endif
#if \
  (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || \
  (defined(__cplusplus) && (__cplusplus >= 199711L))
#  define RLL_INLINE inline
#elif \
  defined(RLL_GCC_VERSION) || \
  RLL_ARM_VERSION_CHECK(6,2,0)
#  define RLL_INLINE __inline__
#elif \
  RLL_MSVC_VERSION_CHECK(12,0,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0) || \
  RLL_ARM_VERSION_CHECK(4,1,0) || \
  RLL_TI_ARMCL_VERSION_CHECK(5,1,0) || \
  RLL_TI_CL430_VERSION_CHECK(3,1,0) || \
  RLL_TI_CL2000_VERSION_CHECK(6,2,0) || \
  RLL_TI_CL6X_VERSION_CHECK(8,0,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_INLINE __inline
#else
#  define RLL_INLINE
#endif

#if defined(RLL_ALWAYS_INLINE)
#  undef RLL_ALWAYS_INLINE
#endif
#if \
  RLL_HAS_ATTRIBUTE(always_inline) || \
  RLL_GCC_VERSION_CHECK(4,0,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_SUNPRO_VERSION_CHECK(5,11,0) || \
  RLL_ARM_VERSION_CHECK(4,1,0) || \
  RLL_IBM_VERSION_CHECK(10,1,0) || \
  RLL_TI_VERSION_CHECK(15,12,0) || \
  (RLL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (RLL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (RLL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (RLL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10) || \
  RLL_IAR_VERSION_CHECK(8,10,0)
#  define RLL_ALWAYS_INLINE __attribute__((__always_inline__)) RLL_INLINE
#elif \
  RLL_MSVC_VERSION_CHECK(12,0,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_ALWAYS_INLINE __forceinline
#elif defined(__cplusplus) && \
    ( \
      RLL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
      RLL_TI_CL430_VERSION_CHECK(4,3,0) || \
      RLL_TI_CL2000_VERSION_CHECK(6,4,0) || \
      RLL_TI_CL6X_VERSION_CHECK(6,1,0) || \
      RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      RLL_TI_CLPRU_VERSION_CHECK(2,1,0) \
    )
#  define RLL_ALWAYS_INLINE _Pragma("FUNC_ALWAYS_INLINE;")
#elif RLL_IAR_VERSION_CHECK(8,0,0)
#  define RLL_ALWAYS_INLINE _Pragma("inline=forced")
#else
#  define RLL_ALWAYS_INLINE RLL_INLINE
#endif

#if defined(RLL_NEVER_INLINE)
#  undef RLL_NEVER_INLINE
#endif
#if \
  RLL_HAS_ATTRIBUTE(noinline) || \
  RLL_GCC_VERSION_CHECK(4,0,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_SUNPRO_VERSION_CHECK(5,11,0) || \
  RLL_ARM_VERSION_CHECK(4,1,0) || \
  RLL_IBM_VERSION_CHECK(10,1,0) || \
  RLL_TI_VERSION_CHECK(15,12,0) || \
  (RLL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (RLL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (RLL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL430_VERSION_CHECK(4,3,0) || \
  (RLL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  RLL_TI_CL6X_VERSION_CHECK(7,5,0) || \
  RLL_TI_CL7X_VERSION_CHECK(1,2,0) || \
  RLL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10) || \
  RLL_IAR_VERSION_CHECK(8,10,0)
#  define RLL_NEVER_INLINE __attribute__((__noinline__))
#elif \
  RLL_MSVC_VERSION_CHECK(13,10,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_NEVER_INLINE __declspec(noinline)
#elif RLL_PGI_VERSION_CHECK(10,2,0)
#  define RLL_NEVER_INLINE _Pragma("noinline")
#elif RLL_TI_CL6X_VERSION_CHECK(6,0,0) && defined(__cplusplus)
#  define RLL_NEVER_INLINE _Pragma("FUNC_CANNOT_INLINE;")
#elif RLL_IAR_VERSION_CHECK(8,0,0)
#  define RLL_NEVER_INLINE _Pragma("inline=never")
#elif RLL_COMPCERT_VERSION_CHECK(3,2,0)
#  define RLL_NEVER_INLINE __attribute((noinline))
#elif RLL_PELLES_VERSION_CHECK(9,0,0)
#  define RLL_NEVER_INLINE __declspec(noinline)
#else
#  define RLL_NEVER_INLINE
#endif

#if defined(RLL_PRIVATE)
#  undef RLL_PRIVATE
#endif
#if defined(RLL_PUBLIC)
#  undef RLL_PUBLIC
#endif
#if defined(RLL_IMPORT)
#  undef RLL_IMPORT
#endif
#if defined(_WIN32) || defined(__CYGWIN__)
#  define RLL_PRIVATE
#  define RLL_PUBLIC   __declspec(dllexport)
#  define RLL_IMPORT   __declspec(dllimport)
#else
#  if \
    RLL_HAS_ATTRIBUTE(visibility) || \
    RLL_GCC_VERSION_CHECK(3,3,0) || \
    RLL_SUNPRO_VERSION_CHECK(5,11,0) || \
    RLL_INTEL_VERSION_CHECK(13,0,0) || \
    RLL_ARM_VERSION_CHECK(4,1,0) || \
    RLL_IBM_VERSION_CHECK(13,1,0) || \
    ( \
      defined(__TI_EABI__) && \
      ( \
        (RLL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
        RLL_TI_CL6X_VERSION_CHECK(7,5,0) \
      ) \
    ) || \
    RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#    define RLL_PRIVATE __attribute__((__visibility__("hidden")))
#    define RLL_PUBLIC  __attribute__((__visibility__("default")))
#  else
#    define RLL_PRIVATE
#    define RLL_PUBLIC
#  endif
#  define RLL_IMPORT    extern
#endif

#if defined(RLL_NO_THROW)
#  undef RLL_NO_THROW
#endif
#if \
  RLL_HAS_ATTRIBUTE(nothrow) || \
  RLL_GCC_VERSION_CHECK(3,3,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_NO_THROW __attribute__((__nothrow__))
#elif \
  RLL_MSVC_VERSION_CHECK(13,1,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0) || \
  RLL_ARM_VERSION_CHECK(4,1,0)
#  define RLL_NO_THROW __declspec(nothrow)
#else
#  define RLL_NO_THROW
#endif

#if defined(RLL_FALL_THROUGH)
# undef RLL_FALL_THROUGH
#endif
#if \
  RLL_HAS_ATTRIBUTE(fallthrough) || \
  RLL_GCC_VERSION_CHECK(7,0,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_FALL_THROUGH __attribute__((__fallthrough__))
#elif RLL_HAS_CPP_ATTRIBUTE_NS(clang,fallthrough)
#  define RLL_FALL_THROUGH RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[clang::fallthrough]])
#elif RLL_HAS_CPP_ATTRIBUTE(fallthrough)
#  define RLL_FALL_THROUGH RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[fallthrough]])
#elif defined(__fallthrough) /* SAL */
#  define RLL_FALL_THROUGH __fallthrough
#else
#  define RLL_FALL_THROUGH
#endif

#if defined(RLL_RETURNS_NON_NULL)
#  undef RLL_RETURNS_NON_NULL
#endif
#if \
  RLL_HAS_ATTRIBUTE(returns_nonnull) || \
  RLL_GCC_VERSION_CHECK(4,9,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_RETURNS_NON_NULL __attribute__((__returns_nonnull__))
#elif defined(_Ret_notnull_) /* SAL */
#  define RLL_RETURNS_NON_NULL _Ret_notnull_
#else
#  define RLL_RETURNS_NON_NULL
#endif

#if defined(RLL_ARRAY_PARAM)
#  undef RLL_ARRAY_PARAM
#endif
#if \
  defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && \
  !defined(__STDC_NO_VLA__) && \
  !defined(__cplusplus) && \
  !defined(RLL_PGI_VERSION) && \
  !defined(RLL_TINYC_VERSION)
#  define RLL_ARRAY_PARAM(name) (name)
#else
#  define RLL_ARRAY_PARAM(name)
#endif

#if defined(RLL_IS_CONSTANT)
#  undef RLL_IS_CONSTANT
#endif
#if defined(RLL_REQUIRE_CONSTEXPR)
#  undef RLL_REQUIRE_CONSTEXPR
#endif
/* RLL_IS_CONSTEXPR_ is for
   RLL INTERNAL USE ONLY.  API subject to change without notice. */
#if defined(RLL_IS_CONSTEXPR_)
#  undef RLL_IS_CONSTEXPR_
#endif
#if \
  RLL_HAS_BUILTIN(__builtin_constant_p) || \
  RLL_GCC_VERSION_CHECK(3,4,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0) || \
  RLL_TINYC_VERSION_CHECK(0,9,19) || \
  RLL_ARM_VERSION_CHECK(4,1,0) || \
  RLL_IBM_VERSION_CHECK(13,1,0) || \
  RLL_TI_CL6X_VERSION_CHECK(6,1,0) || \
  (RLL_SUNPRO_VERSION_CHECK(5,10,0) && !defined(__cplusplus)) || \
  RLL_CRAY_VERSION_CHECK(8,1,0) || \
  RLL_MCST_LCC_VERSION_CHECK(1,25,10)
#  define RLL_IS_CONSTANT(expr) __builtin_constant_p(expr)
#endif
#if !defined(__cplusplus)
#  if \
       RLL_HAS_BUILTIN(__builtin_types_compatible_p) || \
       RLL_GCC_VERSION_CHECK(3,4,0) || \
       RLL_INTEL_VERSION_CHECK(13,0,0) || \
       RLL_IBM_VERSION_CHECK(13,1,0) || \
       RLL_CRAY_VERSION_CHECK(8,1,0) || \
       RLL_ARM_VERSION_CHECK(5,4,0) || \
       RLL_TINYC_VERSION_CHECK(0,9,24)
#    if defined(__INTPTR_TYPE__)
#      define RLL_IS_CONSTEXPR_(expr) __builtin_types_compatible_p(__typeof__((1 ? (void*) ((__INTPTR_TYPE__) ((expr) * 0)) : (int*) 0)), int*)
#    else
#      include <stdint.h>
#      define RLL_IS_CONSTEXPR_(expr) __builtin_types_compatible_p(__typeof__((1 ? (void*) ((intptr_t) ((expr) * 0)) : (int*) 0)), int*)
#    endif
#  elif \
       ( \
          defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && \
          !defined(RLL_SUNPRO_VERSION) && \
          !defined(RLL_PGI_VERSION) && \
          !defined(RLL_IAR_VERSION)) || \
       (RLL_HAS_EXTENSION(c_generic_selections) && !defined(RLL_IAR_VERSION)) || \
       RLL_GCC_VERSION_CHECK(4,9,0) || \
       RLL_INTEL_VERSION_CHECK(17,0,0) || \
       RLL_IBM_VERSION_CHECK(12,1,0) || \
       RLL_ARM_VERSION_CHECK(5,3,0)
#    if defined(__INTPTR_TYPE__)
#      define RLL_IS_CONSTEXPR_(expr) _Generic((1 ? (void*) ((__INTPTR_TYPE__) ((expr) * 0)) : (int*) 0), int*: 1, void*: 0)
#    else
#      include <stdint.h>
#      define RLL_IS_CONSTEXPR_(expr) _Generic((1 ? (void*) ((intptr_t) * 0) : (int*) 0), int*: 1, void*: 0)
#    endif
#  elif \
       defined(RLL_GCC_VERSION) || \
       defined(RLL_INTEL_VERSION) || \
       defined(RLL_TINYC_VERSION) || \
       defined(RLL_TI_ARMCL_VERSION) || \
       RLL_TI_CL430_VERSION_CHECK(18,12,0) || \
       defined(RLL_TI_CL2000_VERSION) || \
       defined(RLL_TI_CL6X_VERSION) || \
       defined(RLL_TI_CL7X_VERSION) || \
       defined(RLL_TI_CLPRU_VERSION) || \
       defined(__clang__)
#    define RLL_IS_CONSTEXPR_(expr) ( \
         sizeof(void) != \
         sizeof(*( \
           1 ? \
             ((void*) ((expr) * 0L) ) : \
             ((struct { char v[sizeof(void) * 2]; } *) 1) \
           ) \
         ) \
       )
#  endif
#endif
#if defined(RLL_IS_CONSTEXPR_)
#  if !defined(RLL_IS_CONSTANT)
#    define RLL_IS_CONSTANT(expr) RLL_IS_CONSTEXPR_(expr)
#  endif
#  define RLL_REQUIRE_CONSTEXPR(expr) (RLL_IS_CONSTEXPR_(expr) ? (expr) : (-1))
#else
#  if !defined(RLL_IS_CONSTANT)
#    define RLL_IS_CONSTANT(expr) (0)
#  endif
#  define RLL_REQUIRE_CONSTEXPR(expr) (expr)
#endif

#if defined(RLL_BEGIN_C_DECLS)
#  undef RLL_BEGIN_C_DECLS
#endif
#if defined(RLL_END_C_DECLS)
#  undef RLL_END_C_DECLS
#endif
#if defined(RLL_C_DECL)
#  undef RLL_C_DECL
#endif
#if defined(__cplusplus)
#  define RLL_BEGIN_C_DECLS extern "C" {
#  define RLL_END_C_DECLS }
#  define RLL_C_DECL extern "C"
#else
#  define RLL_BEGIN_C_DECLS
#  define RLL_END_C_DECLS
#  define RLL_C_DECL
#endif

#if defined(RLL_STATIC_ASSERT)
#  undef RLL_STATIC_ASSERT
#endif
#if \
  !defined(__cplusplus) && ( \
      (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)) || \
      (RLL_HAS_FEATURE(c_static_assert) && !defined(RLL_INTEL_CL_VERSION)) || \
      RLL_GCC_VERSION_CHECK(6,0,0) || \
      RLL_INTEL_VERSION_CHECK(13,0,0) || \
      defined(_Static_assert) \
    )
#  define RLL_STATIC_ASSERT(expr, message) _Static_assert(expr, message)
#elif \
  (defined(__cplusplus) && (__cplusplus >= 201103L)) || \
  RLL_MSVC_VERSION_CHECK(16,0,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_STATIC_ASSERT(expr, message) RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(static_assert(expr, message))
#else
#  define RLL_STATIC_ASSERT(expr, message)
#endif

#if defined(RLL_NULL)
#  undef RLL_NULL
#endif
#if defined(__cplusplus)
#  if __cplusplus >= 201103L
#    define RLL_NULL RLL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(nullptr)
#  elif defined(NULL)
#    define RLL_NULL NULL
#  else
#    define RLL_NULL RLL_STATIC_CAST(void*, 0)
#  endif
#elif defined(NULL)
#  define RLL_NULL NULL
#else
#  define RLL_NULL ((void*) 0)
#endif

#if defined(RLL_MESSAGE)
#  undef RLL_MESSAGE
#endif
#if RLL_HAS_WARNING("-Wunknown-pragmas")
#  define RLL_MESSAGE(msg) \
  RLL_DIAGNOSTIC_PUSH \
  RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS \
  RLL_PRAGMA(message msg) \
  RLL_DIAGNOSTIC_POP
#elif \
  RLL_GCC_VERSION_CHECK(4,4,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0)
#  define RLL_MESSAGE(msg) RLL_PRAGMA(message msg)
#elif RLL_CRAY_VERSION_CHECK(5,0,0)
#  define RLL_MESSAGE(msg) RLL_PRAGMA(_CRI message msg)
#elif RLL_IAR_VERSION_CHECK(8,0,0)
#  define RLL_MESSAGE(msg) RLL_PRAGMA(message(msg))
#elif RLL_PELLES_VERSION_CHECK(2,0,0)
#  define RLL_MESSAGE(msg) RLL_PRAGMA(message(msg))
#else
#  define RLL_MESSAGE(msg)
#endif

#if defined(RLL_WARNING)
#  undef RLL_WARNING
#endif
#if RLL_HAS_WARNING("-Wunknown-pragmas")
#  define RLL_WARNING(msg) \
  RLL_DIAGNOSTIC_PUSH \
  RLL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS \
  RLL_PRAGMA(clang warning msg) \
  RLL_DIAGNOSTIC_POP
#elif \
  RLL_GCC_VERSION_CHECK(4,8,0) || \
  RLL_PGI_VERSION_CHECK(18,4,0) || \
  RLL_INTEL_VERSION_CHECK(13,0,0)
#  define RLL_WARNING(msg) RLL_PRAGMA(GCC warning msg)
#elif \
  RLL_MSVC_VERSION_CHECK(15,0,0) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_WARNING(msg) RLL_PRAGMA(message(msg))
#else
#  define RLL_WARNING(msg) RLL_MESSAGE(msg)
#endif

#if defined(RLL_REQUIRE)
#  undef RLL_REQUIRE
#endif
#if defined(RLL_REQUIRE_MSG)
#  undef RLL_REQUIRE_MSG
#endif
#if RLL_HAS_ATTRIBUTE(diagnose_if)
#  if RLL_HAS_WARNING("-Wgcc-compat")
#    define RLL_REQUIRE(expr) \
       RLL_DIAGNOSTIC_PUSH \
       _Pragma("clang diagnostic ignored \"-Wgcc-compat\"") \
       __attribute__((diagnose_if(!(expr), #expr, "error"))) \
       RLL_DIAGNOSTIC_POP
#    define RLL_REQUIRE_MSG(expr,msg) \
       RLL_DIAGNOSTIC_PUSH \
       _Pragma("clang diagnostic ignored \"-Wgcc-compat\"") \
       __attribute__((diagnose_if(!(expr), msg, "error"))) \
       RLL_DIAGNOSTIC_POP
#  else
#    define RLL_REQUIRE(expr) __attribute__((diagnose_if(!(expr), #expr, "error")))
#    define RLL_REQUIRE_MSG(expr,msg) __attribute__((diagnose_if(!(expr), msg, "error")))
#  endif
#else
#  define RLL_REQUIRE(expr)
#  define RLL_REQUIRE_MSG(expr,msg)
#endif

#if defined(RLL_FLAGS)
#  undef RLL_FLAGS
#endif
#if RLL_HAS_ATTRIBUTE(flag_enum) && (!defined(__cplusplus) || RLL_HAS_WARNING("-Wbitfield-enum-conversion"))
#  define RLL_FLAGS __attribute__((__flag_enum__))
#else
#  define RLL_FLAGS
#endif

#if defined(RLL_FLAGS_CAST)
#  undef RLL_FLAGS_CAST
#endif
#if RLL_INTEL_VERSION_CHECK(19,0,0)
#  define RLL_FLAGS_CAST(T, expr) (__extension__ ({ \
  RLL_DIAGNOSTIC_PUSH \
      _Pragma("warning(disable:188)") \
      ((T) (expr)); \
      RLL_DIAGNOSTIC_POP \
    }))
#else
#  define RLL_FLAGS_CAST(T, expr) RLL_STATIC_CAST(T, expr)
#endif

#if defined(RLL_EMPTY_BASES)
#  undef RLL_EMPTY_BASES
#endif
#if \
  (RLL_MSVC_VERSION_CHECK(19,0,23918) && !RLL_MSVC_VERSION_CHECK(20,0,0)) || \
  RLL_INTEL_CL_VERSION_CHECK(2021,1,0)
#  define RLL_EMPTY_BASES __declspec(empty_bases)
#else
#  define RLL_EMPTY_BASES
#endif

/* Remaining macros are deprecated. */

#if defined(RLL_GCC_NOT_CLANG_VERSION_CHECK)
#  undef RLL_GCC_NOT_CLANG_VERSION_CHECK
#endif
#if defined(__clang__)
#  define RLL_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch) (0)
#else
#  define RLL_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch) RLL_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(RLL_CLANG_HAS_ATTRIBUTE)
#  undef RLL_CLANG_HAS_ATTRIBUTE
#endif
#define RLL_CLANG_HAS_ATTRIBUTE(attribute) RLL_HAS_ATTRIBUTE(attribute)

#if defined(RLL_CLANG_HAS_CPP_ATTRIBUTE)
#  undef RLL_CLANG_HAS_CPP_ATTRIBUTE
#endif
#define RLL_CLANG_HAS_CPP_ATTRIBUTE(attribute) RLL_HAS_CPP_ATTRIBUTE(attribute)

#if defined(RLL_CLANG_HAS_BUILTIN)
#  undef RLL_CLANG_HAS_BUILTIN
#endif
#define RLL_CLANG_HAS_BUILTIN(builtin) RLL_HAS_BUILTIN(builtin)

#if defined(RLL_CLANG_HAS_FEATURE)
#  undef RLL_CLANG_HAS_FEATURE
#endif
#define RLL_CLANG_HAS_FEATURE(feature) RLL_HAS_FEATURE(feature)

#if defined(RLL_CLANG_HAS_EXTENSION)
#  undef RLL_CLANG_HAS_EXTENSION
#endif
#define RLL_CLANG_HAS_EXTENSION(extension) RLL_HAS_EXTENSION(extension)

#if defined(RLL_CLANG_HAS_DECLSPEC_DECLSPEC_ATTRIBUTE)
#  undef RLL_CLANG_HAS_DECLSPEC_DECLSPEC_ATTRIBUTE
#endif
#define RLL_CLANG_HAS_DECLSPEC_ATTRIBUTE(attribute) RLL_HAS_DECLSPEC_ATTRIBUTE(attribute)

#if defined(RLL_CLANG_HAS_WARNING)
#  undef RLL_CLANG_HAS_WARNING
#endif
#define RLL_CLANG_HAS_WARNING(warning) RLL_HAS_WARNING(warning)