input  [1:0] read_address;

input        line_0_valid;
input  [1:0] line_0_tag;
input  [7:0] line_0_block;

input        line_1_valid;
input  [1:0] line_1_tag;
input  [7:0] line_1_block;

output       read_hit;
output [7:0] read_byte;

wire line_0_match_1;
wire line_0_match_0;
wire line_0_match;
wire line_0_valid_match;

wire line_1_match_1;
wire line_1_match_0;
wire line_1_match;
wire line_1_valid_match;


wire line_0_block_07;
wire line_0_block_06;
wire line_0_block_05;
wire line_0_block_04;
wire line_0_block_03;
wire line_0_block_02;
wire line_0_block_01;
wire line_0_block_00;

wire line_1_block_07;
wire line_1_block_06;
wire line_1_block_05;
wire line_1_block_04;
wire line_1_block_03;
wire line_1_block_02;
wire line_1_block_01;
wire line_1_block_00;



assign line_0_match_1 = read_address[1] ~^ line_0_tag[1];
assign line_0_match_0 = read_address[0] ~^ line_0_tag[0];
assign line_0_match = line_0_match_1 & line_0_match_0;
assign line_0_valid_match = line_0_valid & line_0_match;

assign line_1_match_1 = read_address[1] ~^ line_1_tag[1];
assign line_1_match_0 = read_address[0] ~^ line_1_tag[0];
assign line_1_match = line_1_match_1 & line_1_match_0;
assign line_1_valid_match = line_1_valid & line_1_match;

assign read_hit = line_0_valid_match | line_1_valid_match;

assign line_0_block_07 = line_0_match & line_0_block[7];
assign line_0_block_06 = line_0_match & line_0_block[6];
assign line_0_block_05 = line_0_match & line_0_block[5];
assign line_0_block_04 = line_0_match & line_0_block[4];
assign line_0_block_03 = line_0_match & line_0_block[3];
assign line_0_block_02 = line_0_match & line_0_block[2];
assign line_0_block_01 = line_0_match & line_0_block[1];
assign line_0_block_00 = line_0_match & line_0_block[0];

assign line_1_block_07 = line_1_match & line_1_block[7];
assign line_1_block_06 = line_1_match & line_1_block[6];
assign line_1_block_05 = line_1_match & line_1_block[5];
assign line_1_block_04 = line_1_match & line_1_block[4];
assign line_1_block_03 = line_1_match & line_1_block[3];
assign line_1_block_02 = line_1_match & line_1_block[2];
assign line_1_block_01 = line_1_match & line_1_block[1];
assign line_1_block_00 = line_1_match & line_1_block[0];

assign read_byte[7] = line_0_block_07 | line_1_block_07;
assign read_byte[6] = line_0_block_06 | line_1_block_06;
assign read_byte[5] = line_0_block_05 | line_1_block_05;
assign read_byte[4] = line_0_block_04 | line_1_block_04;
assign read_byte[3] = line_0_block_03 | line_1_block_03;
assign read_byte[2] = line_0_block_02 | line_1_block_02;
assign read_byte[1] = line_0_block_01 | line_1_block_01;
assign read_byte[0] = line_0_block_00 | line_1_block_00;