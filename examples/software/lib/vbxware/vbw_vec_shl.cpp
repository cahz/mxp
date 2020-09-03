#include "vbx.h"
#include "vbw_exit_codes.h"

template<typename vbx_sp_t>
int vbw_vec_shl(vbx_sp_t *v_out, vbx_sp_t *v_in, unsigned int vl)
{
	vbx_sp_t *v_temp = (vbx_sp_t *)vbx_sp_malloc(sizeof(vbx_sp_t)*vl);

	vbx_set_vl(vl,1,1);

	// zero the output and temp
	vbxx(VMOV, v_out, 0);

	for (int i = 1; i <= 8*sizeof(vbx_sp_t); i++){
		vbxx(VSHL, v_temp, v_in, i);

		// set v_out to the index at which it overflows
		vbxx(VCMV_FS, v_out, i, v_temp);

		// set index to 0 if overflow flag is set
		vbxx(VCMV_NZ, v_in, 0, v_out);
	}

	vbx_sync();
	return VBW_SUCCESS;
}
extern "C" int vbw_vec_shl_word(vbx_word_t *v_out, vbx_word_t *v_in, unsigned int vl){
	return vbw_vec_shl<vbx_word_t>(v_out,v_in,vl);
}
extern "C" int vbw_vec_shl_uword(vbx_uword_t *v_out, vbx_uword_t *v_in, unsigned int vl){
	return vbw_vec_shl<vbx_uword_t>(v_out,v_in,vl);
}
extern "C" int vbw_vec_shl_half(vbx_half_t *v_out, vbx_half_t *v_in, unsigned int vl){
	return vbw_vec_shl<vbx_half_t>(v_out,v_in,vl);
}
extern "C" int vbw_vec_shl_uhalf(vbx_uhalf_t *v_out, vbx_uhalf_t *v_in, unsigned int vl){
	return vbw_vec_shl<vbx_uhalf_t>(v_out,v_in,vl);
}
extern "C" int vbw_vec_shl_byte(vbx_byte_t *v_out, vbx_byte_t *v_in, unsigned int vl){
	return vbw_vec_shl<vbx_byte_t>(v_out,v_in,vl);
}
extern "C" int vbw_vec_shl_ubyte(vbx_ubyte_t *v_out, vbx_ubyte_t *v_in, unsigned int vl){
	return vbw_vec_shl<vbx_ubyte_t>(v_out,v_in,vl);
}
