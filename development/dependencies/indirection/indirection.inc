/*
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the indirection.inc function pointers library.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (c) 2022
	the Initial Developer. All Rights Reserved.
*/

#if defined _INC_indirection
	#endinput
#endif
#define _INC_indirection

/**
 * <library
 *   name="indirection"
 *   summary="Function pointers and code redirection."
 *   license="Copyright (c) 2022 Alex &quot;Y_Less&quot; Cole.  Licensed under MPL 1.1"
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     Indirection is a system for calling function pointers in a generic and
 *     type-safe way.  Instead of <c>CallLocalFunction</c>, <c>Call</c>,
 *     <c>defer</c>, <c>Callback_Call</c>, or any other method, this gives one
 *     common interface which can be extended by library authors; utilising
 *     tags for compile-time parameters.
 *   </remarks>
 * </library>
 */

/// <p/>

#if !defined AMX_HEADER_INC
	#tryinclude "..\amx\amx_header"
#endif
#if !defined AMX_HEADER_INC
	#tryinclude <amx_assembly\amx_header>
#endif
#if !defined AMX_HEADER_INC
	#tryinclude "..\amx_assembly\amx_header"
#endif
#if !defined AMX_HEADER_INC
	#tryinclude "..\..\amx_assembly\amx_header"
#endif
#if !defined AMX_HEADER_INC
	#tryinclude "amx_header"
#endif
#if !defined AMX_HEADER_INC
	#tryinclude <amx_header>
#endif
#if !defined AMX_HEADER_INC
	#define AMX_INCLUDING_FAILED
#endif

#if defined AMX_INCLUDING_FAILED
	#error Could not include "https://github.com/Zeex/amx_assembly" - ensure its files are in "include\amx_assembly\"
//#elseif !defined AddressofResolve
//	#error Please update "https://github.com/Zeex/amx_assembly" to the latest version.
#endif

#if defined CUSTOM_TAG_TYPES
	#define GLOBAL_TAG_TYPES {_,Bit,Text,Group,File,Float,Text3D,CUSTOM_TAG_TYPES}
#else
	#define GLOBAL_TAG_TYPES {_,Bit,Text,Group,File,Float,Text3D}
#endif

#if !defined INDIRECTION_META_DATA_SIZE
	#define INDIRECTION_META_DATA_SIZE (8)
#endif

enum E_INDIRECTION
{
	E_INDIRECTION_ALWAYS_NULL, // So we can tell this is not a string.
	E_INDIRECTION_HANDER,      // Called by `@` to handle this pointer.
	E_INDIRECTION_CLAIM,       // Called by `Indirect_Claim`.
	E_INDIRECTION_RELEASE,     // Called by `Indirect_Release`.
	E_INDIRECTION_METADATA,    // Only used by end-users.
	E_INDIRECTION_TAG,         // Save the encoded parameters tag of this callback.
	E_INDIRECTION_OWNER,       // Attach the function to players etc.
	E_INDIRECTION_NEXT         // Next pointer in a generic list of callbacks.
}

stock
	INDIRECTION_META[INDIRECTION_META_DATA_SIZE],
	INDIRECTION_COUNT = 0,
	INDIRECTION_DATA = 0,
	INDIRECTION_TAG = 0;

// Constant offsets for assembly.
const
	E_INDIRECTION_ALWAYS_NULL__ = _:E_INDIRECTION_ALWAYS_NULL * cellbytes,
	E_INDIRECTION_HANDER__      = _:E_INDIRECTION_HANDER * cellbytes,
	E_INDIRECTION_CLAIM__       = _:E_INDIRECTION_CLAIM * cellbytes,
	E_INDIRECTION_RELEASE__     = _:E_INDIRECTION_RELEASE * cellbytes,
	E_INDIRECTION_METADATA__    = _:E_INDIRECTION_METADATA * cellbytes,
	E_INDIRECTION_TAG__         = _:E_INDIRECTION_TAG * cellbytes,
	E_INDIRECTION_OWNER__       = _:E_INDIRECTION_OWNER * cellbytes,
	E_INDIRECTION_NEXT__        = _:E_INDIRECTION_NEXT * cellbytes,
	E_INDIRECTION__             = _:E_INDIRECTION * cellbytes;

stock const
	INDIRECTION_NAUGHT = 0;

static stock
	INDR_gsAddr = 0,
	INDR_gsTmp = 0,
	INDR_gsTag[64],
	INDR_gsCodSize = 0, // The size of `COD`.
	INDR_gsKnownOwnedCallbacks = 0;

#if !defined YSI_MAX_STRING
	#define YSI_MAX_STRING (144)
#endif

#define string:
#define void:

#define PP_LEFT_BRACKET<> (

#if !defined TAGOF
	#if ((__Pawn & 0x0F) >= 0x0A) || ((__Pawn & 0xF0) >= 0xA0)
		// Defer `tagof` on things with colons slightly to remove anything after
		// it.  This lets us do `tagof (Float:i)` with no problem, since the `i`
		// is removed.
		#define TAGOF(%0);
		#define __TAGOF__[%0] %0:
		#define tagof(%0:%1) __NO_TAGOF:__IS_TAGOF:tagof PP_LEFT_BRACKET<>%0:$%1)
		#define __NO_TAGOF:__IS_TAGOF:tagof%9<>%0)%2:$%1) tagof%9<>%0)%2:%1)
		#define __IS_TAGOF:tagof%9<>%0:$%1) tagof%9<>__TAGOF__[%0])
	#elseif defined __COMPILER_TAG_DATA
		#define TAGOF(%0);
	#else
		#define TAGOF(%0); stock const %0:__TAGOF__%0;
		#define __TAGOF__%0\32; __TAGOF__
		#define tagof(%0:%1) __NO_TAGOF:__IS_TAGOF:tagof PP_LEFT_BRACKET<>%0:$%1)
		#define __NO_TAGOF:__IS_TAGOF:tagof%9<>%0)%2:$%1) tagof%9<>%0)%2:%1)
		#define __IS_TAGOF:tagof%9<>%0:$%1) tagof%9<>__TAGOF__%0)
	#endif

	#if !defined __COMPILER_TAG_DATA
		stock bool:operator==(_:a, __NO_TAGOF:b)
		{
			return a == _:b;
		}

		stock bool:operator!=(_:a, __NO_TAGOF:b)
		{
			return a != _:b;
		}
	#endif

	#define __TAGOF__F@_@%0\32; __TAGOF__F@_@
	#if defined __COMPILER_TAG_DATA
		#define SPECIFIER(%0) __COMPILER_TAG_DATA(F@_@%0,0)
	#else
		#define SPECIFIER(%0) TAGOF(F@_@%0)
	#endif
