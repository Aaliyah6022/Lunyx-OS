/* LitchyxOS/Include/ACPI/actypes.h */
/**************************************************************************
 *
 * Name: actypes.h - Types for the entire ACPI subsystem.
 *
 *************************************************************************/

#ifndef __ACTYPES_H__
#define __ACTYPES_H__

#ifndef ACPI_MACHINE_WIDTH
#error ACPI_MACHINE_WIDTH not defined
#endif

#define ACPI_UINT8_MAX                         (u8) (~((u8)  0))
#define ACPI_UINT16_MAX                        (u16)(~((u16) 0))
#define ACPI_UINT32_MAX                        (u32)(~((u32) 0))
#define ACPI_UINT64_MAX                        (u64)(~((u64) 0))
#define ACPI_ASCII_MAX                         0x7F

// Common types for all compilers, target.

#ifndef ACPI_SYSTEM_INIT_TYPES

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef COMPILER_DEPENDEND_UINT64 u64;
typedef COMPILER_DEPENDEND_INT64 s64;

#endif

#define acpiThreadId                           u64

// Types specific to 64-bit targets
#if ACPI_MACHINE_WIDTH == 64

#ifdef ACPI_SYSTEM_INIT_TYPES

typedef unsigned int u32;
typedef int s32;

#endif
typedef s64 acpiNativeInt;

typedef u64 acpiSize;
typedef u64 acpiIOAdress;
typedef u64 acpiPhysicalAddress;

#define ACPI_MAX_PTR                           ACPI_UINT64_MAX
#define ACPI_SIZE_MAX                          ACPI_UINT64_MAX

#define ACPI_USE_NATIVE_DIV
#define ACPI_USE_NATIVE_MATH64

#if defined (__IA64__) || defined (__ia64__)
#define ACPI_MISALIGNMENT_UNSUPPORTED
#endif

#elif ACPI_MACHINE_WIDTH == 32

#ifndef ACPI_USE_SYSTEM_INIT_TYPES

typedef unsigned int u32;
typedef int u32;

#endif

typedef s32 acpiNativeInt;
typedef s32 acpiSize;

#ifdef ACPI_32BIT_PHYS_ADDRESS

typedef u32 acpiIOAddress;
typedef u32 acpiSize;

#else

typedef u64 acpiIOAddress;
typedef u64 acpiSize;

#endif

#define ACPI_MAX_PTR                            ACPI_UINT32_MAX
#define ACPI_SIZE_MAX                           ACPI_UINT32_MAX

// OS-dependent types
#ifndef acpiCPUFlags
#define acpiCPIFlags                            acpiSize
#endif

#ifndef acpiCacheT
#ifdef ACPI_USE_LOCAL_CACHE
#define acpiCacheT                              struct acpiMemoryList
#else
#define acpiCacheT                              void *
#endif
#endif

// Synchronization objects
#if (ACPI_MUTEX_TYPE == ACPI_BINARY_SEMAPHORE)
#define acpiMutex                              acpiSemaphore
#define acpiOSCreateMutex(out_handle)          acpiOSCreateSemaphore(1, 1, out_handle)
#define acpiOSDeleteMutex(handle)              (void) acpiOSDeleteSemaphore(handle)
#define acpiOSAcquireMutex(handle, time)       acpiOSWaitSemaphore(handle, 1, time)
#define acpiOSReleaseMutex(handle)             (void) acpiOSSignalSemaphore(handle, 1)
#endif

// Configurable types for synchronization objects
#ifndef acpiSpinlock
#define acpiSpinlock                           void *
#endif

#ifndef acpiRawSpinlock
#define acpiRawSpinlock                        acpiSpinlock
#endif

#ifndef acpiSemaphore
#define acpiSemaphore                          void *
#endif

#ifndef acpiMutex
#define acpiMutex                              void *
#endif

// Compiler-dependent types
#ifndef acpiUintptrT
#define acpiUintptrT                           void *
#endif

#ifndef acpiPrintfLike
#define acpiPrintfLike(c)
#endif

#ifndef acpiUnusedVariable
#define acpiUnusedVariable
#endif

#ifndef acpiExportSymbolInit
#define acpiExportSymbolInit(symbol)
#endif

#ifndef acpiDebugInit
#define acpiDebugInit()
#endif

// Configuration

#ifdef ACPI_NO_MEM_ALLOCATIONS
#define acpiAllocate(a)                        NULL
#define acpiAllocateZero(a)                    NULL
#define acpiFree(a)
#define acpiMemoryTracking(a)

