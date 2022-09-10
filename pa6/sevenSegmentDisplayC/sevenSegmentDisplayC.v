input [3:0] numeral_bit;

output c;

wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

wire not_3_and_not_2;
wire 1_and_not_0;

wire maxterm_02;

assign not_numeral_bit_3 = ~ numeral_bit[3];
assign not_numeral_bit_2 = ~ numeral_bit[2];
assign not_numeral_bit_1 = ~ numeral_bit[1];
assign not_numeral_bit_0 = ~ numeral_bit[0];

assign not_3_and_not_2 = not_numeral_bit_3 & not_numeral_bit_2;
assign 1_and_not_0 = numeral_bit[1] & not_numeral_bit_0;
assign maxterm_02 = not_3_and_not_2 & 1_and_not_0;
assign c = ~ maxterm_02;