#endif

#if defined __PawnBuild
	// Because I somewhat scuppered myself!
	#if __PawnBuild == 0
		#define INDIRECTION_FUNC_INC__
		#undef __PawnBuild
	#endif
#else
	#define INDIRECTION_FUNC_INC__
#endif
#if defined INDIRECTION_FUNC_INC__
	forward __Indirect_FuncInc__();
	
	public __Indirect_FuncInc__()
	{
		memcpy
			("", "", 0, 0, 0);
		funcidx
			("");
	}

	#undef INDIRECTION_FUNC_INC__
#endif

TAGOF(Float);
TAGOF(File);

// Technically the function tags are not always `F@_@`.  The third character can
// be anything, and is reserved for representing the return type.  However, it
// is currently not used.  DO NOT consume spaces after `F@_@` since this will
// break functions with no parameters since their tag is just `F@_@:` (or
// `F@_@_`).  Function tags could be weak, which means if you pass a pointer to
// a function that wants a different type, or pass an untyped pointer to a
// function that wants any type, you will get a mismatch warning.  However, you
// can pass a typed pointer to a function that doesn't expect any type for
// backwards-compatability reasons.  I decided against this though - make them
// strong and give warnings on all old code!
#define Func:%0<%1> F@_@%1:%0

// Examples of predeclarations of specifier types.  These fix a bug in the old
// compiler where you can't (always) do `tagof (Float:)`.  This is relevant here
// since the specifiers are passed as `F@_@i:Func`, so we need `tagof (F@_@i:)`
// to get at the specifier.  However, since that doesn't work, we instead need
// `tagof (__TAGOF__F@_@i)` with `stock const F@_@i:__TAGOF__F@_@i`.  I.e. we need a
// variable using the tag to get the tag from, instead of getting it directly.
SPECIFIER(i);
SPECIFIER(s);

// This is for getting excess parameters on non-strings.
#define _:%0,) _:%0)

// I did consider an alternate method of making `@` do this:
//   
//   #define @.%0(%1) Indirect_Data(%0),Indirect_Call(%1)
//   
// But that would fail when an `@` call contained another `@` call:
//   
//   @.Func1(@.Func2(42, 43));
//   
// It would save the stack manipulation though (not convinced it would be less
// code though with the generation of multiple function calls).
#define @ str_new_static

// V2 design, with meta-data on `@`.  Can now do:
//   
//   @.var(params)
//   @.&func<iis>(params)
//   @.&func(params)
//   @.func[meta](params)
//   
#define str_new_static.%0(%1) (Indirect_Call__(_:(INDIRECTION_DATA=_:%0,INDIRECTION_TAG=tagof(%0),Indirect_Meta()),%1))

/// <library>indirection</library>
native Indirect_Memcpy(dest[], source, index = 0, numbytes, maxlength = sizeof (dest)) = memcpy;

/// <library>indirection</library>
stock Indirect_Meta(GLOBAL_TAG_TYPES:...)
{
	// Offset to the first parameter.
	const cells0 = 3 * cellbytes;
	const cells1 = 2 * cellbytes;
	new meta;
	#emit ADDR.pri     cells0
	#emit STOR.S.pri   meta
	#emit LOAD.S.pri   cells1
	#emit STOR.pri     INDIRECTION_COUNT
	Indirect_Memcpy(INDIRECTION_META, meta, 0, INDIRECTION_COUNT, INDIRECTION_META_DATA_SIZE);
	return (INDIRECTION_COUNT /= cellbytes);
}

// Look for `&` for variable dereferencing.
#define INDIRECTION_DATA=_:%9&%0,INDIRECTION_TAG=tagof(%9), INDIRECTION_DATA=_:INDIR2_:addressof(%0),INDIRECTION_TAG=prototypeof(%0),

// Now we know this is an indirection call, are there any meta-data params?
#define Indirect_Call__(_:(INDIRECTION_DATA=_:%0[%2]%6,INDIRECTION_TAG=tagof(%4),Indirect_Meta()),%3) Indirect_Call__(_:(INDIRECTION_DATA=_:%0%6,INDIRECTION_TAG=tagof(%4),Indirect_Meta(%2)),%3)

// Look for `<>` generic tag types.
#define INDIR2_:addressof(%0<%4>),INDIRECTION_TAG=prototypeof(%9), addressof(%0<%4>),F@_@%4:INDIRECTION_TAG=F@_@%4:tagof(F@_@%4:),

// The `ALS_DO` callback syntax is `CALLBACK<name, specifier>(params)`
#define Indirect_DoCallback<%0,%4>(%9) O@A@("On"#%0),F@_@%4:INDIRECTION_TAG=F@_@%4:tagof(F@_@%4:),

// Simplify the complex ALS syntax.
//#define Indirect_ALS<%0><%1> %1<,%0>()
// Example:
//
//   #define ALS_DO_PlayerConnect Indirect_ALSTag<i>
//

// Can now do:
//   
//   @.var(params)
//   @.&func<iis>(params)
//   @.func[meta](params)
//   @.OnPlayerConnect(params)
//   

/// <library>indirection</library>
forward Indirect_Call(func, tag, GLOBAL_TAG_TYPES:...);

// Old API.
#define Indirect_Call(%0,%1) (Indirect_Call__(_:INDIR1_:(INDIRECTION_DATA=(%0),INDIRECTION_TAG=(%1),Indirect_Meta())))
#define INDIR1_:(INDIRECTION_DATA=(%0),INDIRECTION_TAG=(%1,%2),Indirect_Meta())) (INDIRECTION_DATA=(%0),INDIRECTION_TAG=(%1),Indirect_Meta()),%2)

#define Indirect_Meta() INDIRECTION_NAUGHT