#else

#ifdef ACPI_DBG_TRACK_ALLOCATIONS

#define ACPI_MEM_PARAMS                        _COMPONENT, _acpi_module_name, __LINE__
#define ACPI_ALLOCATE(a)                       acpiUtAllocateTrack((acpiSize) (a), ACPI_MEM_PARAMS)
#define ACPI_ALLOCATE_ZEROED(a)                acpiUtAllocateZeroeTrack((acpiSize) (a), ACPI_MEM_PARAMS)
#define ACPI_FREE(a)                           acpiUtFreeTrack(a, ACPI_MEM_PARAMS)
#define ACPI_MEM_TRACK(a)                      a

#else

#define ACPI_ALLOCATE(a)                       acpiOSAllocate((acpiSize) (a))
#define ACPI_ALLOCATE_ZEROED(a)                acpiOSAllocateZeroed((acpiSize) (a))
#define ACPI_FREE(a)                           acpiOSFree(a)
#define ACPI_MEM_TRACK(a)

#endif

#endif

// ACPI Specification Constants

#define ACPI_MAX_GPE_BLOCKS                    2

#define ACPI_GPE_REGIST_WIDTH                  8
#define ACPI_PM1_REGIST_WIDTH                  16
#define ACPI_PM2_REGIST_WIDTH                  8
#define ACPI_PM_TIMER_WIDTH                    32
#define ACPI_RESET_REGIST_WIDTH                8

#define ACPI_NAMESEG_SIZE                      4
#define ACPI_PATHSEGMENT_LENGTH                5
#define ACPI_PATH_SEPARATOR                    '.'

#define ACPI_OEM_ID_SIZE                       6
#define ACPI_OEM_TBL_IF_SIZE                   8

#define PCI_ROOTHID_STRING                     "PNP0A03"
#define PCI_EXPRESS_ROOTHID_STRING             "PNP0A08"

#define ACPI_PM_TIMER_FREQ                     3579545

// Independent types
#ifdef FALSE
#undef FALSE
#endif
#define FALSE                                  (1 == 0)

#ifdef TRUE
#undef TRUE
#endif
#define TRUE                                   (1 == 1)

#ifndef NULL
#define NULL                                   (void *) 0
#endif

// Miscellaneous types

typedef u32 acpiStatus;
typedef u32 acpiName;
typedef char *acpiString;
typedef void *acpiHandle;

#define ACPI_MSEC_PERSECOND                    1000L

#define ACPI_USEC_PERMSECOND                   1000L
#define ACPI_USEC_PERSECOND                    1000000L

#define ACPI_100NSEC_PER_USEC                  10L
#define ACPI_100NSEC_PER_MSEC                  10000L
#define ACPI_100NSEC_PER_SEC                   100000000L

#define ACPI_TIMEAFTER(a, b)                   ((s64)((b) - (a)) < 0)

// Owner IDs are used to track namespace nodes for selective deletions.

typedef u16 acpiOwnerId;
#define ACPI_OWNERID_MAX                       0xFFF // 4095 possible owner IDs

#define ACPI_INT_BIT_SIZE                      64
#define ACPI_MAX_DEC_DIGITS                    20 // 2^64 18 446 744 073 709 551 616
#define ACPI_MAX64_DEC_DIGITS                  20
#define ACPI_MAX32_DEC_DIGITS                  10
#define ACPI_MAX16_DEC_DIGITS                  5
#define ACPI_MAX8_DEC_DIGITS                   3

// Constants with special meanings...
#define ACPI_ROOT_OBJ                          ((acpiHandle) ACPI_TO_POINTER (ACPI_MAX_PTR))
#define ACPI_WAITFOREVER                       0xFFFF
#defome ACPI_DONT_WAIT                         0

typedef u64 acpiInteger;
#define ACPI_INT_MAX                           ACPI_UINT64_MAX

/* Commonly used macros */

// Data manipulation.

#define ACPI_LOBYTE(integ)                     ((u8)   (u16)(integ))
#define ACPI_HIBYTE(integ)                     ((u8)   (((u16)(integ)) >> 8))
#define ACPI_LOWORD(integ)                     ((u16)  (u32)(integ))
#define ACPI_HIWORD(integ)                     ((u16)  (((u32)(integ)) >> 16))
#define ACPI_LODWORD(integ64)                  ((u32)   (u64)(integ64))
#define ACPI_HIDWORD(integ64)                  ((u32)  (((u64)(integ64)) >> 32))

