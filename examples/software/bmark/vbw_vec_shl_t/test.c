/* VECTORBLOX MXP SOFTWARE DEVELOPMENT KIT
 *
 * Copyright (C) 2012-2018 VectorBlox Computing Inc., Vancouver, British Columbia, Canada.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 *     * Neither the name of VectorBlox Computing Inc. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This agreement shall be governed in all respects by the laws of the Province
 * of British Columbia and by the laws of Canada.
 *
 * This file is part of the VectorBlox MXP Software Development Kit.
 *
 */


#include "vbx_copyright.h"
VBXCOPYRIGHT( test_vec_shl )

/*
 * Vector Add - Scalar version and Vector version
 */

#include <stdio.h>
#include "vbx.h"
#include "vbx_test.h"
#include "scalar_vec_shl.h"
#include "vbw_vec_shl.h"

#define VBX_TEMPLATE_T   VBX_UBYTESIZE_DEF
// signed   VBX_BYTESIZE_DEF    VBX_HALFSIZE_DEF    VBX_WORDSIZE_DEF
// unsigned VBX_UBYTESIZE_DEF   VBX_UHALFSIZE_DEF   VBX_UWORDSIZE_DEF
#include "vbw_template_t.h"

int test_vector( vbx_sp_t *v_out, vbx_sp_t *v_in, int N)
{
	int retval;

	printf( "\nExecuting MXP vector overflow test...\n" );

	retval = VBX_T(vbw_vec_shl)( v_out, v_in, N );
	vbx_sync();

	printf( "...done. retval: %X\n", retval );
	return retval;
}


int test_scalar( vbx_mm_t *scalar_out, vbx_mm_t *scalar_in, int N )
{
	printf( "\nExecuting scalar shift overflow test...\n" );

	VBX_T(scalar_vec_shl)( scalar_out, scalar_in, N );

	printf( "...done\n" );
	return 0;
}

int main(void)
{
	vbx_test_init();
	vbx_mxp_t *this_mxp = VBX_GET_THIS_MXP();
	const int VBX_SCRATCHPAD_SIZE = this_mxp->scratchpad_size;
	const int required_vectors = 4;

	int N = VBX_SCRATCHPAD_SIZE / sizeof(vbx_mm_t) / required_vectors;

	int PRINT_LENGTH = N< MAX_PRINT_LENGTH ? N:MAX_PRINT_LENGTH;

	double scalar_time;
	int errors=0;

	vbx_mxp_print_params();
	printf( "\nShift overflow test...\n" );
	printf( "Vector length: %d\n", N );

	vbx_mm_t *scalar_in = malloc( N*sizeof(vbx_mm_t) );
	vbx_mm_t *scalar_out = malloc( N*sizeof(vbx_mm_t) );

	vbx_mm_t *vector_in = vbx_shared_malloc( N*sizeof(vbx_mm_t) );
	vbx_mm_t *vector_out = vbx_shared_malloc( N*sizeof(vbx_mm_t) );

	vbx_sp_t *v_in = vbx_sp_malloc( N*sizeof(vbx_sp_t) );
	vbx_sp_t *v_out = vbx_sp_malloc( N*sizeof(vbx_sp_t) );

	VBX_T(test_zero_array)( scalar_out, N );
	VBX_T(test_zero_array)( vector_out, N );

	VBX_T(test_init_array)( scalar_in, N, 1 );
	VBX_T(test_copy_array)( vector_in, scalar_in, N );

	VBX_T(test_print_array)( scalar_in, PRINT_LENGTH );

	scalar_time = test_scalar( scalar_out, scalar_in, N );
	VBX_T(test_print_array)( scalar_out, PRINT_LENGTH);

	vbx_dma_to_vector( v_in, (void *)vector_in, N*sizeof(vbx_sp_t) );
	test_vector( v_out, v_in, N );
	vbx_dma_to_host( (void *)vector_out, v_out, N*sizeof(vbx_sp_t) );
	vbx_sync();
	VBX_T(test_print_array)( vector_out, PRINT_LENGTH );

	errors += VBX_T(test_verify_array)( scalar_out, vector_out, N );

	vbx_shared_free(vector_in);
	vbx_shared_free(vector_out);
	free(scalar_in);
	free(scalar_out);

	VBX_TEST_END(errors);
	return 0;
}