/// <library>indirection</library>
stock Indirect_Call__(meta, GLOBAL_TAG_TYPES:...)
{
	const cells0 = 4 * cellbytes;
	const cells1 = -1 * cellbytes;
	const cells3 = 1 * cellbytes;
	const cells4 = 2 * cellbytes;
	#pragma unused meta
	if (!INDIRECTION_DATA)
	{
		return 0;
	}
	{}
	// The COD and DAT segments are different, so `func` pointing in to DAT
	// relative to COD will not be a valid pointer, and THAT you can detect!
	// 
	// Get the previous frame.  This undoes the effects of our `PROC` so the
	// called function must have a proper `PROC`.
	#emit ADDR.pri     cells0
	#emit STOR.pri     INDR_gsAddr
	#emit POP.pri
	#emit SCTRL        5
	// Get the return address.
	#emit POP.alt
	// Get the parameter count.
	#emit POP.pri
	// Reduce the parameter count.
	#emit ADD.C        cells1
	// Store the new parameter count.
	#emit SWAP.pri
	#emit STOR.pri     INDIRECTION_COUNT
	// Store the return address.
	#emit PUSH.alt
	// Check the pointer type.  If it is in the `COD` area, jump straight to it
	// with the tag for parameter types (if it isn't 0).  Otherwise, use the
	// `func` from `DAT` as a pointer to a handler.
	if (INDIRECTION_DATA >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.pri     INDIRECTION_DATA
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.pri     INDIRECTION_DATA
		if (!INDIRECTION_DATA)
		{
			// Get the function at `func - COD + 4`.
			#emit CONST.pri    E_INDIRECTION_HANDER__
			#emit ADD
			#emit LOAD.I
			// Call it, passing `func` as a proper pointer, NOT skipping `PROC`.
			#emit STOR.alt     INDIRECTION_DATA
			#emit SCTRL        6
			// NEVER RETURNS PAST HERE.
		}
		{}
		// `INDIRECTION_DATA` is now a pointer to a string of a function name.
		// Resolve it via index lookup.
		#emit PUSH.alt
		#emit PUSH.C       cells3
		#emit SYSREQ.C     funcidx
		#emit STACK        cells4
		#emit STOR.pri     INDIRECTION_DATA
		if (INDIRECTION_DATA == -1)
		{
			#emit PROC
			#emit RETN
		}
		{}
		// Get the address from the index.
		#if cellbits == 64
			const shifter = 3;
		#else
			const shifter = 2;
		#endif
		#emit LCTRL        __dat
		#emit NEG
		#emit ADD.C        32 // Always this, regardless of cell size.
		#emit STOR.pri     INDR_gsTmp
		#emit LREF.alt     INDR_gsTmp
		#emit LCTRL        __dat
		#emit NEG
		#emit ADD
		// This replicates `IDXADDR`, but in no more instructions since the data
		// are in the wrong registers.
		#emit LOAD.alt     INDIRECTION_DATA
		#emit SHL.C.alt    shifter
		#emit ADD
		// Add more data, to account for `__defsize` offsets.
		#emit LOAD.alt     INDIRECTION_DATA
		#emit SHL.C.alt    2
		#emit ADD
		#emit STOR.pri     INDR_gsTmp
		#emit LREF.pri     INDR_gsTmp
		#emit STOR.pri     INDIRECTION_DATA
	}
	if (INDIRECTION_TAG)
	{
		// Skip the `F@_@` prefix.
		GetTagNameFromID(INDIRECTION_TAG, INDR_gsTag);
		if (INDR_gsTag[0]) for (INDR_gsTmp = 4; ; )
		{
			switch (INDR_gsTag[INDR_gsTmp++])
			{
			case 'i', 'd', 't', 'f', 'c':
			{
				// Resolve non-reference parameters.
				#emit LREF.pri   INDR_gsAddr
				#emit LOAD.I
				#emit SREF.pri   INDR_gsAddr
			}
			case '\0', 'x':
				break;
			}
			INDR_gsAddr += cellbytes;
		}
	}
	{}
	// No handler, and no tag data.  Just jump to it and hope (hope it has a `PROC` too).
	#emit LOAD.pri     INDIRECTION_DATA
	#emit SCTRL        6
	return 0;
}

