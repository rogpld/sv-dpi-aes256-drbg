`timescale 1ns / 1ps

module tb;

   import "DPI-C" context function void dpi_rng_init();
   import "DPI-C" context function int dpi_get_random_u32(output int val);

   const int NUM_SAMPLES = 100000;
   int       bit_counts[32];
   int       random_val;
   int       status;

   initial begin
      for (int i = 0; i < 32; i++) begin
         bit_counts[i] = 0;
      end

      $display("%0d samples", NUM_SAMPLES);

      dpi_rng_init();

      for (int s = 0; s < NUM_SAMPLES; s++) begin

         status = dpi_get_random_u32(random_val);

         if (status != 0) begin
            $error("FAILED %0d", s);
            $finish;
         end

         for (int b = 0; b < 32; b++) begin
            if (((random_val >> b) & 32'd1) != 0) begin
               bit_counts[b]++;
            end
         end
      end

      $display("Bit | Count (1s) | Frequency");
      $display("----|------------|----------");

      for (int b = 0; b < 32; b++) begin
         real freq;
         freq = (real'(bit_counts[b]) / real'(NUM_SAMPLES)) * 100.0;

         $display(" %2d |   %5d    |  %5.2f%% %s",
                  b,
                  bit_counts[b],
                  freq,
                  (freq < 48.0 || freq > 52.0) ? "<- WARNING" : "[OK]");
      end

      $display("DONE");
      $finish;
   end

endmodule
