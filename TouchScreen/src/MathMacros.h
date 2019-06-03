#ifndef MATHMACROS_H
#define MATHMACROS_H

#define MM_MIN(value1, value2) (((value1) >= (value2)) ? (value2) : (value1))
#define MM_MAX(value1, value2) (((value1) >= (value2)) ? (value1) : (value2))
#define MM_CLAMP(value, min, max) (((value) < (min)) ? (min) : ((value) > (max)) ? (max) : (value))
#define MM_CLAMP01(value) (MM_CLAMP(value, 0.0, 1.0))
#define MM_LERPUNCLAMPED(from, to, value) ((from * (1.0 - value)) + (to * value))
#define MM_LERP(from, to, value) (MM_LERPUNCLAMPED((from), (to), (MM_CLAMP01(value))))

#endif