/// <library>indirection</library>
/// <remarks>
///   Not `Indirect_CallString` to make use of the `string:` macro.
/// </remarks>
stock string:Indirect_Callstring(func, tag, GLOBAL_TAG_TYPES:...)
{
	const cells0 = 2 * cellbytes;
	const cells1 = 3 * cellbytes;
	const cells2 = 5 * cellbytes;
	const cells3 = -2 * cellbytes;
	const cells4 = 1 * cellbytes;
	const cells5 = 1 * cellbytes;
	const cells6 = 2 * cellbytes;
	#pragma unused tag
	if (!func)
	{
		// Get the offset to the secret return parameter.
		#emit LOAD.S.pri   cells0
		#emit ADDR.alt     cells1
		#emit ADD
		#emit LOAD.I
		#emit MOVE.alt
		#emit ZERO.pri
		#emit STOR.I
		#emit RETN
		new ret[YSI_MAX_STRING];
		return ret;
	}
	{}
	#emit ADDR.pri     cells2
	#emit STOR.pri     INDR_gsAddr
	#emit POP.pri
	#emit SCTRL        5
	// Get the return address.
	#emit POP.alt
	// Get the parameter count.
	#emit POP.pri
	// Reduce the parameter count.
	#emit ADD.C        cells3
	// Store the return address.
	#emit SWAP.alt
	#emit STOR.alt     INDIRECTION_DATA
	#emit POP.alt
	// Store the new parameter count.
	#emit SWAP.pri
	#emit STOR.pri     INDIRECTION_TAG
	#emit PUSH.alt
	// Check the pointer type.  If it is in the `COD` area, jump straight to it
	// with the tag for parameter types (if it isn't 0).  Otherwise, use the
	// `func` from `DAT` as a pointer to a handler.
	if (INDIRECTION_DATA >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.pri     INDIRECTION_DATA
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.pri     INDIRECTION_DATA
		if (!INDIRECTION_DATA)
		{
			// Get the function at `func - COD + 4`.
			#emit CONST.pri    cells4
			#emit ADD
			#emit LOAD.I
			// Call it, passing `func` as a proper pointer, NOT skipping `PROC`.
			#emit STOR.alt     INDIRECTION_DATA
			#emit SCTRL        6
			// NEVER RETURNS PAST HERE.
		}
		{}
		// `INDIRECTION_DATA` is now a pointer to a string of a function name.
		// Resolve it via index lookup.
		#emit PUSH.alt
		#emit PUSH.C       cells5
		#emit SYSREQ.C     funcidx
		#emit STACK        cells6
		#emit STOR.pri     INDIRECTION_DATA
		if (INDIRECTION_DATA == -1)
		{
			#emit PROC
			#emit RETN
		}
		{}
		// Get the address from the index.
		#if cellbits == 64
			const shifter = 3;
		#else
			const shifter = 2;
		#endif
		#emit LCTRL        __dat
		#emit NEG
		#emit ADD.C        32 // Always this, regardless of cell size.
		#emit STOR.pri     INDR_gsTmp
		#emit LREF.alt     INDR_gsTmp
		#emit LCTRL        __dat
		#emit NEG
		#emit ADD
		// This replicates `IDXADDR`, but in no more instructions since the data
		// are in the wrong registers.
		#emit LOAD.alt     INDIRECTION_DATA
		#emit SHL.C.alt    shifter
		#emit ADD
		// Add more data, to account for `__defsize` offsets.
		#emit LOAD.alt     INDIRECTION_DATA
		#emit SHL.C.alt    2
		#emit ADD
		#emit STOR.pri     INDR_gsTmp
		#emit LREF.pri     INDR_gsTmp
		#emit STOR.pri     INDIRECTION_DATA
	}
	if (INDIRECTION_TAG)
	{
		// Skip the `F@_@` prefix.
		GetTagNameFromID(INDIRECTION_TAG, INDR_gsTag);
		if (INDR_gsTag[0]) for (INDR_gsTmp = 4; ; )
		{
			switch (INDR_gsTag[INDR_gsTmp++])
			{
			case 'i', 'd', 't', 'f', 'c':
			{
				// Resolve non-reference parameters.
				#emit LREF.pri   INDR_gsAddr
				#emit LOAD.I
				#emit SREF.pri   INDR_gsAddr
			}
			case '\0', 'x':
				break;
			}
			INDR_gsAddr += cellbytes;
		}
	}
	{}
	// No handler, and no tag data.  Just jump to it and hope.
	#emit LOAD.pri     INDIRECTION_DATA
	#emit SCTRL        6
	// Never called.  Don't use "static" because it would allocate real memory
	// in advance.  Instead, this will want to allocate on the stack but never
	// get hit to do so.
	new ret[YSI_MAX_STRING];
	return ret;
}

/// <library>indirection</library>
/// <remarks>
///   Not `Indirect_Callvoid` to make use of the `void:` macro.
/// </remarks>
stock void:Indirect_Callvoid(func, tag, GLOBAL_TAG_TYPES:...)
{
	const cells0 = 5 * cellbytes;
	const cells1 = -2 * cellbytes;
	const cells2 = 1 * cellbytes;
	const cells3 = 1 * cellbytes;
	const cells4 = 2 * cellbytes;
	#pragma unused tag
	if (!func)
	{
		return;
	}
	{}
	#emit ADDR.pri     cells0
	#emit STOR.pri     INDR_gsAddr
	#emit POP.pri
	#emit SCTRL        5
	// Get the return address.
	#emit POP.alt
	// Get the parameter count.
	#emit POP.pri
	// Reduce the parameter count.
	#emit ADD.C        cells1
	// Store the return address.
	#emit SWAP.alt
	#emit STOR.alt     INDIRECTION_DATA
	#emit POP.alt
	// Store the new parameter count.
	#emit SWAP.pri
	#emit STOR.pri     INDIRECTION_TAG
	#emit PUSH.alt
	// Check the pointer type.  If it is in the `COD` area, jump straight to it
	// with the tag for parameter types (if it isn't 0).  Otherwise, use the
	// `func` from `DAT` as a pointer to a handler.
	if (INDIRECTION_DATA >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.pri     INDIRECTION_DATA
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.pri     INDIRECTION_DATA
		if (!INDIRECTION_DATA)
		{
			// Get the function at `func - COD + 4`.
			#emit CONST.pri    cells2
			#emit ADD
			#emit LOAD.I
			// Call it, passing `func` as a proper pointer, NOT skipping `PROC`.
			#emit STOR.alt     INDIRECTION_DATA
			#emit SCTRL        6
			// NEVER RETURNS PAST HERE.
		}
		{}
		// `INDIRECTION_DATA` is now a pointer to a string of a function name.
		// Resolve it via index lookup.
		#emit PUSH.alt
		#emit PUSH.C       cells3
		#emit SYSREQ.C     funcidx
		#emit STACK        cells4
		#emit STOR.pri     INDIRECTION_DATA
		if (INDIRECTION_DATA == -1)
		{
			#emit PROC
			#emit RETN
		}
		{}
		// Get the address from the index.
		#if cellbits == 64
			const shifter = 3;
		#else
			const shifter = 2;
		#endif
		#emit LCTRL        __dat
		#emit NEG
		#emit ADD.C        32 // Always this, regardless of cell size.
		#emit STOR.pri     INDR_gsTmp
		#emit LREF.alt     INDR_gsTmp
		#emit LCTRL        __dat
		#emit NEG
		#emit ADD
		// This replicates `IDXADDR`, but in no more instructions since the data
		// are in the wrong registers.
		#emit LOAD.alt     INDIRECTION_DATA
		#emit SHL.C.alt    shifter
		#emit ADD
		// Add more data, to account for `__defsize` offsets.
		#emit LOAD.alt     INDIRECTION_DATA
		#emit SHL.C.alt    2
		#emit ADD
		#emit STOR.pri     INDR_gsTmp
		#emit LREF.pri     INDR_gsTmp
		#emit STOR.pri     INDIRECTION_DATA
	}
	if (INDIRECTION_TAG)
	{
		// Skip the `F@_@` prefix.
		GetTagNameFromID(INDIRECTION_TAG, INDR_gsTag);
		if (INDR_gsTag[0]) for (INDR_gsTmp = 4; ; )
		{
			switch (INDR_gsTag[INDR_gsTmp++])
			{
			case 'i', 'd', 't', 'f', 'c':
			{
				// Resolve non-reference parameters.
				#emit LREF.pri   INDR_gsAddr
				#emit LOAD.I
				#emit SREF.pri   INDR_gsAddr
			}
			case '\0', 'x':
				break;
			}
			INDR_gsAddr += cellbytes;
		}
	}
	{}
	// No handler, and no tag data.  Just jump to it and hope.
	#emit LOAD.pri     INDIRECTION_DATA
	#emit SCTRL        6
	// Don't return anything.
}