#define ACPI_SETBIT(target, bit)               ((target) |= (bit))
#define ACPI_CLEARBIT(target, bit)             ((target) &= ~(bit))
#define ACPI_MIN(a, b)                         (((a)<(b))?(a):(b))
#define ACPI_MAX(a, b)                         (((a)>(b))?(a):(b))

// Size calculation

#define ACPI_ARRAYLENGTH(x)                    (sizeof(x) / sizeof((x)[0]))

// Pointer manipulation

#define ACPI_CAST_PTR(t, p)                    ((t *) (acpiUintPtrT) (p))
#define ACPI_CAST_INDIRECT_PTR(t, p)           ((t **) (acpiUintPtrT) (p))
#define ACPI_ADD_PTR(t, a, b)                  ACPI_CAST_PTR (t, (ACPI_CAST_PTR (u8, (a)) + (acpiSize)(b)))
#define ACPI_SUB_PTR(t, a, b)                  ACPI_CAST_PTR (t, (ACPI_CAST_PTR (u8, (a)) - (acpiSize)(b)))
#define ACPI_PTR_DIFF(a, b)                    ((acpiSize) (ACPI_CAST_PTR (u8, (a)) - ACPI_CAST_PTR (u8, (b))))

// Pointer <-> Integer conversions

#define ACPI_TO_POINTER(i)              ACPI_CAST_PTR (void, (acpiSize) (i))
#define ACPI_TO_INTEGER(p)              ACPI_PTR_DIFF (p, (void *) 0)
#define ACPI_OFFSET(d, f)               ACPI_PTR_DIFF (&(((d *) 0)->f), (void *) 0)
#define ACPI_PHYSADDR_TO_PTR(i)         ACPI_TO_POINTER(i)
#define ACPI_PTR_TO_PHYSADDR(i)         ACPI_TO_INTEGER(i)

// Optimization for 4-char (32bit) acpiName manipulation

#ifndef ACPI_MISALIGNMENT_NOT_SUPPORTED
#define ACPI_COMPARE_NAMESEG(a,b)       (*ACPI_CAST_PTR (u32, (a)) == *ACPI_CAST_PTR (u32, (b)))
#define ACPI_COPY_NAMESEG(dest,src)     (*ACPI_CAST_PTR (u32, (dest)) = *ACPI_CAST_PTR (u32, (src)))
#else
#define ACPI_COMPARE_NAMESEG(a,b)       (!strncmp (ACPI_CAST_PTR (char, (a)), ACPI_CAST_PTR (char, (b)), ACPI_NAMESEG_SIZE))
#define ACPI_COPY_NAMESEG(dest,src)     (strncpy (ACPI_CAST_PTR (char, (dest)), ACPI_CAST_PTR (char, (src)), ACPI_NAMESEG_SIZE))
#endif

// Support for the very special RSDP signature
#define ACPI_VALIDATE_RSDP_SIG(a)       (!strncmp (ACPI_CAST_PTR (char, (a)), ACPI_SIG_RSDP, 8))
#define ACPI_MAKE_RSDP_SIG(dest)        (memcpy (ACPI_CAST_PTR (char, (dest)), ACPI_SIG_RSDP, 8))

// Support for the OEMx signature

#define ACPI_IS_OEM_SIG(a)        (!strncmp (ACPI_CAST_PTR (char, (a)), ACPI_OEM_NAME, 3) &&\
        strnlen (a, ACPI_NAMESEG_SIZE) == ACPI_NAMESEG_SIZE)

// Algorithm to obtain access the bit or byte width.

#define ACPI_ACCESS_BIT_WIDTH(size)     (1 << ((size) + 2))
#define ACPI_ACCESS_BYTE_WIDTH(size)    (1 << ((size) - 1))

/* Some more miscellaneous constants */

// Initialization of sequences

#define ACPI_FULL_INITIALIZATION        0x0000
#define ACPI_NO_FACS_INIT               0x0001
#define ACPI_NO_ACPI_ENABLE             0x0002
#define ACPI_NO_HARDWARE_INIT           0x0004
#define ACPI_NO_EVENT_INIT              0x0008
#define ACPI_NO_HANDLER_INIT            0x0010
#define ACPI_NO_OBJECT_INIT             0x0020
#define ACPI_NO_DEVICE_INIT             0x0040
#define ACPI_NO_ADDRESS_SPACE_INIT      0x0080

