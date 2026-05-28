//
// Created by cj on 26/5/26.
//

#ifndef SHOOTER_RAYLIB_COREDBG_H
#define SHOOTER_RAYLIB_COREDBG_H

#if defined(MSVC)
#define FORCEINLINE __inline
#elif defined(__GNUC__)
#define FORCEINLINE __attribute__((always_inline))
#endif


#endif //SHOOTER_RAYLIB_COREDBG_H