/// <library>indirection</library>
stock Indirect_Array(func, tag, const params[], size = sizeof (params))
{
	#if cellbits == 32
		const cells0 = 2;
	#elseif cellbits == 64
		const cells0 = 3;
	#else
		#error Unsupported `cellbits`.
	#endif
	const cells1 = 5 * cellbytes;
	const cells2 = 6 * cellbytes;
	const cells4 = 1 * cellbytes;
	const cells5 = 2 * cellbytes;
	static
		ret = 0,
		src = 0;
	#pragma unused func, tag, params, size
	// Get the previous frame.  This undoes the effects of our `PROC` so the
	// called function must have a proper `PROC`.
	#emit POP.pri
	#emit SCTRL        5
	// Get the return address.
	#emit POP.pri
	#emit STOR.pri     ret
	// Remove the parameter count.
	#emit POP.pri
	// Get the target tag.
	#emit POP.pri
	#emit STOR.pri     INDIRECTION_DATA
	// Get the target function.
	#emit POP.pri
	#emit STOR.pri     INDIRECTION_TAG
	// Get the source data.
	#emit POP.alt
	#emit STOR.alt     src
	// Get the size.
	#emit POP.alt
	#emit SHL.C.alt    cells0
//	#emit STOR.alt     cnt
	// We cannot just adjust the stack size while the other parameters are still
	// on it, since the new stack might be smaller than the old one, and dealing
	// with that in a simple way is not possible.  Well, it is possible - it's
	// what we are doing!  Copy the parameters.
	#emit LCTRL        4
	#emit SUB
	#emit SCTRL        4
	#emit PUSH.alt
	#emit PUSH.alt
	#emit PUSH.C       0
	#emit PUSH         src
	#emit STOR.pri     src
	#emit PUSH.pri
	#emit PUSH.C       cells1
	#emit SYSREQ.C     memcpy
	#emit MOVE.pri
	#emit STACK        cells2
	#emit PUSH.pri
	#emit PUSH         ret
	// 
	// Check the pointer type.  If it is in the `COD` area, jump straight to it
	// with the tag for parameter types (if it isn't 0).  Otherwise, use the
	// `func` from `DAT` as a pointer to a handler.
	if (INDIRECTION_DATA >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.pri     INDIRECTION_DATA
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.pri     INDIRECTION_DATA
		if (!INDIRECTION_DATA)
		{
			#emit STOR.alt     INDIRECTION_DATA
			// Get the function at `func - COD + 4`.
			#emit LOAD.pri     INDIRECTION_DATA
			#emit ADD.C        E_INDIRECTION_HANDER__
			#emit LOAD.I
			// Call it, passing `func` as a proper pointer, NOT skipping `PROC`.
			#emit SCTRL        6
			// NEVER RETURNS PAST HERE.
		}
		{}
		// `INDIRECTION_DATA` is now a pointer to a string of a function name.
		// Resolve it via index lookup.
		#emit PUSH.alt
		#emit PUSH.C       cells4
		#emit SYSREQ.C     funcidx
		#emit STACK        cells5
		#emit STOR.pri     INDIRECTION_DATA
		if (INDIRECTION_DATA == -1)
		{
			// Failure.
			#emit PROC
			#emit RETN
		}
		{}
		// Get the address from the index.
		#if cellbits == 64
			const shifter = 3;
		#else
			const shifter = 2;
		#endif
		#emit LCTRL        __dat
		#emit NEG
		#emit ADD.C        32 // Always this, regardless of cell size.
		#emit STOR.pri     INDR_gsTmp
		#emit LREF.alt     INDR_gsTmp
		#emit LCTRL        __dat
		#emit NEG
		#emit ADD
		// This replicates `IDXADDR`, but in no more instructions since the data
		// are in the wrong registers.
		#emit LOAD.alt     INDIRECTION_DATA
		#emit SHL.C.alt    shifter
		#emit ADD
		// Add more data, to account for `__defsize` offsets.
		#emit LOAD.alt     INDIRECTION_DATA
		#emit SHL.C.alt    2
		#emit ADD
		#emit STOR.pri     INDR_gsTmp
		#emit LREF.pri     INDR_gsTmp
		#emit STOR.pri     INDIRECTION_DATA
	}
	if (INDIRECTION_TAG)
	{
		// Skip the `F@_@` prefix.
		GetTagNameFromID(INDIRECTION_TAG, INDR_gsTag);
		if (INDR_gsTag[0]) for (INDR_gsTmp = 4; ; )
		{
			switch (INDR_gsTag[INDR_gsTmp++])
			{
			case 'i', 'd', 't', 'f', 'c':
			{
				// Resolve non-reference parameters.
				#emit LREF.pri   src
				#emit LOAD.I
				#emit SREF.pri   src
			}
			case '\0', 'x':
				break;
			}
			src += cellbytes;
		}
	}
	{}
	// No handler, and no tag data.  Just jump to it and hope (hope it has a `PROC` too).
	#emit LOAD.pri     INDIRECTION_DATA
	#emit SCTRL        6
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="func">The function pointer with attached Nextdata.</param>
 * <remarks>
 *   Gets extra data from the pointer.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_GetNext_(func)
{
	if (func >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Probably a string.
			return 0;
		}
		{}
		// I'm relying on `alt` not changing here...
		// Get the function at `func - COD + 16`.
		#emit CONST.pri    E_INDIRECTION_NEXT__
		#emit ADD
		#emit LOAD.I
		#emit RETN
	}
	return 0;
}
#define Indirect_GetNext(%0) Indirect_GetNext_(_:%0)

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="func">The function pointer to attach Nextdata to.</param>
 * <param name="data">The Nextdata.</param>
 *//*------------------------------------------------------------------------**/