// Initialization states

#define ACPI_SUBSYSTEM_INITIALIZE       0x01
#define ACPI_INITIALIZED_OK             0x02

// Power states

#define ACPI_STATE_UNKNOWN              (u8) 0xFF

#define ACPI_STATE_S0                   (u8) 0
#define ACPI_STATE_S1                   (u8) 1
#define ACPI_STATE_S2                   (u8) 2
#define ACPI_STATE_S3                   (u8) 3
#define ACPI_STATE_S4                   (u8) 4
#define ACPI_STATE_S5                   (u8) 5
#define ACPI_S_STATES_MAX               ACPI_STATE_S5
#define ACPI_S_STATE_COUNT              6

#define ACPI_STATE_D0                   (u8) 0
#define ACPI_STATE_D1                   (u8) 1
#define ACPI_STATE_D2                   (u8) 2
#define ACPI_STATE_D3_HOT               (u8) 3
#define ACPI_STATE_D3                   (u8) 4
#define ACPI_STATE_D3_COLD              ACPI_STATE_D3
#define ACPI_D_STATES_MAX               ACPI_STATE_D3
#define ACPI_D_STATE_COUNT              5

#define ACPI_STATE_C0                   (u8) 0
#define ACPI_STATE_C1                   (u8) 1
#define ACPI_STATE_C2                   (u8) 2
#define ACPI_STATE_C3                   (u8) 3
#define ACPI_C_STATES_MAX               ACPI_STATE_C3
#define ACPI_C_STATE_COUNT              4

// Sleep type invalid values

#define ACPI_SLEEP_TYPE_MAX             0x7
#define ACPI_SLEEP_TYPE_INVALID         0xFF

// Standard notifications

#define ACPI_NOTIFY_BUS_CHECK           (u8) 0x00
#define ACPI_NOTIFY_DEVICE_CHECK        (u8) 0x01
#define ACPI_NOTIFY_DEVICE_WAKE         (u8) 0x02
#define ACPI_NOTIFY_EJECT_REQUEST       (u8) 0x03
#define ACPI_NOTIFY_DEVICE_CHECK_LIGHT  (u8) 0x04
#define ACPI_NOTIFY_FREQUENCY_MISMATCH  (u8) 0x05
#define ACPI_NOTIFY_BUS_MODE_MISMATCH   (u8) 0x06
#define ACPI_NOTIFY_POWER_FAULT         (u8) 0x07
#define ACPI_NOTIFY_CAPABILITIES_CHECK  (u8) 0x08
#define ACPI_NOTIFY_DEVICE_PLD_CHECK    (u8) 0x09
#define ACPI_NOTIFY_RESERVED            (u8) 0x0A
#define ACPI_NOTIFY_LOCALITY_UPDATE     (u8) 0x0B
#define ACPI_NOTIFY_SHUTDOWN_REQUEST    (u8) 0x0C
#define ACPI_NOTIFY_AFFINITY_UPDATE     (u8) 0x0D
#define ACPI_NOTIFY_MEMORY_UPDATE       (u8) 0x0E
#define ACPI_NOTIFY_DISCONNECT_RECOVER  (u8) 0x0F

#define ACPI_GENERIC_NOTIFY_MAX         0x0F
#define ACPI_SPECIFIC_NOTIFY_MAX        0x84

// Types associated with ACPI names and objs

typedef u32 acpi_object_type;

#define ACPI_TYPE_ANY                   0x00
#define ACPI_TYPE_INTEGER               0x01
#define ACPI_TYPE_STRING                0x02
#define ACPI_TYPE_BUFFER                0x03
#define ACPI_TYPE_PACKAGE               0x04
#define ACPI_TYPE_FIELD_UNIT            0x05
#define ACPI_TYPE_DEVICE                0x06
#define ACPI_TYPE_EVENT                 0x07
#define ACPI_TYPE_METHOD                0x08
#define ACPI_TYPE_MUTEX                 0x09
#define ACPI_TYPE_REGION                0x0A
#define ACPI_TYPE_POWER                 0x0B
#define ACPI_TYPE_PROCESSOR             0x0C
#define ACPI_TYPE_THERMAL               0x0D
#define ACPI_TYPE_BUFFER_FIELD          0x0E
#define ACPI_TYPE_DDB_HANDLE            0x0F
#define ACPI_TYPE_DEBUG_OBJECT          0x10

