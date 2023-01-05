#include "ap_axi_sdata.h"
#include "ap_int.h"
#include "hls_stream.h"
#include "krnl_s2mm.h"
#include "patterns.h"
#include "string.h"
// Naive Version
#define FIFO_SIZE 350		// naive fifo_size


void krnl_s2mm(ap_uint<OUTWIDTH> *out,     // Write only memory mapped
               hls::stream<pkt> &n2k,    // Internal Stream
               const unsigned int     size     // Size in bytes
               ) {
#pragma HLS INTERFACE m_axi port = out offset = slave bundle = gmem
#pragma HLS INTERFACE axis port = n2k
#pragma HLS INTERFACE s_axilite port = out bundle = control
#pragma HLS INTERFACE s_axilite port = size bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

  unsigned int bytes_per_beat = (DWIDTH / 8);
  unsigned int count = 0;

  data_mover:
    int out_i = 0;

    char fifo[FIFO_SIZE];
    memset(fifo, ' ', FIFO_SIZE);

  pkt_loop:
    for (unsigned int x = 0; x < (size / bytes_per_beat); x++) {
		pkt v;
		n2k.read(v);
  char_loop:
      for (unsigned int y = 0; y < bytes_per_beat; ++y) {
      	const char current_char = v.data.range(7 + y * 8, y * 8);

      	// shift
        for (int i = FIFO_SIZE - 1; i > 0 ; i--) {
		#pragma HLS UNROLL
            fifo[i] = fifo[i - 1];
        }
        fifo[0] = current_char;

        ap_uint<16> id = 0;
//         matching
        for(int i = 0; i < PATTERNS_COUNT; i++){
    	#pragma HLS UNROLL
        	bool match_i = true;
        	for (int j = 0; j < pattern_lengths[i]; ++j) {
			#pragma HLS UNROLL
        		char c = patterns[i][j];
        		bool tmp_bool = fifo[pattern_lengths[i] - 1 - j] == c;
        		match_i &= tmp_bool;
        	}
        	ap_uint<16> match_id = 0;
        	if(match_i){
        		match_id = i + 1;
        	}
        	id |= match_id;

      	}
        out[out_i].range(OUTWIDTH - 1 - (y * 16), OUTWIDTH - 16 - (y * 16)) = id - 1;
      }

      ++out_i;
    }
  }