stock Indirect_SetNext_(func, data)
{
	if (func >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Probably a string.
			return false;
		}
		{}
		// I'm relying on `alt` not changing here...
		// Get the function at `func - COD + 16`.
		#emit CONST.pri    E_INDIRECTION_NEXT__
		#emit ADD
		#emit LOAD.S.alt   data
		#emit XCHG
		#emit STOR.I
		return true;
	}
	return false;
}
#define Indirect_SetNext(%0,%1) Indirect_SetNext_(_:(%0),%1)

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="func">The function pointer to attach Nextdata to.</param>
 * <returns><c>1</c> - an indirection function.  <c>2</c> - a string name.
 * <c>3</c> - a code pointer.
 *//*------------------------------------------------------------------------**/

stock Indirect_GetType_(func)
{
	if (func >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// String.
			return 2;
		}
		// Indirect.
		return 1;
	}
	// Pointer.
	return 3;
}
#define Indirect_GetType(%0) Indirect_GetType_(_:(%0))

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="func">The function pointer with a tag.</param>
 * <remarks>
 *   Gets the tag of the pointer.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_GetTag_(func)
{
	if (func >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Probably a string.
			return 0;
		}
		{}
		// I'm relying on `alt` not changing here...
		// Get the function at `func - COD + 16`.
		#emit CONST.pri    E_INDIRECTION_TAG__
		#emit ADD
		#emit LOAD.I
		#emit RETN
	}
	return 0;
}
#define Indirect_GetTag(%0) Indirect_GetTag_(_:%0)

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="func">The function pointer to attach a tag to.</param>
 * <param name="tag">The tag.</param>
 *//*------------------------------------------------------------------------**/

stock bool:Indirect_SetTag_(func, tag)
{
	if (func >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Probably a string.
			return false;
		}
		{}
		// I'm relying on `alt` not changing here...
		// Get the function at `func - COD + 16`.
		#emit CONST.pri    E_INDIRECTION_TAG__
		#emit ADD
		#emit LOAD.S.alt   tag
		#emit XCHG
		#emit STOR.I
		return true;
	}
	return false;
}
#define Indirect_SetTag(%0,%1) Indirect_SetTag_(_:(%0),%1)

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="func">The function pointer with an owner.</param>
 * <remarks>
 *   Gets the owner of the pointer.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_GetOwner_(func)
{
	if (func >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Probably a string.
			return 0;
		}
		{}
		// I'm relying on `alt` not changing here...
		// Get the function at `func - COD + 16`.
		#emit CONST.pri    E_INDIRECTION_OWNER__
		#emit ADD
		#emit LOAD.I
		#emit CONST.alt    cellmax
		#emit AND
		#emit RETN
	}
	return 0;
}
#define Indirect_GetOwner(%0) Indirect_GetOwner_(_:%0)

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="func">The function pointer to attach an owner to.</param>
 * <param name="data">The owner.</param>
 *//*------------------------------------------------------------------------**/

stock Indirect_SetOwner_(func, owner)
{
	if (func >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Probably a string.
			return false;
		}
		{}
		#emit STOR.S.alt   func
		// Store the owner.
		WriteAmxMemory(func + E_INDIRECTION_OWNER__, owner | cellmin);
		return true;
	}
	return false;
}
#define Indirect_SetOwner(%0,%1) Indirect_SetOwner_(_:(%0),%1)

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="func">The function pointer with attached metadata.</param>
 * <remarks>
 *   Gets extra data from the pointer.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_GetMeta_(func)
{
	if (func >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Probably a string.
			return 0;
		}
		{}
		// I'm relying on `alt` not changing here...
		// Get the function at `func - COD + 16`.
		#emit CONST.pri    E_INDIRECTION_METADATA__
		#emit ADD
		#emit LOAD.I
		#emit RETN
	}
	return 0;
}
#define Indirect_GetMeta(%0) Indirect_GetMeta_(_:%0)

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="func">The function pointer to attach metadata to.</param>
 * <param name="data">The metadata.</param>
 *//*------------------------------------------------------------------------**/