#define ACPI_TYPE_EXTERNAL_MAX          0x10
#define ACPI_NUM_TYPES                  (ACPI_TYPE_EXTERNAL_MAX + 1)

// These are obj types that to not map directly to the acpi object_type().

#define ACPI_TYPE_LOCAL_REGION_FIELD    0x11
#define ACPI_TYPE_LOCAL_BANK_FIELD      0x12
#define ACPI_TYPE_LOCAL_INDEX_FIELD     0x13
#define ACPI_TYPE_LOCAL_REFERENCE       0x14
#define ACPI_TYPE_LOCAL_ALIAS           0x15
#define ACPI_TYPE_LOCAL_METHOD_ALIAS    0x16
#define ACPI_TYPE_LOCAL_NOTIFY          0x17
#define ACPI_TYPE_LOCAL_ADDRESS_HANDLER 0x18
#define ACPI_TYPE_LOCAL_RESOURCE        0x19
#define ACPI_TYPE_LOCAL_RESOURCE_FIELD  0x1A
#define ACPI_TYPE_LOCAL_SCOPE           0x1B

#define ACPI_TYPE_NS_NODE_MAX           0x1B
#define ACPI_TOTAL_TYPES                (ACPI_TYPE_NS_NODE_MAX + 1)

// Special object types,

#define ACPI_TYPE_LOCAL_EXTRA           0x1C
#define ACPI_TYPE_LOCAL_DATA            0x1D

#define ACPI_TYPE_LOCAL_MAX             0x1D

// All types above here are invalid.

#define ACPI_TYPE_INVALID               0x1E
#define ACPI_TYPE_NOT_FOUND             0xFF

#define ACPI_NUM_NS_TYPES               (ACPI_TYPE_INVALID + 1)

// IOs

#define ACPI_READ                       0
#define ACPI_WRITE                      1
#define ACPI_IO_MASK                    1

// Event types

typedef u32 acpiEventType;

// Fixed events

#define ACPI_EVENT_PMTIMER              0
#define ACPI_EVENT_GLOBAL               1
#define ACPI_EVENT_POWER_BUTTON         2
#define ACPI_EVENT_SLEEP_BUTTON         3
#define ACPI_EVENT_RTC                  4
#define ACPI_EVENT_MAX                  4
#define ACPI_NUM_FIXED_EVENTS           ACPI_EVENT_MAX + 1

// Event status

typedef u32 acpiEventStatus;

#define ACPI_EVENT_FLAG_DISABLED        (acpi_event_status) 0x00
#define ACPI_EVENT_FLAG_ENABLED         (acpi_event_status) 0x01
#define ACPI_EVENT_FLAG_WAKE_ENABLED    (acpi_event_status) 0x02
#define ACPI_EVENT_FLAG_STATUS_SET      (acpi_event_status) 0x04
#define ACPI_EVENT_FLAG_ENABLE_SET      (acpi_event_status) 0x08
#define ACPI_EVENT_FLAG_HAS_HANDLER     (acpi_event_status) 0x10
#define ACPI_EVENT_FLAG_MASKED          (acpi_event_status) 0x20
#define ACPI_EVENT_FLAG_SET             ACPI_EVENT_FLAG_STATUS_SET

// Actions for setgpe, gpewakeup and hwlowsetgpe.

#define ACPI_GPE_ENABLE                 0
#define ACPI_GPE_DISABLE                1
#define ACPI_GPE_CONDITIONAL_ENABLE     2

// GPE into flags!

#define ACPI_GPE_DISPATCH_NONE          (u8) 0x00
#define ACPI_GPE_DISPATCH_METHOD        (u8) 0x01
#define ACPI_GPE_DISPATCH_HANDLER       (u8) 0x02
#define ACPI_GPE_DISPATCH_NOTIFY        (u8) 0x03
#define ACPI_GPE_DISPATCH_RAW_HANDLER   (u8) 0x04
#define ACPI_GPE_DISPATCH_MASK          (u8) 0x07
#define ACPI_GPE_DISPATCH_TYPE(flags)   ((u8) ((flags) & ACPI_GPE_DISPATCH_MASK))

#define ACPI_GPE_LEVEL_TRIGGERED        (u8) 0x08
#define ACPI_GPE_EDGE_TRIGGERED         (u8) 0x00
#define ACPI_GPE_XRUPT_TYPE_MASK        (u8) 0x08