stock Indirect_SetMeta_(func, data)
{
	if (func >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Probably a string.
			return false;
		}
		{}
		// I'm relying on `alt` not changing here...
		// Get the function at `func - COD + 16`.
		#emit CONST.pri    E_INDIRECTION_METADATA__
		#emit ADD
		#emit LOAD.S.alt   data
		#emit XCHG
		#emit STOR.I
		return true;
	}
	return false;
}
#define Indirect_SetMeta(%0,%1) Indirect_SetMeta_(_:(%0),%1)

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="func">The function pointer you want to use later.</param>
 * <remarks>
 *   If a function pointer is used within one function, that is not a problem.
 *   However, if you want to store the function pointer for use later, you must
 *   first "claim" it, so that any associated data is not cleared when the
 *   parent function ends (i.e. the function that called your function).  After
 *   use it must be released, and the number of claims must match the number of
 *   releases.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_Claim_(func)
{
	if (func >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Probably a string.
			return;
		}
		{}
		// I'm relying on `alt` not changing here...  A LOT!
		#emit CONST.pri    E_INDIRECTION_CLAIM__
		#emit ADD
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (!func)
		{
			// Already claimed.
			return;
		}
		{}
		// Save the pointer to pass on.
		#emit STOR.S.alt   func
		// Clean up owner lists.
		new next = ReadAmxMemory(func + E_INDIRECTION_OWNER__);
		if (next)
		{
			WriteAmxMemory(func + E_INDIRECTION_NEXT__, INDR_gsKnownOwnedCallbacks);
			INDR_gsKnownOwnedCallbacks = func + E_INDIRECTION_NEXT__;
		}
		next = ReadAmxMemory(func + E_INDIRECTION_CLAIM__);
		#pragma unused next // It is used, secretly in assembly...
		WriteAmxMemory(func + E_INDIRECTION_CLAIM__, 0);
		// `next` is at the top of the stack with the code pointer.
		#emit POP.pri
		#emit SWAP.pri
		#emit SCTRL        5
		#emit POP.pri
		#emit SCTRL        6
	}
}
#define Indirect_Claim(%0) Indirect_Claim_(_:%0)

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <remarks>
 *   Null function that does nothing for when an owner is gone.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Indirect_Stub(...)
{
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <remarks>
 *   Hack to allow external access to this address, so that we can do some tests
 *   more quickly in places.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_GetStubPointer()
{
	static stub = 0;
	if (!stub)
	{
		if (stub)
		{
			// Include in the output.  Can't be called.
			Indirect_Stub();
		}
		{}
		#emit CONST.pri    Indirect_Stub
		#emit STOR.pri     stub
	}
	return stub;
}

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="owner">A person or other entity that no longer exists.</param>
 * <remarks>
 *   Disables all callbacks belonging to this entity.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_Disconnect(owner)
{
	// Special "owned" flag.
	owner |= cellmin;
	new
		prev = ref(INDR_gsKnownOwnedCallbacks),
		cur = ReadAmxMemory(prev),
		stub = Indirect_GetStubPointer();
	while (cur)
	{
		if (ReadAmxMemory(cur - (E_INDIRECTION_NEXT__ - E_INDIRECTION_OWNER__)) == owner)
		{
			// Disable the handler.
			WriteAmxMemory(cur - (E_INDIRECTION_NEXT__ - E_INDIRECTION_HANDER__), stub),
			WriteAmxMemory(cur - (E_INDIRECTION_NEXT__ - E_INDIRECTION_OWNER__), 0),
			// Remove from the list.
			INDR_gsTmp = ReadAmxMemory(cur),
			WriteAmxMemory(prev, INDR_gsTmp),
			WriteAmxMemory(cur, 0),
			cur = INDR_gsTmp;
		}
		else
		{
			prev = cur;
			cur = ReadAmxMemory(prev);
		}
	}
}

///*-------------------------------------------------------------------------*//**
// * <library>indirection</library>
// * <param name="owner">A person or other entity that no longer exists.</param>
// * <param name="meta">Meta-data that needs matching.</param>
// * <remarks>
// *   This is a cheap way of adding two owners, To only disable all callbacks
// *   belonging to this entity with matching meta-data.
// * </remarks>
// *//*------------------------------------------------------------------------**/
//
//stock Indirect_Disconnect2(owner, meta)
//{
//	// Special "owned" flag.
//	owner |= cellmin;
//	new
//		prev = ref(INDR_gsKnownOwnedCallbacks),
//		cur = ReadAmxMemory(prev),
//		stub = Indirect_GetStubPointer();
//	while (cur)
//	{
//		if (
//			ReadAmxMemory(cur - (E_INDIRECTION_NEXT__ - E_INDIRECTION_METADATA__)) == meta &&
//			ReadAmxMemory(cur - (E_INDIRECTION_NEXT__ - E_INDIRECTION_OWNER__)) == owner
//			)
//		{
//			// Disable the handler.
//			WriteAmxMemory(cur - (E_INDIRECTION_NEXT__ - E_INDIRECTION_HANDER__), stub),
//			WriteAmxMemory(cur - (E_INDIRECTION_NEXT__ - E_INDIRECTION_OWNER__), 0),
//			// Remove from the list.
//			INDR_gsTmp = ReadAmxMemory(cur),
//			WriteAmxMemory(prev, INDR_gsTmp),
//			WriteAmxMemory(cur, 0),
//			cur = INDR_gsTmp;
//		}
//		else
//		{
//			prev = cur;
//			cur = ReadAmxMemory(prev);
//		}
//	}
//}
//
//#define Indirect_Disconnect(%0,%1) Indirect_Disconnect2(%0,%1)

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 *//*------------------------------------------------------------------------**/

native Indirect_FuncIDX_(ptr) = funcidx;

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="func">The function pointer you had previously stored.</param>
 * <remarks>
 *   Is it still valid (exists and not disabled).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Indirect_IsValid_(func)
{
	if (func >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Strings must be valid.  I guess we could use `funcidx`...
			// Extract the pointer back out of `alt`.
			#emit STOR.S.alt   func
			return Indirect_FuncIDX_(func) != -1;
		}
		{}
		// I'm relying on `alt` not changing here...
		#emit CONST.pri    E_INDIRECTION_HANDER__
		#emit ADD
		#emit LOAD.I
		#emit STOR.S.pri   func
		return func != Indirect_GetStubPointer();
	}
	// Direct pointers are always valid (because we can't tell otherwise).
	return func != 0;
}
#define Indirect_IsValid(%0) Indirect_IsValid_(_:%0)

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="func">The function pointer you had previously stored.</param>
 * <remarks>
 *   If a function pointer is used within one function, that is not a problem.
 *   However, if you want to store the function pointer for use later, you must
 *   first "claim" it, so that any associated data is not cleared when the
 *   parent function ends (i.e. the function that called your function).  After
 *   use it must be released, and the number of claims must match the number of
 *   releases.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_Release_(func)
{
	if (func >= INDR_gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     INDR_gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Probably a string.
			return;
		}
		{}
		// I'm relying on `alt` not changing here...  A LOT!
		#emit CONST.pri    E_INDIRECTION_RELEASE__
		#emit ADD
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (!func)
		{
			// Already claimed.
			return;
		}
		{}
		// Save the pointer to pass on.
		#emit STOR.S.alt   func
		// Clean up owner lists.
		new next = ReadAmxMemory(func + E_INDIRECTION_OWNER__);
		if (next)
		{
			next = ref(INDR_gsKnownOwnedCallbacks);
			new cur = ReadAmxMemory(next);
			while (cur)
			{
				if (cur == func + E_INDIRECTION_NEXT__)
				{
					cur = ReadAmxMemory(cur);
					WriteAmxMemory(next, cur);
					WriteAmxMemory(func + E_INDIRECTION_NEXT__, 0);
					WriteAmxMemory(func + E_INDIRECTION_OWNER__, 0);
					break;
				}
				next = cur;
				cur = ReadAmxMemory(next);
			}
		}
		next = ReadAmxMemory(func + E_INDIRECTION_RELEASE__);
		#pragma unused next // It is used, secretly in assembly...
		WriteAmxMemory(func + E_INDIRECTION_RELEASE__, 0);
		// `next` is at the top of the stack with the code pointer.
		#emit POP.pri
		#emit SWAP.pri
		#emit SCTRL        5
		#emit POP.pri
		#emit SCTRL        6
	}
}
#define Indirect_Release(%0) Indirect_Release_(_:%0)

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="id">The ID of the tag to get the specifiers from the name of.
 * </param>
 * <param name="dest">Where to store the name.</param>
 * <remarks>
 *   Functions are tagged with a special tag containing their specifiers.  Get
 *   the string value of that tag from the AMX header.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_Tag(id, dest[32])
{
	GetTagNameFromID(id, INDR_gsTag),
	dest[0] = '\0';
	if (INDR_gsTag[0])
		strcat(dest, INDR_gsTag[4]);
}

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="">The array to convert to an offset pointer.</param>
 * <remarks>
 *   Strings and arrays are passed relative to `COD` not `DAT` so they can be
 *   distinguished from normal function pointers.  This function does the
 *   offset.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_Ref_(...)
{
	const cells0 = 3 * cellbytes;
	assert(numargs() == 1);
	#emit LOAD.S.pri       cells0
	#emit LOAD.alt         INDR_gsCodSize
	#emit ADD
	#emit RETN
	return 0;
}
#define Indirect_Ref(%0) Indirect_Ref_(_:(%0))

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="">The array to convert to an offset pointer.</param>
 * <remarks>
 *   Strings and arrays are passed relative to `COD` not `DAT` so they can be
 *   distinguished from normal function pointers.  This function does the
 *   offset.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_Ptr_(ptr)
{
	const cells0 = 3 * cellbytes;
	#pragma unused ptr
	assert(numargs() == 1);
	#emit LOAD.S.pri       cells0
	#emit LOAD.alt         INDR_gsCodSize
	#emit ADD
	#emit RETN
	return 0;
}
#define Indirect_Ptr(%0) Indirect_Ptr_(_:(%0))

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="">The array to convert to an offset pointer.</param>
 * <remarks>
 *   Strings and arrays are passed relative to `COD` not `DAT` so they can be
 *   distinguished from normal function pointers.  This function does the
 *   offset.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_DeRef_(...)
{
	const cells0 = 3 * cellbytes;
	assert(numargs() == 1);
	#emit LOAD.S.pri       cells0
	#emit LOAD.alt         INDR_gsCodSize
	#emit SUB
	#emit RETN
	return 0;
}
#define Indirect_DeRef(%0) Indirect_DeRef_(_:(%0), sizeof (%0[]))

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <param name="">The array to convert to an offset pointer.</param>
 * <remarks>
 *   Strings and arrays are passed relative to `COD` not `DAT` so they can be
 *   distinguished from normal function pointers.  This function does the
 *   offset.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_DePtr_(ptr)
{
	#emit LOAD.S.pri       ptr
	#emit LOAD.alt         INDR_gsCodSize
	#emit SUB
	#emit RETN
	return 0;
}
#define Indirect_DePtr(%0) Indirect_DePtr_(_:(%0))

#if !defined _ALS_OnJITCompile
	forward OnJITCompile();
#endif

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <remarks>
 *   A generic public wrapper for calling inline functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Indirect_FromCallback(Func:cb<>, bool:release);

public Indirect_FromCallback(Func:cb<>, bool:release)
{
	new ret = @.cb();
	if (release)
		Indirect_Release(cb);
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <remarks>
 *   Get integer metadata.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Indirect_GetMetaInt(index, &ret)
{
	if (INDIRECTION_COUNT > index)
	{
		index = INDIRECTION_META[index];
		#emit LREF.S.pri   index
		#emit SREF.S.pri   ret
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <remarks>
 *   Get float metadata.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Indirect_GetMetaFloat(index, &Float:ret)
{
	if (INDIRECTION_COUNT > index)
	{
		index = INDIRECTION_META[index];
		#emit LREF.S.pri   index
		#emit SREF.S.pri   ret
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <remarks>
 *   Get boolean metadata.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Indirect_GetMetaBool(index, &bool:ret)
{
	if (INDIRECTION_COUNT > index)
	{
		index = INDIRECTION_META[index];
		#emit LREF.S.pri   index
		#emit SREF.S.pri   ret
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <remarks>
 *   Get ref metadata.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Indirect_GetMetaRef(index, &ret)
{
	if (INDIRECTION_COUNT > index)
	{
		index = INDIRECTION_META[index];
		#emit LOAD.S.pri   index
		#emit SREF.S.pri   ret
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <remarks>
 *   Set ref metadata.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Indirect_SetMetaRef(index, val)
{
	if (INDIRECTION_COUNT > index)
	{
		index = INDIRECTION_META[index];
		#emit LOAD.S.pri   val
		#emit SREF.S.pri   index
		return true;
	}
	return false;
}

/// <library>indirection</library>
native Indirect_Strcat(dest[], const source, maxlength = sizeof (dest)) = dest;

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <remarks>
 *   Get ref metadata.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Indirect_GetMetaString(index, dest[], size = sizeof (dest))
{
	if (INDIRECTION_COUNT > index)
	{
		dest[0] = '\0',
		Indirect_Strcat(dest, INDIRECTION_META[index], size);
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>indirection</library>
 * <remarks>
 *   Get the size of the COD AMX segment.
 * </remarks>
 *//*------------------------------------------------------------------------**/

Indirect_Init()
{
	if (!INDR_gsCodSize)
	{
		#emit LCTRL        __cod
		#emit MOVE.alt
		#emit LCTRL        __dat
		#emit SUB
		#emit STOR.pri     INDR_gsCodSize
	}
}
 
/// <library>indirection</library>
public OnJITCompile()
{
	Indirect_Init();
	#if defined Indirection_OnJITCompile
		return Indirection_OnJITCompile();
	#else
		return 1;
	#endif
}

/// <library>indirection</library>
public OnFilterScriptInit()
{
	Indirect_Init();
	#if defined Indirection_OnFilterScriptInit
		Indirection_OnFilterScriptInit();
	#endif
	return 1;
}

/// <library>indirection</library>
public OnGameModeInit()
{
	Indirect_Init();
	#if defined Indirection_OnGameModeInit
		Indirection_OnGameModeInit();
	#endif
	return 1;
}

#if defined Indirection_OnJITCompile
	forward Indirection_OnJITCompile();
#endif
#if defined _ALS_OnJITCompile
	#undef OnJITCompile
#else
	#define _ALS_OnJITCompile
#endif
#define OnJITCompile(%0) Indirection_OnJITCompile(%0)

#if defined Indirection_OnFilterScriptInit
	forward Indirection_OnFilterScriptInit();
#endif
#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit(%0) Indirection_OnFilterScriptInit(%0)

#if defined Indirection_OnGameModeInit
	forward Indirection_OnGameModeInit();
#endif
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit(%0) Indirection_OnGameModeInit(%0)