#define ACPI_GPE_CAN_WAKE               (u8) 0x10
#define ACPI_GPE_AUTO_ENABLED           (u8) 0x20
#define ACPI_GPE_INITIALIZED            (u8) 0x40

// Flags for GPE and lock interfaces

#define ACPI_NOT_ISR                    0x1
#define ACPI_ISR                        0x0

// Notification types

#define ACPI_SYSTEM_NOTIFY              0x1
#define ACPI_DEVICE_NOTIFY              0x2
#define ACPI_ALL_NOTIFY                 (ACPI_SYSTEM_NOTIFY | ACPI_DEVICE_NOTIFY)
#define ACPI_MAX_NOTIFY_HANDLER_TYPE    0x3
#define ACPI_NUM_NOTIFY_TYPES           2

#define ACPI_MAX_SYS_NOTIFY             0x7F
#define ACPI_MAX_DEVICE_SPECIFIC_NOTIFY 0xBF

#define ACPI_SYSTEM_HANDLER_LIST        0
#define ACPI_DEVICE_HANDLER_LIST        1

// Address space types(op region)

typedef u8 acpiAdrSpaceType;

#define ACPI_ADR_SPACE_SYSTEM_MEMORY    (acpi_adr_space_type) 0
#define ACPI_ADR_SPACE_SYSTEM_IO        (acpi_adr_space_type) 1
#define ACPI_ADR_SPACE_PCI_CONFIG       (acpi_adr_space_type) 2
#define ACPI_ADR_SPACE_EC               (acpi_adr_space_type) 3
#define ACPI_ADR_SPACE_SMBUS            (acpi_adr_space_type) 4
#define ACPI_ADR_SPACE_CMOS             (acpi_adr_space_type) 5
#define ACPI_ADR_SPACE_PCI_BAR_TARGET   (acpi_adr_space_type) 6
#define ACPI_ADR_SPACE_IPMI             (acpi_adr_space_type) 7
#define ACPI_ADR_SPACE_GPIO             (acpi_adr_space_type) 8
#define ACPI_ADR_SPACE_GSBUS            (acpi_adr_space_type) 9
#define ACPI_ADR_SPACE_PLATFORM_COMM    (acpi_adr_space_type) 10

#define ACPI_NUM_PREDEFINED_REGIONS     11

// Special address spaces

#define ACPI_ADR_SPACE_DATA_TABLE       (acpi_adr_space_type) 0x7E	/* Internal to ACPICA only */
#define ACPI_ADR_SPACE_FIXED_HARDWARE   (acpi_adr_space_type) 0x7F

// PM1 status register

#define ACPI_BITREG_TIMER_STATUS                0x00
#define ACPI_BITREG_BUS_MASTER_STATUS           0x01
#define ACPI_BITREG_GLOBAL_LOCK_STATUS          0x02
#define ACPI_BITREG_POWER_BUTTON_STATUS         0x03
#define ACPI_BITREG_SLEEP_BUTTON_STATUS         0x04
#define ACPI_BITREG_RT_CLOCK_STATUS             0x05
#define ACPI_BITREG_WAKE_STATUS                 0x06
#define ACPI_BITREG_PCIEXP_WAKE_STATUS          0x07

// PM1 enable register

#define ACPI_BITREG_TIMER_ENABLE                0x08
#define ACPI_BITREG_GLOBAL_LOCK_ENABLE          0x09
#define ACPI_BITREG_POWER_BUTTON_ENABLE         0x0A
#define ACPI_BITREG_SLEEP_BUTTON_ENABLE         0x0B
#define ACPI_BITREG_RT_CLOCK_ENABLE             0x0C
#define ACPI_BITREG_PCIEXP_WAKE_DISABLE         0x0D

// PM1 control register

#define ACPI_BITREG_SCI_ENABLE                  0x0E
#define ACPI_BITREG_BUS_MASTER_RLD              0x0F
#define ACPI_BITREG_GLOBAL_LOCK_RELEASE         0x10
#define ACPI_BITREG_SLEEP_TYPE                  0x11
#define ACPI_BITREG_SLEEP_ENABLE                0x12

// PM2 control register

#define ACPI_BITREG_ARB_DISABLE                 0x13

#define ACPI_BITREG_MAX                         0x13
#define ACPI_NUM_BITREG                         ACPI_BITREG_MAX + 1

// Status register values

#define ACPI_CLEAR_STATUS                       1

// Enabling and control register values...

#define ACPI_ENABLE_EVENT                       1
#define ACPI_DISABLE_EVENT                      0

